#ifndef SURFACE_TERRAINS_H
#define SURFACE_TERRAINS_H

#define TERRAINSOUND        0xFF000000
#define PARTICLES           0x0F000000
#define CAMANGLE            0x00F00000
#define CAMFLAGS            0x000F0000
#define SPECIALPROPERTY     0x0000FF00
#define PROPERTYFLAGS       0x000000FF

#define SOUND_TERRAIN_DEFAULT 0 // e g  air
#define SOUND_TERRAIN_GRASS 1
#define SOUND_TERRAIN_WATER 2
#define SOUND_TERRAIN_STONE 3
#define SOUND_TERRAIN_SPOOKY 4// squeaky floor
#define SOUND_TERRAIN_SNOW 5
#define SOUND_TERRAIN_ICE 6
#define SOUND_TERRAIN_SAND 7
#define SOUND_TERRAIN_WOOD 8
#define SOUND_TERRAIN_METAL 9
#define SOUND_TERRAIN_GLAS 10

#define PARTICLE_TERRAIN_NONE 0
#define PARTICLE_TERRAIN_NONE1 1
#define PARTICLE_TERRAIN_WATER 2
#define PARTICLE_TERRAIN_NONE2 3
#define PARTICLE_TERRAIN_ROCKS 4
#define PARTICLE_TERRAIN_SNOW 5
#define PARTICLE_TERRAIN_NONE4 6
#define PARTICLE_TERRAIN_SAND 7
#define PARTICLE_TERRAIN_LEAFS 8
#define PARTICLE_TERRAIN_ACTIVATENVIRONMENT 9
#define PARTICLE_TERRAIN_SPARKLES 10

#define SPECFLAG_NORMAL                 0
#define SPECFLAG_BURNING                1
#define SPECFLAG_HANGABLE               2
#define SPECFLAG_CAMGETSTUCK            3
#define SPECFLAG_SINKSAND               4
#define SPECFLAG_SLOWDOWN               5
#define SPECFLAG_SLIPPERY               6
#define SPECFLAG_MEGASLIP               7
#define SPECFLAG_CLIMBABLE              8
#define SPECFLAG_DEATH_PLANE            9
#define SPECFLAG_PAINTING               10
#define SPECFLAG_NEW_WATER              11
#define SPECFLAG_NEW_WATER_BOTTOM       12
#define SPECFLAG_SHADOW_VOLUME          13
#define SPECFLAG_SHADOW_VOLUME_BOTTOM   14
#define SPECFLAG_VANISH_CAP_WALLS       15

#define CAMERA_TERRAIN_DEFAULT                      0x0
#define CAMERA_TERRAIN_NOSURFBACK                   0x1
#define CAMERA_TERRAIN_KEEP_IN                      0x2
#define CAMERA_TERRAIN_GOTHROUGH                    0x3
#define CAMERA_TERRAIN_SPECIALCODE                  0x4
#define CAMERA_TERRAIN_SPECIALCODE_SLIDE_COURSE_8   0x0

#define NEWTERRAIN(sound, spec, part, light) \
    (((u16)((sound) & 0xF) << 12) | \
     ((u16)((spec)  & 0xF) <<  8) | \
     ((u16)((part)  & 0xF) <<  4) | \
     ((u16)((light) & 0xF)))
     
#define SURFACETYPE (surf) (surf->type & 0xFF)
#define SURF_TYPE_OBJ_ACTION  0x77
#define SURF_TYPE_OBJ_ACTION2 0x78
#include "config.h"

// Surface Types
#define SURFACE_DEFAULT NEWTERRAIN(0, 0, 0, 0)
#define SURFACE_HANGABLE NEWTERRAIN(SOUND_TERRAIN_SPOOKY, SPECFLAG_HANGABLE, 0, 0)
#define SURFACE_NP_GRASS_WITH_LIGHT NEWTERRAIN(SOUND_TERRAIN_GRASS, 0, 0, 0)
#define SURFACE_S_GRASS_WITH_LIGHT NEWTERRAIN(SOUND_TERRAIN_GRASS, SPECFLAG_MEGASLIP, 0, 0)
#define SURFACE_BURNING NEWTERRAIN(SOUND_TERRAIN_WATER, SPECFLAG_BURNING, 0, 0)
#define SURFACE_NOT_SLIPPERY NEWTERRAIN(SOUND_TERRAIN_STONE, SPECFLAG_CLIMBABLE, 0, 0)
#define SURFACE_MGR_MUSIC NEWTERRAIN(4, 0, 0, 0)
#define SURFACE_NULL                      -1
#define SURFACE_SLOW                       NEWTERRAIN(0, SPECFLAG_SLOWDOWN, 0, 0)
#define SURFACE_NEW_WATER                  NEWTERRAIN(0, SPECFLAG_NEW_WATER, 0, 0)
#define SURFACE_NEW_WATER_BOTTOM           NEWTERRAIN(0, SPECFLAG_NEW_WATER_BOTTOM, 0, 0)
#define SURFACE_NOT_SLIPPERY_DEFAULT       NEWTERRAIN(0, SPECFLAG_CLIMBABLE, 0, 0)
#define SURFACE_WOOD                       NEWTERRAIN(4, 0, 0, 0)
#define SURFACE_WOOD_SLIPPERY              NEWTERRAIN(4, SPECFLAG_SLIPPERY 0, 0)
#define SURFACE_CLIMBABLE_WOOD             NEWTERRAIN(4, SPECFLAG_CLIMBABLE, 0, 0)
#define SURFACE_DEATH_PLANE                NEWTERRAIN(0, SPECFLAG_DEATH_PLANE, 0, 0)
#define SURFACE_CLOSE_CAMERA               0x000B
#define SURFACE_METAL                      NEWTERRAIN(0, 0, 0, 0)
#define SURFACE_WATER                      0x000D
#define SURFACE_FLOWING_WATER              0x000E
#define SURFACE_SAND                       0x000F
#define SURFACE_SLIPPERY_DEFAULT           0x0010
#define SURFACE_HANGABLE_WOOD              0x0011
#define SURFACE_INTANGIBLE                 0x0012
#define SURFACE_VERY_SLIPPERY              0x0013
#define SURFACE_SLIPPERY                   0x0014
#define SURFACE_TTM_VINES                  0x0016
#define SURFACE_STONE                      0x0017
#define SURFACE_NOT_SLIPPERY_SAND          0x0018
#define SURFACE_SLIPPERY_DEFAULT2          0x0019
#define SURFACE_INSTANT_WARP_1B            0x001B
#define SURFACE_INSTANT_WARP_1C            0x001C
#define SURFACE_INSTANT_WARP_1D            0x001D
#define SURFACE_INSTANT_WARP_1E            0x001E
#define SURFACE_SNOW                       0x001F
#define SURFACE_SLIPPERY_SNOW              0x0020
#define SURFACE_SHALLOW_QUICKSAND          0x0021
#define SURFACE_DEEP_QUICKSAND             0x0022
#define SURFACE_INSTANT_QUICKSAND          0x0023
#define SURFACE_DEEP_MOVING_QUICKSAND      0x0024
#define SURFACE_SHALLOW_MOVING_QUICKSAND   0x0025
#define SURFACE_QUICKSAND                  0x0026
#define SURFACE_MOVING_QUICKSAND           0x0027
#define SURFACE_WALL_MISC                  0x0028
#define SURFACE_NOISE_DEFAULT              0x0029
#define SURFACE_NOISE_SLIPPERY             0x002A
#define SURFACE_ICEE                       0x002B
#define SURFACE_HORIZONTAL_WIND            0x002C
#define SURFACE_INSTANT_MOVING_QUICKSAND   0x002D
#define SURFACE_ICE                        0x002E
#define SURFACE_LOOK_UP_WARP               NEWTERRAIN(3, 0, 0, 1)
#define SURFACE_HARD                       0x0030
#define SURFACE_YELLOW_STONE               0x0031
#define SURFACE_WARP                       0x0032
#define SURFACE_TIMER_START                0x0033
#define SURFACE_TIMER_END                  0x0034
#define SURFACE_HARD_SLIPPERY              0x0035
#define SURFACE_HARD_VERY_SLIPPERY         0x0036
#define SURFACE_HARD_NOT_SLIPPERY          0x0037
#define SURFACE_VERTICAL_WIND              0x0038
#define SURFACE_STONE_WITH_LIGHT           0x003B
#define SURFACE_BEACH                      0x003C
#define SURFACE_TERRAIN_CASTLE_TOPS        0x003D
#define SURFACE_NO_LIGHT                   0x003E
#define SURFACE_CASTLE_SAND                0x003F
#define SURFACE_BOSS_FIGHT_CAMERA          0x0065
#define SURFACE_CAMERA_FREE_ROAM           0x0066
#define SURFACE_0067                       0x0067
#define SURFACE_THI3_WALLKICK              0x0068
#define SURFACE_CAMERA_8_DIR               0x0069
#define SURFACE_SHADOW_VOLUME              NEWTERRAIN(0, SPECFLAG_SHADOW_VOLUME, 0, 0)
#define SURFACE_SHADOW_VOLUME_BOTTOM       NEWTERRAIN(0, SPECFLAG_SHADOW_VOLUME, 0, 1)
#define SURFACE_006C                       0x006C
#define SURFACE_006D                       0x006D
#define SURFACE_CAMERA_MIDDLE              0x006E
#define SURFACE_CAMERA_ROTATE_RIGHT        0x006F
#define SURFACE_CAMERA_ROTATE_LEFT         0x0070
#define SURFACE_0071                       0x0071
#define SURFACE_CAMERA_BOUNDARY            0x0072
#define SURFACE_NOISE_VERY_SLIPPERY_73     0x0073
#define SURFACE_NOISE_VERY_SLIPPERY_74     0x0074
#define SURFACE_NOISE_VERY_SLIPPERY        0x0075
#define SURFACE_NO_CAM_COLLISION           0x0076
#define SURFACE_NO_CAM_COLLISION_77        0x0077
#define SURFACE_NO_CAM_COL_VERY_SLIPPERY   0x0078
#define SURFACE_NO_CAM_COL_SLIPPERY        0x0079
#define SURFACE_SWITCH                     0x007A
#define SURFACE_VANISH_CAP_WALLS           NEWTERRAIN(0, SPECFLAG_VANISH_CAP_WALLS, 0, 0)
#define SURFACE_007C                       0x007C
#define SURFACE_007D                       0x007D
#define SURFACE_007E                       0x007E
#define SURFACE_007F                       0x007F
#define SURFACE_0080                       0x0080
#define SURFACE_0081                       0x0081
#define SURFACE_0082                       0x0082
#define SURFACE_0083                       0x0083
#define SURFACE_0084                       0x0084
#define SURFACE_0085                       0x0085
#define SURFACE_0086                       0x0086
#define SURFACE_0087                       0x0087
#define SURFACE_0088                       0x0088
#define SURFACE_0089                       0x0089
#define SURFACE_008A                       0x008A
#define SURFACE_008B                       0x008B
#define SURFACE_008C                       0x008C
#define SURFACE_008D                       0x008D
#define SURFACE_008E                       0x008E
#define SURFACE_008F                       0x008F
#define SURFACE_0090                       0x0090
#define SURFACE_0091                       0x0091
#define SURFACE_0092                       0x0092
#define SURFACE_0093                       0x0093
#define SURFACE_0094                       0x0094
#define SURFACE_0095                       0x0095
#define SURFACE_0096                       0x0096
#define SURFACE_0097                       0x0097
#define SURFACE_0098                       0x0098
#define SURFACE_0099                       0x0099
#define SURFACE_009A                       0x009A
#define SURFACE_009B                       0x009B
#define SURFACE_009C                       0x009C
#define SURFACE_009D                       0x009D
#define SURFACE_009E                       0x009E
#define SURFACE_009F                       0x009F
#define SURFACE_00A0                       0x00A0
#define SURFACE_00A1                       0x00A1
#define SURFACE_00A2                       0x00A2
#define SURFACE_00A3                       0x00A3
#define SURFACE_00A4                       0x00A4
#define SURFACE_00A5                       0x00A5
// Definimos una macro auxiliar para no escribir NEWTERRAIN 100 veces
#define PAINT_ENTRY(id) (NEWTERRAIN(3, SPECFLAG_PAINTING, 0, 0) | (id))

// Pinturas - Wobble
#define SURFACE_PAINTING_WOBBLE_A6         PAINT_ENTRY(0x00A6)
#define SURFACE_PAINTING_WOBBLE_A7         PAINT_ENTRY(0x00A7)
#define SURFACE_PAINTING_WOBBLE_A8         PAINT_ENTRY(0x00A8)
#define SURFACE_PAINTING_WOBBLE_A9         PAINT_ENTRY(0x00A9)
#define SURFACE_PAINTING_WOBBLE_AA         PAINT_ENTRY(0x00AA)
#define SURFACE_PAINTING_WOBBLE_AB         PAINT_ENTRY(0x00AB)
#define SURFACE_PAINTING_WOBBLE_AC         PAINT_ENTRY(0x00AC)
#define SURFACE_PAINTING_WOBBLE_AD         PAINT_ENTRY(0x00AD)
#define SURFACE_PAINTING_WOBBLE_AE         PAINT_ENTRY(0x00AE)
#define SURFACE_PAINTING_WOBBLE_AF         PAINT_ENTRY(0x00AF)
#define SURFACE_PAINTING_WOBBLE_B0         PAINT_ENTRY(0x00B0)
#define SURFACE_PAINTING_WOBBLE_B1         PAINT_ENTRY(0x00B1)
#define SURFACE_PAINTING_WOBBLE_B2         PAINT_ENTRY(0x00B2)
#define SURFACE_PAINTING_WOBBLE_B3         PAINT_ENTRY(0x00B3)
#define SURFACE_PAINTING_WOBBLE_B4         PAINT_ENTRY(0x00B4)
#define SURFACE_PAINTING_WOBBLE_B5         PAINT_ENTRY(0x00B5)
#define SURFACE_PAINTING_WOBBLE_B6         PAINT_ENTRY(0x00B6)
#define SURFACE_PAINTING_WOBBLE_B7         PAINT_ENTRY(0x00B7)
#define SURFACE_PAINTING_WOBBLE_B8         PAINT_ENTRY(0x00B8)
#define SURFACE_PAINTING_WOBBLE_B9         PAINT_ENTRY(0x00B9)
#define SURFACE_PAINTING_WOBBLE_BA         PAINT_ENTRY(0x00BA)
#define SURFACE_PAINTING_WOBBLE_BB         PAINT_ENTRY(0x00BB)
#define SURFACE_PAINTING_WOBBLE_BC         PAINT_ENTRY(0x00BC)
#define SURFACE_PAINTING_WOBBLE_BD         PAINT_ENTRY(0x00BD)
#define SURFACE_PAINTING_WOBBLE_BE         PAINT_ENTRY(0x00BE)
#define SURFACE_PAINTING_WOBBLE_BF         PAINT_ENTRY(0x00BF)
#define SURFACE_PAINTING_WOBBLE_C0         PAINT_ENTRY(0x00C0)
#define SURFACE_PAINTING_WOBBLE_C1         PAINT_ENTRY(0x00C1)
#define SURFACE_PAINTING_WOBBLE_C2         PAINT_ENTRY(0x00C2)
#define SURFACE_PAINTING_WOBBLE_C3         PAINT_ENTRY(0x00C3)
#define SURFACE_PAINTING_WOBBLE_C4         PAINT_ENTRY(0x00C4)
#define SURFACE_PAINTING_WOBBLE_C5         PAINT_ENTRY(0x00C5)
#define SURFACE_PAINTING_WOBBLE_C6         PAINT_ENTRY(0x00C6)
#define SURFACE_PAINTING_WOBBLE_C7         PAINT_ENTRY(0x00C7)
#define SURFACE_PAINTING_WOBBLE_C8         PAINT_ENTRY(0x00C8)
#define SURFACE_PAINTING_WOBBLE_C9         PAINT_ENTRY(0x00C9)
#define SURFACE_PAINTING_WOBBLE_CA         PAINT_ENTRY(0x00CA)
#define SURFACE_PAINTING_WOBBLE_CB         PAINT_ENTRY(0x00CB)
#define SURFACE_PAINTING_WOBBLE_CC         PAINT_ENTRY(0x00CC)
#define SURFACE_PAINTING_WOBBLE_CD         PAINT_ENTRY(0x00CD)
#define SURFACE_PAINTING_WOBBLE_CE         PAINT_ENTRY(0x00CE)
#define SURFACE_PAINTING_WOBBLE_CF         PAINT_ENTRY(0x00CF)
#define SURFACE_PAINTING_WOBBLE_D0         PAINT_ENTRY(0x00D0)
#define SURFACE_PAINTING_WOBBLE_D1         PAINT_ENTRY(0x00D1)
#define SURFACE_PAINTING_WOBBLE_D2         PAINT_ENTRY(0x00D2)

// Pinturas - Warp
#define SURFACE_PAINTING_WARP_D3           PAINT_ENTRY(0x00D3)
#define SURFACE_PAINTING_WARP_D4           PAINT_ENTRY(0x00D4)
#define SURFACE_PAINTING_WARP_D5           PAINT_ENTRY(0x00D5)
#define SURFACE_PAINTING_WARP_D6           PAINT_ENTRY(0x00D6)
#define SURFACE_PAINTING_WARP_D7           PAINT_ENTRY(0x00D7)
#define SURFACE_PAINTING_WARP_D8           PAINT_ENTRY(0x00D8)
#define SURFACE_PAINTING_WARP_D9           PAINT_ENTRY(0x00D9)
#define SURFACE_PAINTING_WARP_DA           PAINT_ENTRY(0x00DA)
#define SURFACE_PAINTING_WARP_DB           PAINT_ENTRY(0x00DB)
#define SURFACE_PAINTING_WARP_DC           PAINT_ENTRY(0x00DC)
#define SURFACE_PAINTING_WARP_DD           PAINT_ENTRY(0x00DD)
#define SURFACE_PAINTING_WARP_DE           PAINT_ENTRY(0x00DE)
#define SURFACE_PAINTING_WARP_DF           PAINT_ENTRY(0x00DF)
#define SURFACE_PAINTING_WARP_E0           PAINT_ENTRY(0x00E0)
#define SURFACE_PAINTING_WARP_E1           PAINT_ENTRY(0x00E1)
#define SURFACE_PAINTING_WARP_E2           PAINT_ENTRY(0x00E2)
#define SURFACE_PAINTING_WARP_E3           PAINT_ENTRY(0x00E3)
#define SURFACE_PAINTING_WARP_E4           PAINT_ENTRY(0x00E4)
#define SURFACE_PAINTING_WARP_E5           PAINT_ENTRY(0x00E5)
#define SURFACE_PAINTING_WARP_E6           PAINT_ENTRY(0x00E6)
#define SURFACE_PAINTING_WARP_E7           PAINT_ENTRY(0x00E7)
#define SURFACE_PAINTING_WARP_E8           PAINT_ENTRY(0x00E8)
#define SURFACE_PAINTING_WARP_E9           PAINT_ENTRY(0x00E9)
#define SURFACE_PAINTING_WARP_EA           PAINT_ENTRY(0x00EA)
#define SURFACE_PAINTING_WARP_EB           PAINT_ENTRY(0x00EB)
#define SURFACE_PAINTING_WARP_EC           PAINT_ENTRY(0x00EC)
#define SURFACE_PAINTING_WARP_ED           PAINT_ENTRY(0x00ED)
#define SURFACE_PAINTING_WARP_EE           PAINT_ENTRY(0x00EE)
#define SURFACE_PAINTING_WARP_EF           PAINT_ENTRY(0x00EF)
#define SURFACE_PAINTING_WARP_F0           PAINT_ENTRY(0x00F0)
#define SURFACE_PAINTING_WARP_F1           PAINT_ENTRY(0x00F1)
#define SURFACE_PAINTING_WARP_F2           PAINT_ENTRY(0x00F2)
#define SURFACE_PAINTING_WARP_F3           PAINT_ENTRY(0x00F3)
#define SURFACE_TTC_PAINTING_1             PAINT_ENTRY(0x00F4)
#define SURFACE_TTC_PAINTING_2             PAINT_ENTRY(0x00F5)
#define SURFACE_TTC_PAINTING_3             PAINT_ENTRY(0x00F6)
#define SURFACE_PAINTING_WARP_F7           PAINT_ENTRY(0x00F7)
#define SURFACE_PAINTING_WARP_F8           PAINT_ENTRY(0x00F8)
#define SURFACE_PAINTING_WARP_F9           PAINT_ENTRY(0x00F9)
#define SURFACE_PAINTING_WARP_FA           PAINT_ENTRY(0x00FA)
#define SURFACE_PAINTING_WARP_FB           PAINT_ENTRY(0x00FB)
#define SURFACE_PAINTING_WARP_FC           PAINT_ENTRY(0x00FC)
#define SURFACE_WOBBLING_WARP              PAINT_ENTRY(0x00FD)
#define SURFACE_00FE                       0x00FE
#define SURFACE_TRAPDOOR                   0x00FF

#define SURFACE_IS_NEW_WATER(cmd)               (((cmd) == SURFACE_NEW_WATER) || ((cmd) == SURFACE_NEW_WATER_BOTTOM))
// Extrae los bits 8-11 y compara con los IDs de volumen de sombra
#define SURFACE_IS_SHADOW_VOLUME(cmd) \
    ((((cmd) >> 8) & 0xF) == SPECFLAG_SHADOW_VOLUME || \
     (((cmd) >> 8) & 0xF) == SPECFLAG_SHADOW_VOLUME_BOTTOM)
#define SURFACE_IS_QUICKSAND(cmd)               ((((cmd) >= SURFACE_SHALLOW_QUICKSAND) && ((cmd) <= SURFACE_MOVING_QUICKSAND)) || ((cmd) == SURFACE_INSTANT_MOVING_QUICKSAND))
#define SURFACE_IS_NOT_HARD(cmd)                (((cmd) != SURFACE_HARD) && !((cmd) >= SURFACE_HARD_SLIPPERY && ((cmd) <= SURFACE_HARD_NOT_SLIPPERY)))
#define SURFACE_IS_PAINTING_WOBBLE(cmd)         (((cmd) >= SURFACE_PAINTING_WOBBLE_A6) && ((cmd) <= SURFACE_PAINTING_WOBBLE_D2))
#define SURFACE_IS_PAINTING_WOBBLE_LEFT(cmd)    ((((cmd) - SURFACE_PAINTING_WOBBLE_A6) % 3) == 0)
#define SURFACE_IS_PAINTING_WOBBLE_MIDDLE(cmd)  ((((cmd) - SURFACE_PAINTING_WOBBLE_A7) % 3) == 0)
#define SURFACE_IS_PAINTING_WOBBLE_RIGHT(cmd)   ((((cmd) - SURFACE_PAINTING_WOBBLE_A8) % 3) == 0)
#define SURFACE_IS_PAINTING_WARP(cmd)           (((cmd) >= SURFACE_PAINTING_WARP_D3) && ((cmd) < SURFACE_WOBBLING_WARP)) // skips SURFACE_WOBBLING_WARP
#define SURFACE_IS_PAINTING_WARP_LEFT(cmd)      ((((cmd) - SURFACE_PAINTING_WARP_D3  ) % 3) == 0)
#define SURFACE_IS_PAINTING_WARP_MIDDLE(cmd)    ((((cmd) - SURFACE_PAINTING_WARP_D4  ) % 3) == 0)
#define SURFACE_IS_PAINTING_WARP_RIGHT(cmd)     ((((cmd) - SURFACE_PAINTING_WARP_D5  ) % 3) == 0)
#define SURFACE_IS_INSTANT_WARP(cmd)            (((cmd) >= SURFACE_INSTANT_WARP_1B) && ((cmd) <= SURFACE_INSTANT_WARP_1E))
#define SURFACE_IS_WARP(cmd)                    (((cmd) == SURFACE_LOOK_UP_WARP) || ((cmd) == SURFACE_WOBBLING_WARP) || SURFACE_IS_PAINTING_WARP(cmd) || SURFACE_IS_INSTANT_WARP(cmd))
#define SURFACE_IS_UNSAFE(cmd)                  (((cmd) == SURFACE_BURNING) || SURFACE_IS_QUICKSAND(cmd) || SURFACE_IS_WARP(cmd))

// Extrae la propiedad especial (bits 8-11)
#define GET_SURFACE_PROP(surf)  (((surf)->type >> 8) & 0xF)

#define IS_SURFACE_HANGABLE(surf) \
    ((surf) != NULL && GET_SURFACE_PROP(surf) == SPECFLAG_HANGABLE)

#define IS_SURFACE_SLOWDOWN(surf) \
    ((surf) != NULL && GET_SURFACE_PROP(surf) == SPECFLAG_SLOWDOWN)

#define IS_SURFACE_BURNING(surf) \
    ((surf) != NULL && GET_SURFACE_PROP(surf) == SPECFLAG_BURNING)

#define GET_SURFACE_SOUND(surf) (((surf)->type >> 12) & 0xF)
enum SurfaceClass {
    SURFACE_CLASS_DEFAULT,
    SURFACE_CLASS_VERY_SLIPPERY = 0x0013,
    SURFACE_CLASS_SLIPPERY,
    SURFACE_CLASS_NOT_SLIPPERY
};

enum SurfaceFlags {
    SURFACE_FLAGS_NONE            = (0 << 0), // 0x0000
    SURFACE_FLAG_DYNAMIC          = (1 << 0), // 0x0001
    SURFACE_FLAG_NO_CAM_COLLISION = (1 << 1), // 0x0002
};

// These are effectively unique "surface" types like those defined higher
// And they are used as collision commands to load certain functions
enum TerrainLoadCmd {
    TERRAIN_LOAD_VERTICES = 0x40, // Begins vertices list for collision triangles
    TERRAIN_LOAD_CONTINUE,        // Stop loading vertices but continues to load other collision commands
    TERRAIN_LOAD_END,             // End the collision list
    TERRAIN_LOAD_OBJECTS,         // Loads in certain objects for level start
    TERRAIN_LOAD_ENVIRONMENT      // Loads water/HMC gas
};

#define TERRAIN_LOAD_IS_SURFACE_TYPE_LOW(cmd)  (cmd <  0x40)
#define TERRAIN_LOAD_IS_SURFACE_TYPE_HIGH(cmd) (cmd >= 0x65)

// Terrain types defined by the level script command terrain_type (cmd_31)
enum TerrainType {
    TERRAIN_GRASS,
    TERRAIN_STONE,
    TERRAIN_SNOW,
    TERRAIN_SAND,
    TERRAIN_SPOOKY,
    TERRAIN_WATER,
    TERRAIN_SLIDE,
    TERRAIN_MASK = 0x7
};

// These collision commands are unique "surface" types like those defined higher

// Collision Data Routine Initiate
#define COL_INIT() TERRAIN_LOAD_VERTICES

// Collision Vertices Read Initiate
#define COL_VERTEX_INIT(vtxNum) vtxNum

// Collision Vertex
#define COL_VERTEX(x, y, z) x, y, z

// Collision Tris Initiate
#define COL_TRI_INIT(surfType, triNum) surfType, triNum

// Collision Tri
#ifdef ALL_SURFACES_HAVE_FORCE
#define COL_TRI(v1, v2, v3) v1, v2, v3, 0
#else
#define COL_TRI(v1, v2, v3) v1, v2, v3
#endif

// Collision Tri With Special Params
#define COL_TRI_SPECIAL(v1, v2, v3, param) v1, v2, v3, param

// Collision Tris Stop Loading
#define COL_TRI_STOP() TERRAIN_LOAD_CONTINUE

// End Collision Data
#define COL_END() TERRAIN_LOAD_END

// Special Object Initiate
#define COL_SPECIAL_INIT(num) TERRAIN_LOAD_OBJECTS, num

// Water Boxes Initiate
#define COL_WATER_BOX_INIT(num) TERRAIN_LOAD_ENVIRONMENT, num

// Water Box
#define COL_WATER_BOX(id, x1, z1, x2, z2, y) id, x1, z1, x2, z2, y

#endif // SURFACE_TERRAINS_H
