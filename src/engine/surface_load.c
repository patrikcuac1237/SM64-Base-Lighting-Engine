#include <PR/ultratypes.h>

#include "sm64.h"
#include "game/ingame_menu.h"
#include "graph_node.h"
#include "behavior_script.h"
#include "behavior_data.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/macro_special_objects.h"
#include "surface_collision.h"
#include "math_util.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
#include "surface_load.h"
#include "game/puppyprint.h"

#include "config.h"

/**
 * Partitions for course and object surfaces. The arrays represent
 * the 16x16 cells that each level is split into.
 */
SpatialPartitionCell gStaticSurfacePartition[NUM_CELLS][NUM_CELLS];
SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];

/**
 * Pools of data to contain either surface nodes or surfaces.
 */
struct SurfaceNode *sSurfaceNodePool;
struct Surface *sSurfacePool;

/**
 * The size of the surface node pool (SURFACE_NODE_POOL_SIZE).
 */
s32 sSurfaceNodePoolSize = SURFACE_NODE_POOL_SIZE;

/**
 * The size of the surface pool (SURFACE_POOL_SIZE).
 */
s32 sSurfacePoolSize = SURFACE_POOL_SIZE;

u8 gSurfacePoolError = 0x0;

/**
 * Allocate the part of the surface node pool to contain a surface node.
 */
static struct SurfaceNode *alloc_surface_node(void) {
    struct SurfaceNode *node = &sSurfaceNodePool[gSurfaceNodesAllocated++];

    node->next = NULL;

    if (gSurfaceNodesAllocated >= sSurfaceNodePoolSize) {
        gSurfacePoolError |= NOT_ENOUGH_ROOM_FOR_NODES;
    }

    return node;
}

/**
 * Allocate the part of the surface pool to contain a surface and
 * initialize the surface.
 */
static struct Surface *alloc_surface(void) {

    struct Surface *surface = &sSurfacePool[gSurfacesAllocated++];

    if (gSurfacesAllocated >= sSurfacePoolSize) {
        gSurfacePoolError |= NOT_ENOUGH_ROOM_FOR_SURFACES;
    }

    surface->type = SURFACE_DEFAULT;
    surface->force = 0;
    surface->flags = SURFACE_FLAGS_NONE;
    surface->room = 0;
    surface->object = NULL;

    return surface;
}

/**
 * Iterates through the entire partition, clearing the surfaces.
 */
static void clear_spatial_partition(SpatialPartitionCell *cells) {
    register s32 i = sqr(NUM_CELLS);

    while (i--) {
        (*cells)[SPATIAL_PARTITION_FLOORS].next = NULL;
        (*cells)[SPATIAL_PARTITION_CEILS].next = NULL;
        (*cells)[SPATIAL_PARTITION_WALLS].next = NULL;
        (*cells)[SPATIAL_PARTITION_WATER].next = NULL;
        (*cells)[SPATIAL_PARTITION_SHADOWS].next = NULL;

        cells++;
    }
}

/**
 * Clears the static (level) surface partitions for new use.
 */
static void clear_static_surfaces(void) {
    clear_spatial_partition(&gStaticSurfacePartition[0][0]);
}

/**
 * Add a surface to the correct cell list of surfaces.
 * @param dynamic Determines whether the surface is static or dynamic
 * @param cellX The X position of the cell in which the surface resides
 * @param cellZ The Z position of the cell in which the surface resides
 * @param surface The surface to add
 */
static void add_surface_to_cell(s32 dynamic, s32 cellX, s32 cellZ, struct Surface *surface) {
    struct SurfaceNode *list;
    s32 priority;
    s32 sortDir = 1; 
    s32 listIndex;

    // Clasificación por tipo de superficie
    if (SURFACE_IS_NEW_WATER(surface->type)) {
        listIndex = SPATIAL_PARTITION_WATER;
    } 
    else if (SURFACE_IS_SHADOW_VOLUME(surface->type)) { // <--- Lógica para sombras
        listIndex = SPATIAL_PARTITION_SHADOWS;
    }
    else if (surface->normal.y > NORMAL_FLOOR_THRESHOLD) {
        listIndex = SPATIAL_PARTITION_FLOORS;
    } else if (surface->normal.y < NORMAL_CEIL_THRESHOLD) {
        listIndex = SPATIAL_PARTITION_CEILS;
        sortDir = -1;
    } else {
        listIndex = SPATIAL_PARTITION_WALLS;
        sortDir = 0;
    }

    // ... (El resto de la función para alojar el nodo se mantiene igual)
    s32 surfacePriority = surface->upperY * sortDir;
    struct SurfaceNode *newNode = alloc_surface_node();
    newNode->surface = surface;

    if (dynamic) {
        list = &gDynamicSurfacePartition[cellZ][cellX][listIndex];
    } else {
        list = &gStaticSurfacePartition[cellZ][cellX][listIndex];
    }

    // Loop until we find the appropriate place for the surface in the list.
    while (list->next != NULL) {
        priority = list->next->surface->upperY * sortDir;

        if (surfacePriority > priority) {
            break;
        }

        list = list->next;
    }

    newNode->next = list->next;
    list->next = newNode;
}

/**
 * Every level is split into CELL_SIZE * CELL_SIZE cells of surfaces (to limit computing
 * time). This function determines the lower cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s32 lower_cell_index(s32 coord) {
    // Move from range [-LEVEL_BOUNDARY_MAX, LEVEL_BOUNDARY_MAX) to [0, 2 * LEVEL_BOUNDARY_MAX)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) {
        coord = 0;
    }

    // [0, NUM_CELLS)
    s32 index = coord / CELL_SIZE;

    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE < 50) {
        index--;
    }

    // Potentially > NUM_CELLS - 1, but since the upper index is <= NUM_CELLS - 1, not exploitable
    return MAX(0, index);
}

/**
 * Every level is split into CELL_SIZE * CELL_SIZE cells of surfaces (to limit computing
 * time). This function determines the upper cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s32 upper_cell_index(s32 coord) {
    // Move from range [-LEVEL_BOUNDARY_MAX, LEVEL_BOUNDARY_MAX) to [0, 2 * LEVEL_BOUNDARY_MAX)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) {
        coord = 0;
    }

    // [0, NUM_CELLS)
    s32 index = coord / CELL_SIZE;

    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE > CELL_SIZE - 50) {
        index++;
    }

    // Potentially < 0, but since lower index is >= 0, not exploitable
    return MIN((NUM_CELLS - 1), index);
}

/**
 * Every level is split into 16x16 cells, this takes a surface, finds
 * the appropriate cells (with a buffer), and adds the surface to those
 * cells.
 * @param surface The surface to check
 * @param dynamic Boolean determining whether the surface is static or dynamic
 */
static void add_surface(struct Surface *surface, s32 dynamic) {
    s32 cellZ, cellX;
    s32 minX, maxX, minZ, maxZ;

    min_max_3i(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0], &minX, &maxX);
    min_max_3i(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2], &minZ, &maxZ);

    s32 minCellX = lower_cell_index(minX);
    s32 maxCellX = upper_cell_index(maxX);
    s32 minCellZ = lower_cell_index(minZ);
    s32 maxCellZ = upper_cell_index(maxZ);

    for (cellZ = minCellZ; cellZ <= maxCellZ; cellZ++) {
        for (cellX = minCellX; cellX <= maxCellX; cellX++) {
            add_surface_to_cell(dynamic, cellX, cellZ, surface);
        }
    }
}

/**
 * Initializes a Surface struct using the given vertex data
 * @param vertexData The raw data containing vertex positions
 * @param vertexIndices Helper which tells positions in vertexData to start reading vertices
 */
static struct Surface *read_surface_data(TerrainData *vertexData, TerrainData **vertexIndices) {
    Vec3t v[3];
    Vec3f n;
    Vec3t offset;
    s16 min, max;

    // --- CORRECCIÓN AQUÍ ---
    // Como vertexData ahora es un puntero a s32 (Collision), al sumar un índice
    // saltaría 4 bytes. Necesitamos que salte 2 bytes (s16) para leer la ROM.
    s16 *data16 = (s16 *)vertexData;
    // -----------------------

    vec3_prod_val(offset, (*vertexIndices), 3);

    // Usamos data16 para realizar la suma de punteros correctamente
    vec3s_copy(v[0], (data16 + offset[0]));
    vec3s_copy(v[1], (data16 + offset[1]));
    vec3s_copy(v[2], (data16 + offset[2]));

    find_vector_perpendicular_to_plane(n, v[0], v[1], v[2]);

    vec3f_normalize(n);

    struct Surface *surface = alloc_surface();

    vec3s_copy(surface->vertex1, v[0]);
    vec3s_copy(surface->vertex2, v[1]);
    vec3s_copy(surface->vertex3, v[2]);

    surface->normal.x = n[0];
    surface->normal.y = n[1];
    surface->normal.z = n[2];

    surface->originOffset = -vec3_dot(n, v[0]);

    min_max_3s(v[0][1], v[1][1], v[2][1], &min, &max);
    surface->lowerY = (min - SURFACE_VERTICAL_BUFFER);
    surface->upperY = (max + SURFACE_VERTICAL_BUFFER);

    return surface;
}

#ifndef ALL_SURFACES_HAVE_FORCE
/**
 * Returns whether a surface has exertion/moves Mario
 * based on the surface type.
 */
static s32 surface_has_force(s32 surfaceType) {
    s32 hasForce = FALSE;

    switch (surfaceType) {
        case SURFACE_FLOWING_WATER:
        case SURFACE_DEEP_MOVING_QUICKSAND:
        case SURFACE_SHALLOW_MOVING_QUICKSAND:
        case SURFACE_MOVING_QUICKSAND:
        case SURFACE_HORIZONTAL_WIND:
        case SURFACE_INSTANT_MOVING_QUICKSAND:
            hasForce = TRUE;
            break;

        default:
            break;
    }
    return hasForce;
}
#endif

/**
 * Returns whether a surface should have the
 * SURFACE_FLAG_NO_CAM_COLLISION flag.
 */
static s32 surf_has_no_cam_collision(s32 surfaceType) {
    s32 flags = SURFACE_FLAGS_NONE;

    switch (surfaceType) {
        case SURFACE_NO_CAM_COLLISION:
        case SURFACE_NO_CAM_COLLISION_77: // Unused
        case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
            flags = SURFACE_FLAG_NO_CAM_COLLISION;
            break;

        default:
            break;
    }

    return flags;
}

/**
 * Load in the surfaces for a given surface type. This includes setting the flags,
 * exertion, and room.
 */
static void load_static_surfaces(TerrainData **data, TerrainData *vertexData, s32 surfaceType, RoomData **surfaceRooms) {
    s32 i;
    struct Surface *surface;
    RoomData room = 0;
#ifndef ALL_SURFACES_HAVE_FORCE
    s16 hasForce = surface_has_force(surfaceType);
#endif
    s32 flags = surf_has_no_cam_collision(surfaceType);

    // --- CORRECCIÓN DE LECTURA INICIAL ---
    // Obtenemos una vista de 16 bits para leer la cantidad de superficies
    s16 *data16 = (s16 *)*data;
    s32 numSurfaces = *data16++; 
    // Actualizamos el puntero original al terminar
    *data = (TerrainData *)data16; 

    for (i = 0; i < numSurfaces; i++) {
        if (*surfaceRooms != NULL) {
            room = *(*surfaceRooms)++;
        }

        // read_surface_data ya está corregida con el cast a s16
        surface = read_surface_data(vertexData, data);
        
        if (surface != NULL) {
            surface->room = room;
            surface->type = surfaceType;
            surface->flags = flags;

            // --- CORRECCIÓN DE ACCESO A DATOS ---
            // Usamos data16 para leer los índices o valores de fuerza de la ROM
            data16 = (s16 *)*data;
            
#ifdef ALL_SURFACES_HAVE_FORCE
            surface->force = data16[3]; // Equivalent a *(*data + 3) pero en s16
#else
            if (hasForce) {
                surface->force = data16[3];
            } else {
                surface->force = 0;
            }
#endif

            add_surface(surface, FALSE);
        }

        // --- CORRECCIÓN DE AVANCE DE PUNTERO ---
#ifdef ALL_SURFACES_HAVE_FORCE
        data16 += 4;
#else
        data16 += 3;
        if (hasForce) {
            data16++;
        }
#endif
        // Guardamos la posición final del puntero tras los saltos
        *data = (TerrainData *)data16;
    }
}

/**
 * Read the data for vertices for reference by triangles.
 */
static TerrainData *read_vertex_data(TerrainData **data) {
    // Convertimos a s16* para leer correctamente la estructura de la ROM
    s16 *data16 = (s16 *)*data;

    // Leemos el número de vértices (esto avanza 2 bytes)
    s32 numVertices = *data16++;

    // Guardamos la dirección actual como el inicio de los datos de vértices
    TerrainData *vertexData = (TerrainData *)data16;

    // Avanzamos el puntero: 3 coordenadas por vértice (x, y, z), 2 bytes por coordenada.
    // Esto es igual a (3 * numVertices) elementos de tipo s16.
    data16 += 3 * numVertices;

    // Actualizamos el puntero original (el que recibe el resto del motor) 
    // convertido de nuevo a TerrainData* (s32*)
    *data = (TerrainData *)data16;

    return vertexData;
}
/**
 * Loads in special environmental regions, such as water, poison gas, and JRB fog.
 */
static void load_environmental_regions(TerrainData **data) {
    s32 i;
    
    // --- CORRECCIÓN AQUÍ ---
    // Mantenemos una vista de 16 bits para navegar el binario de la ROM
    s16 *data16 = (s16 *)*data;
    
    gEnvironmentRegions = *data;
    s32 numRegions = *data16++; // Leemos el contador como s16

    for (i = 0; i < numRegions; i++) {
        // Saltamos 5 elementos de 2 bytes cada uno (10 bytes en total)
        data16 += 5; 
        
        // Leemos el nivel ambiental como s16
        gEnvironmentLevels[i] = *data16++;
    }

    // Sincronizamos el puntero original al terminar
    *data = (TerrainData *)data16;
}
/**
 * Allocate some of the main pool for surfaces (2300 surf) and for surface nodes (7000 nodes).
 */
void alloc_surface_pools(void) {
    sSurfaceNodePool = main_pool_alloc(sSurfaceNodePoolSize * sizeof(struct SurfaceNode), MEMORY_POOL_LEFT);
    sSurfacePool = main_pool_alloc(sSurfacePoolSize * sizeof(struct Surface), MEMORY_POOL_LEFT);

    gCCMEnteredSlide = FALSE;
    reset_red_coins_collected();
}

#ifdef NO_SEGMENTED_MEMORY
/**
 * Get the size of the terrain data, to get the correct size when copying later.
 */
u32 get_area_terrain_size(TerrainData *data) {
    TerrainData *startPos = data;
    s32 end = FALSE;
    TerrainData terrainLoadType;
    s32 numVertices;
    s32 numRegions;
    s32 numSurfaces;
#ifndef ALL_SURFACES_HAVE_FORCE
    TerrainData hasForce;
#endif

    while (!end) {
        terrainLoadType = *data++;

        switch (terrainLoadType) {
            case TERRAIN_LOAD_VERTICES:
                numVertices = *data++;
                data += 3 * numVertices;
                break;

            case TERRAIN_LOAD_OBJECTS:
                data += get_special_objects_size(data);
                break;

            case TERRAIN_LOAD_ENVIRONMENT:
                numRegions = *data++;
                data += 6 * numRegions;
                break;

            case TERRAIN_LOAD_CONTINUE:
                continue;

            case TERRAIN_LOAD_END:
                end = TRUE;
                break;

            default:
                numSurfaces = *data++;
#ifdef ALL_SURFACES_HAVE_FORCE
                data += 4 * numSurfaces;
#else
                hasForce = surface_has_force(terrainLoadType);
                data += (3 + hasForce) * numSurfaces;
#endif
                break;
        }
    }

    return data - startPos;
}
#endif


/**
 * Process the level file, loading in vertices, surfaces, some objects, and environmental
 * boxes (water, gas, JRB fog).
 */
void load_area_terrain(s32 index, TerrainData *data, RoomData *surfaceRooms, s16 *macroObjects) {
    s32 terrainLoadType;
    TerrainData *vertexData = NULL;
    
    // --- CORRECCIÓN AQUÍ ---
    // Usamos un puntero s16 para navegar por el flujo de datos binarios (ROM).
    // Esto garantiza que los saltos de memoria sean de 2 bytes, no de 4.
    s16 *stream = (s16 *)data;
    // -----------------------

#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif

    gEnvironmentRegions = NULL;
    gSurfaceNodesAllocated = 0;
    gSurfacesAllocated = 0;

    clear_static_surfaces();

    while (TRUE) {
        // Leemos el tipo de comando (2 bytes) correctamente
        terrainLoadType = *stream++;

        // Actualizamos el puntero 'data' para que las funciones subyacentes
        // (que ya tienen el cast a s16 interno) reciban la dirección correcta.
        data = (TerrainData *)stream;

        if (TERRAIN_LOAD_IS_SURFACE_TYPE_LOW(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
        } else if (terrainLoadType == TERRAIN_LOAD_VERTICES) {
            vertexData = read_vertex_data(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_OBJECTS) {
            spawn_special_objects(index, &data);
        } else if (terrainLoadType == TERRAIN_LOAD_ENVIRONMENT) {
            load_environmental_regions(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_CONTINUE) {
            // Actualizamos stream tras saltar (si es necesario)
            stream = (s16 *)data;
            continue;
        } else if (terrainLoadType == TERRAIN_LOAD_END) {
            break;
        } else if (TERRAIN_LOAD_IS_SURFACE_TYPE_HIGH(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
            stream = (s16 *)data; // Sincronizamos stream tras el retorno
            continue;
        }

        // Tras cada llamada, sincronizamos el stream con la posición donde quedó 'data'
        stream = (s16 *)data;
    }

    if (macroObjects != NULL && *macroObjects != -1) {
        if (0 <= *macroObjects && *macroObjects < 30) {
            spawn_macro_objects_hardcoded(index, macroObjects);
        } else {
            spawn_macro_objects(index, macroObjects);
        }
    }

    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += osGetTime() - first;
#endif
}

/**
 * If not in time stop, clear the surface partitions.
 */
void clear_dynamic_surfaces(void) {
    if (!(gTimeStopState & TIME_STOP_ACTIVE)) {
        gSurfacesAllocated = gNumStaticSurfaces;
        gSurfaceNodesAllocated = gNumStaticSurfaceNodes;

        clear_spatial_partition(&gDynamicSurfacePartition[0][0]);
    }
}

/**
 * Applies an object's transformation to the object's vertices.
 */
void transform_object_vertices(TerrainData **data, TerrainData *vertexData) {
    Mat4 *objectTransform = &o->transform;

    // --- CORRECCIÓN AQUÍ ---
    // Usamos un puntero auxiliar para leer la ROM como s16
    s16 *stream = (s16 *)*data;
    
    register s32 numVertices = *stream++;
    // -----------------------

    if (o->header.gfx.throwMatrix == NULL) {
        o->header.gfx.throwMatrix = objectTransform;
        obj_build_transform_from_pos_and_angle(o, O_POS_INDEX, O_FACE_ANGLE_INDEX);
    }

    Mat4 transform;
    mtxf_scale_vec3f(transform, *objectTransform, o->header.gfx.scale);

    Vec3f pos;
    while (numVertices--) {
        // Leemos del stream s16 (ROM)
        vec3s_to_vec3f(pos, stream);
        stream += 3; // Salto correcto de 6 bytes (3 * 2)

        //! No bounds check on vertex data
        linear_mtxf_mul_vec3_and_translate(transform, vertexData, pos);

        // vertexData sigue siendo TerrainData* (s32*), así que 
        // al sumar 3 saltamos 12 bytes. Esto es correcto para escribir en el struct.
        vertexData += 3; 
    }

    // Sincronizamos el puntero original al terminar
    *data = (TerrainData *)stream;
}

/**
 * Load in the surfaces for the o. This includes setting the flags, exertion, and room.
 */
void load_object_surfaces(TerrainData **data, TerrainData *vertexData) {
    s32 i;
    // Creamos el stream de 16 bits para navegar el binario
    s16 *stream = (s16 *)*data;

    s32 surfaceType = *stream++;
    s32 numSurfaces = *stream++;

#ifndef ALL_SURFACES_HAVE_FORCE
    TerrainData hasForce = surface_has_force(surfaceType);
#endif

    s32 flags = surf_has_no_cam_collision(surfaceType) | SURFACE_FLAG_DYNAMIC;
    RoomData room = (o->behavior == segmented_to_virtual(bhvDddWarp)) ? 5 : 0;

    for (i = 0; i < numSurfaces; i++) {
        // Sincronizamos data para que read_surface_data (que ya está corregida) 
        // reciba el puntero correcto
        *data = (TerrainData *)stream;
        struct Surface *surface = read_surface_data(vertexData, data);
        
        // Recuperamos el stream donde haya quedado la lectura de read_surface_data
        stream = (s16 *)*data;

        if (surface != NULL) {
            surface->object = o;
            surface->type = surfaceType;

#ifdef ALL_SURFACES_HAVE_FORCE
            surface->force = stream[3]; // Leemos el force desde el stream de 16 bits
#else
            if (hasForce) {
                surface->force = stream[3];
            } else {
                surface->force = 0;
            }
#endif
            surface->flags |= flags;
            surface->room = room;
            add_surface(surface, TRUE);
        }

        // Avance del stream (s16 stride)
#ifdef ALL_SURFACES_HAVE_FORCE
        stream += 4;
#else
        if (hasForce) {
            stream += 4;
        } else {
            stream += 3;
        }
#endif
    }
    // Sincronizamos el puntero final
    *data = (TerrainData *)stream;
}

#ifdef AUTO_COLLISION_DISTANCE
static void get_optimal_coll_dist(struct Object *obj) {
    register f32 thisVertDist, maxDist = 0.0f;
    Vec3f v;
    
    // --- CORRECCIÓN AQUÍ ---
    // Cast a s16 para recorrer la estructura original de datos
    s16 *stream = (s16 *)o->collisionData;
    
    obj->oFlags |= OBJ_FLAG_DONT_CALC_COLL_DIST;
    
    stream++; // Saltar tipo (primer elemento)
    u32 vertsLeft = *stream++; // Saltar cantidad de vértices
    
    while (vertsLeft) {
        // vec3_prod espera datos, pasamos el stream s16
        vec3_prod(v, stream, obj->header.gfx.scale);
        
        thisVertDist = vec3_sumsq(v);
        if (thisVertDist > maxDist) maxDist = thisVertDist;
        
        stream += 3; // Salto correcto de 6 bytes (3 * 2)
        vertsLeft--;
    }
    obj->oCollisionDistance = (sqrtf(maxDist) + 100.0f);
}
#endif

/**
 * Transform an object's vertices, reload them, and render the object.
 */
void load_object_collision_model(void) {
    TerrainData vertexData[600];
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif

    TerrainData *collisionData = o->collisionData;
    f32 marioDist = o->oDistanceToMario;

    // On an object's first frame, the distance is set to 19000.0f.
    // If the distance hasn't been updated, update it now.
    if (o->oDistanceToMario == 19000.0f) {
        marioDist = dist_between_objects(o, gMarioObject);
    }

#ifdef AUTO_COLLISION_DISTANCE
    if (!(o->oFlags & OBJ_FLAG_DONT_CALC_COLL_DIST)) {
        get_optimal_coll_dist(o);
    }
#endif

    // If the object collision is supposed to be loaded more than the
    // drawing distance, extend the drawing range.
    if (o->oCollisionDistance > o->oDrawingDistance) {
        o->oDrawingDistance = o->oCollisionDistance;
    }

    // Update if no Time Stop, in range, and in the current room.
    if (
        !(gTimeStopState & TIME_STOP_ACTIVE)
        && (marioDist < o->oCollisionDistance)
        && !(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)
    ) {
        collisionData++;
        transform_object_vertices(&collisionData, vertexData);

        // TERRAIN_LOAD_CONTINUE acts as an "end" to the terrain data.
        while (*collisionData != TERRAIN_LOAD_CONTINUE) {
            load_object_surfaces(&collisionData, vertexData);
        }
    }
    COND_BIT((marioDist < o->oDrawingDistance), o->header.gfx.node.flags, GRAPH_RENDER_ACTIVE);
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += osGetTime() - first;
#endif
}
