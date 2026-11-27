#include <PR/ultratypes.h>

#include "area.h"
#include "engine/math_util.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "main.h"
#include "memory.h"
#include "print.h"
#include "rendering_graph_node.h"
#include "shadow.h"
#include "sm64.h"
#include "game_init.h"
#include "puppyprint.h"
#include "debug_box.h"
#include "level_update.h"
#include "behavior_data.h"
#include "engine/behavior_script.h"
#include "obj_behaviors_2.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "string.h"
#include "color_presets.h"
#include "engine/graph_node.h"
#include "engine/surface_collision.h"
#include "config.h"
#include "config/config_world.h"
#include <stdio.h>
#include <point_lights.h>
#include "save_file.h"
float current_aspect_ratio;
/**
 * This file contains the code that processes the scene graph for rendering.
 * The scene graph is responsible for drawing everything except the HUD / text boxes.
 * First the root of the scene graph is processed when geo_process_root
 * is called from level_script.c. The rest of the tree is traversed recursively
 * using the function geo_process_node_and_siblings, which switches over all
 * geo node types and calls a specialized function accordingly.
 * The types are defined in engine/graph_node.h
 *
 * The scene graph typically looks like:
 * - Root (viewport)
 *  - Master list
 *   - Ortho projection
 *    - Background (skybox)
 *  - Master list
 *   - Perspective
 *    - Camera
 *     - <area-specific display lists>
 *     - Object parent
 *      - <group with 240 object nodes>
 *  - Master list
 *   - Script node (Cannon overlay)
 *
 */

s16 gMatStackIndex;
ALIGNED16 Mat4 gMatStack[32];
ALIGNED16 Mtx *gMatStackFixed[32];
f32 sAspectRatio;

/**
 * Animation nodes have state in global variables, so this struct captures
 * the animation state so a 'context switch' can be made when rendering the
 * held object.
 */
struct GeoAnimState {
    /*0x00*/ u8 type;
    /*0x01*/ u8 enabled;
    /*0x02*/ s16 frame;
    /*0x04*/ f32 translationMultiplier;
    /*0x08*/ u16 *attribute;
    /*0x0C*/ s16 *data;
};

// For some reason, this is a GeoAnimState struct, but the current state consists
// of separate global variables. It won't match EU otherwise.
struct GeoAnimState gGeoTempState;

u8 gCurrAnimType;
u8 gCurrAnimEnabled;
s16 gCurrAnimFrame;
f32 gCurrAnimTranslationMultiplier;
u16 *gCurrAnimAttribute;
s16 *gCurrAnimData;

struct AllocOnlyPool *gDisplayListHeap;

struct RenderModeContainer {
    u32 modes[LAYER_COUNT];
};

/* Rendermode settings for cycle 1 for all 8 or 13 layers. */
struct RenderModeContainer renderModeTable_1Cycle[2] = { { {
        G_RM_OPA_SURF,                      // LAYER_FORCE
        G_RM_AA_OPA_SURF,                   // LAYER_OPAQUE
        G_RM_AA_OPA_SURF,                   // LAYER_OPAQUE_INTER
        G_RM_AA_OPA_SURF,                   // LAYER_OPAQUE_DECAL
        G_RM_AA_TEX_EDGE,                   // LAYER_ALPHA
#if SILHOUETTE
        G_RM_AA_TEX_EDGE | ZMODE_DEC,       // LAYER_ALPHA_DECAL
        G_RM_AA_OPA_SURF,                   // LAYER_SILHOUETTE_OPAQUE
        G_RM_AA_TEX_EDGE,                   // LAYER_SILHOUETTE_ALPHA
        G_RM_AA_OPA_SURF,                   // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
        G_RM_AA_TEX_EDGE,                   // LAYER_OCCLUDE_SILHOUETTE_ALPHA
#endif
        G_RM_AA_XLU_SURF,                   // LAYER_TRANSPARENT_DECAL
        G_RM_AA_XLU_SURF,                   // LAYER_TRANSPARENT
        G_RM_AA_XLU_SURF,                   // LAYER_TRANSPARENT_INTER
    } },
    { {
        /* z-buffered */
        G_RM_ZB_OPA_SURF,                   // LAYER_FORCE
        G_RM_AA_ZB_OPA_SURF,                // LAYER_OPAQUE
        G_RM_AA_ZB_OPA_INTER,               // LAYER_OPAQUE_INTER
        G_RM_AA_ZB_OPA_DECAL,               // LAYER_OPAQUE_DECAL
        G_RM_AA_ZB_TEX_EDGE,                // LAYER_ALPHA
#if SILHOUETTE
        G_RM_AA_ZB_TEX_EDGE | ZMODE_DEC,    // LAYER_ALPHA_DECAL
        G_RM_AA_ZB_OPA_SURF,                // LAYER_SILHOUETTE_OPAQUE
        G_RM_AA_ZB_TEX_EDGE,                // LAYER_SILHOUETTE_ALPHA
        G_RM_AA_ZB_OPA_SURF,                // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
        G_RM_AA_ZB_TEX_EDGE,                // LAYER_OCCLUDE_SILHOUETTE_ALPHA
#endif
        G_RM_AA_ZB_XLU_DECAL,               // LAYER_TRANSPARENT_DECAL
        G_RM_AA_ZB_XLU_SURF,                // LAYER_TRANSPARENT
        G_RM_AA_ZB_XLU_INTER,               // LAYER_TRANSPARENT_INTER
    } } };

/* Rendermode settings for cycle 2 for all 13 layers. */
struct RenderModeContainer renderModeTable_2Cycle[2] = { { {
        G_RM_OPA_SURF2,                     // LAYER_FORCE
        G_RM_AA_OPA_SURF2,                  // LAYER_OPAQUE
        G_RM_AA_OPA_SURF2,                  // LAYER_OPAQUE_INTER
        G_RM_AA_OPA_SURF2,                  // LAYER_OPAQUE_DECAL
        G_RM_AA_TEX_EDGE2,                  // LAYER_ALPHA
#if SILHOUETTE
        G_RM_AA_TEX_EDGE2 | ZMODE_DEC,      // LAYER_ALPHA_DECAL
        G_RM_AA_OPA_SURF2,                  // LAYER_SILHOUETTE_OPAQUE
        G_RM_AA_TEX_EDGE2,                  // LAYER_SILHOUETTE_ALPHA
        G_RM_AA_OPA_SURF2,                  // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
        G_RM_AA_TEX_EDGE2,                  // LAYER_OCCLUDE_SILHOUETTE_ALPHA
#endif
        G_RM_AA_XLU_SURF2,                  // LAYER_TRANSPARENT_DECAL
        G_RM_AA_XLU_SURF2,                  // LAYER_TRANSPARENT
        G_RM_AA_XLU_SURF2,                  // LAYER_TRANSPARENT_INTER
    } },
    { {
        /* z-buffered */
        G_RM_ZB_OPA_SURF2,                  // LAYER_FORCE
        G_RM_AA_ZB_OPA_SURF2,               // LAYER_OPAQUE
        G_RM_AA_ZB_OPA_INTER2,              // LAYER_OPAQUE_INTER
        G_RM_AA_ZB_OPA_DECAL2,              // LAYER_OPAQUE_DECAL
        G_RM_AA_ZB_TEX_EDGE2,               // LAYER_ALPHA
#if SILHOUETTE
        G_RM_AA_ZB_TEX_EDGE2 | ZMODE_DEC,   // LAYER_ALPHA_DECAL
        G_RM_AA_ZB_OPA_SURF2,               // LAYER_SILHOUETTE_OPAQUE
        G_RM_AA_ZB_TEX_EDGE2,               // LAYER_SILHOUETTE_ALPHA
        G_RM_AA_ZB_OPA_SURF2,               // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
        G_RM_AA_ZB_TEX_EDGE2,               // LAYER_OCCLUDE_SILHOUETTE_ALPHA
#endif
        G_RM_AA_ZB_XLU_DECAL2,              // LAYER_TRANSPARENT_DECAL
        G_RM_AA_ZB_XLU_SURF2,               // LAYER_TRANSPARENT
        G_RM_AA_ZB_XLU_INTER2,              // LAYER_TRANSPARENT_INTER
    } } };

ALIGNED16 struct GraphNodeRoot *gCurGraphNodeRoot = NULL;
ALIGNED16 struct GraphNodeMasterList *gCurGraphNodeMasterList = NULL;
ALIGNED16 struct GraphNodePerspective *gCurGraphNodeCamFrustum = NULL;
ALIGNED16 struct GraphNodeCamera *gCurGraphNodeCamera = NULL;
ALIGNED16 struct GraphNodeObject *gCurGraphNodeObject = NULL;
ALIGNED16 struct GraphNodeHeldObject *gCurGraphNodeHeldObject = NULL;
u16 gAreaUpdateCounter = 0;
LookAt* gCurLookAt;

static ALWAYS_INLINE float nul_without_loop(float a, float b) {
    float ret;
    __asm__("nul.s %0, %1, %2" : "=f"(ret) : "f"(a), "f"(b));
    return ret;
}

static ALWAYS_INLINE void swl(void *addr, s32 val, const int offset) {
    __asm__("swl %1, %2(%0)" : : "g"(addr), "g"(val), "I"(offset));
}

#if SILHOUETTE
// AA_EN        Enable anti aliasing (not actually used for AA in this case).
// IM_RD        Enable reading coverage value.
// CLR_ON_CVG   Don't change the color unless coverage overflows. This helps prevent triangle overlap.
// CVG_DST_WRAP Wrap the coverage value on overflow.
// CVG_X_ALPHA  Coverage and alpha will be multiplied and both will be the same. This makes texture alpha work (eg. Wing Cap wings).
// FORCE_BL     Force Blending.
#define SIL_CVG_THRESHOLD    0x3F // 32..255, 63 seems to give best results
#define SCHWA (AA_EN | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | CVG_X_ALPHA | FORCE_BL)
static const Gfx dl_silhouette_begin[] = {
    gsDPPipeSync(),
    // Set the render mode for the silhouette so that it gets its color and alpha from the fog register.
    gsDPSetRenderMode((SCHWA | GBL_c1(G_BL_CLR_FOG, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA)),
                      (SCHWA | GBL_c2(G_BL_CLR_FOG, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA))),
    // Set the silhouette's color & alpha.
    gsDPSetFogColor(0, 0, 0, SILHOUETTE),
    // Hacky way to prevent triangle overlap. 32..255. 63 seems to give best results.
    gsDPSetEnvColor(0, 0, 0, 0x3F),
    gsSPEndDisplayList(),
};

static const Gfx dl_silhouette_end[] = {
    gsDPPipeSync(),
    gsDPSetFogColor(  0,   0,   0, 255), // Reset fog color & alpha
    gsDPSetEnvColor(255, 255, 255, 255), // Reset env color & alpha
    gsSPEndDisplayList(),
};
#undef SCHWA
#endif

struct RenderPhase {
    u8 startLayer;
    u8 endLayer;
#ifdef OBJECTS_REJ
    u8 ucode;
#endif
};

//                                               startLayer                      endLayer                        ucode
static struct RenderPhase sRenderPhases[] = {
#ifdef OBJECTS_REJ
 #if SILHOUETTE
    // Silhouette, .rej
    /* RENDER_PHASE_ZEX_BEFORE_SILHOUETTE   */ { LAYER_FIRST,                    LAYER_LAST_BEFORE_SILHOUETTE,   GRAPH_NODE_UCODE_DEFAULT },
    /* RENDER_PHASE_REJ_ZB                  */ { LAYER_ZB_FIRST,                 LAYER_LAST_BEFORE_SILHOUETTE,   GRAPH_NODE_UCODE_REJ     },
    /* RENDER_PHASE_REJ_SILHOUETTE          */ { LAYER_SILHOUETTE_FIRST,         LAYER_SILHOUETTE_LAST,          GRAPH_NODE_UCODE_REJ     },
    /* RENDER_PHASE_REJ_NON_SILHOUETTE      */ { LAYER_SILHOUETTE_FIRST,         LAYER_SILHOUETTE_LAST,          GRAPH_NODE_UCODE_REJ     },
    /* RENDER_PHASE_REJ_OCCLUDE_SILHOUETTE  */ { LAYER_OCCLUDE_SILHOUETTE_FIRST, LAYER_OCCLUDE_SILHOUETTE_LAST,  GRAPH_NODE_UCODE_REJ     },
    /* RENDER_PHASE_ZEX_AFTER_SILHOUETTE    */ { LAYER_OCCLUDE_SILHOUETTE_FIRST, LAYER_LAST,                     GRAPH_NODE_UCODE_DEFAULT },
    /* RENDER_PHASE_REJ_NON_ZB              */ { LAYER_NON_ZB_FIRST,             LAYER_LAST,                     GRAPH_NODE_UCODE_REJ     },
 #else
    // No silhouette, .rej
    /* RENDER_PHASE_ZEX_BG                  */ { LAYER_FIRST,                    LAYER_FIRST,                    GRAPH_NODE_UCODE_DEFAULT },
    /* RENDER_PHASE_REJ_ZB                  */ { LAYER_ZB_FIRST,                 LAYER_ZB_LAST,                  GRAPH_NODE_UCODE_REJ     },
    /* RENDER_PHASE_ZEX_ALL                 */ { LAYER_ZB_FIRST,                 LAYER_LAST,                     GRAPH_NODE_UCODE_DEFAULT },
    /* RENDER_PHASE_REJ_NON_ZB              */ { LAYER_NON_ZB_FIRST,             LAYER_LAST,                     GRAPH_NODE_UCODE_REJ     },
 #endif
#else
 #if SILHOUETTE
    // Silhouette, no .rej
    /* RENDER_PHASE_ZEX_BEFORE_SILHOUETTE   */ { LAYER_FIRST,                    LAYER_LAST_BEFORE_SILHOUETTE    },
    /* RENDER_PHASE_ZEX_SILHOUETTE          */ { LAYER_SILHOUETTE_FIRST,         LAYER_SILHOUETTE_LAST           },
    /* RENDER_PHASE_ZEX_NON_SILHOUETTE      */ { LAYER_SILHOUETTE_FIRST,         LAYER_SILHOUETTE_LAST           },
    /* RENDER_PHASE_ZEX_OCCLUDE_SILHOUETTE  */ { LAYER_OCCLUDE_SILHOUETTE_FIRST, LAYER_OCCLUDE_SILHOUETTE_LAST   },
    /* RENDER_PHASE_ZEX_AFTER_SILHOUETTE    */ { LAYER_OCCLUDE_SILHOUETTE_FIRST, LAYER_LAST                      },
 #else
    // No silhouette, no .rej
    /* RENDER_PHASE_ZEX_ALL                 */ { LAYER_FIRST,                    LAYER_LAST                      },
 #endif
#endif
};

extern const Gfx init_rsp[];

#ifdef OBJECTS_REJ
void switch_ucode(s32 ucode) {
    // Set the ucode and RCP settings
    switch (ucode) {
        default: // GRAPH_NODE_UCODE_DEFAULT
        case GRAPH_NODE_UCODE_DEFAULT:
            gSPLoadUcodeL(gDisplayListHead++, gspF3DZEX2_PosLight_fifo); // F3DZEX2_PosLight
            // Reload the necessary RSP settings
            gSPDisplayList(gDisplayListHead++, init_rsp);
            break;
        case GRAPH_NODE_UCODE_REJ:
            // Use .rej Microcode, skip sub-pixel processing on console
            if (gIsConsole) {
                gSPLoadUcodeL(gDisplayListHead++, gspF3DLX2_Rej_fifo); // F3DLX2_Rej
            } else {
                gSPLoadUcodeL(gDisplayListHead++, gspF3DEX2_Rej_fifo); // F3DEX2_Rej
            }
            // Reload the necessary RSP settings
            gSPDisplayList(gDisplayListHead++, init_rsp);
            // Set the clip ratio (see init_rsp)
            gSPClipRatio(gDisplayListHead++, FRUSTRATIO_2);
            break;
    }
}
#endif

#define UPPER_FIXED(x) ((int)((unsigned int)((x) * 0x10000) >> 16))
#define LOWER_FIXED(x) ((int)((unsigned int)((x) * 0x10000) & 0xFFFF))

// Fixed-point identity matrix with the inverse of world scale
Mtx identityMatrixWorldScale = {{
    {UPPER_FIXED(1.0f / WORLD_SCALE) << 16, 0x00000000,
     UPPER_FIXED(1.0f / WORLD_SCALE) <<  0, 0x00000000},
    {0x00000000,                            UPPER_FIXED(1.0f / WORLD_SCALE) << 16,
     0x00000000,                            UPPER_FIXED(1.0f)               <<  0},
    {LOWER_FIXED(1.0f / WORLD_SCALE) << 16, 0x00000000,
     LOWER_FIXED(1.0f / WORLD_SCALE) <<  0, 0x00000000},
    {0x00000000,                            LOWER_FIXED(1.0f / WORLD_SCALE) << 16,
     0x00000000,                            LOWER_FIXED(1.0f)               <<  0}
}};

/**
 * Process a master list node. This has been modified, so now it runs twice, for each microcode.
 * It iterates through the first 5 layers of if the first index using F3DLX2.Rej, then it switches
 * to F3DZEX and iterates through all layers, then switches back to F3DLX2.Rej and finishes the last
 * 3. It does this, because layers 5-7 are non zbuffered, and just doing 0-7 of ZEX, then 0-7 of REJ
 * would make the ZEX 0-4 render on top of Rej's 5-7.
 */
void geo_process_master_list_sub(struct GraphNodeMasterList *node) {
    struct RenderPhase *renderPhase;
    struct DisplayListNode *currList;
    s32 currLayer     = LAYER_FIRST;
    s32 startLayer    = LAYER_FIRST;
    s32 endLayer      = LAYER_LAST;
    s32 ucode         = GRAPH_NODE_UCODE_DEFAULT;
    s32 phaseIndex    = RENDER_PHASE_FIRST;
    s32 enableZBuffer = (node->node.flags & GRAPH_RENDER_Z_BUFFER) != 0;
    struct RenderModeContainer *mode1List = &renderModeTable_1Cycle[enableZBuffer];
    struct RenderModeContainer *mode2List = &renderModeTable_2Cycle[enableZBuffer];

    // Loop through the render phases
    for (phaseIndex = RENDER_PHASE_FIRST; phaseIndex < RENDER_PHASE_END; phaseIndex++) {
        // Get the render phase information.
        renderPhase = &sRenderPhases[phaseIndex];
        startLayer  = renderPhase->startLayer;
        endLayer    = renderPhase->endLayer;
#ifdef OBJECTS_REJ
        ucode       = renderPhase->ucode;
        // Set the ucode for the current render phase
        switch_ucode(ucode);
        gSPLookAt(gDisplayListHead++, gCurLookAt);
#endif
        if (enableZBuffer) {
            // Enable z buffer.
            gDPPipeSync(gDisplayListHead++);
            gSPSetGeometryMode(gDisplayListHead++, G_ZBUFFER);
        }
        // Iterate through the layers on the current render phase.
        for (currLayer = startLayer; currLayer <= endLayer; currLayer++) {
            // Set 'currList' to the first DisplayListNode on the current layer.
            currList = node->listHeads[ucode][currLayer];
#if defined(DISABLE_AA) || !SILHOUETTE
            // Set the render mode for the current layer.
            gDPSetRenderMode(gDisplayListHead++, mode1List->modes[currLayer],
                                                 mode2List->modes[currLayer]);
#else
            if (phaseIndex == RENDER_PHASE_NON_SILHOUETTE) {
                // To properly cover the silhouette, disable AA.
                // The silhouette model does not have AA due to the hack used to prevent triangle overlap.
                gDPSetRenderMode(gDisplayListHead++, (mode1List->modes[currLayer] & ~IM_RD),
                                                     (mode2List->modes[currLayer] & ~IM_RD));
            } else {
                // Set the render mode for the current dl.
                gDPSetRenderMode(gDisplayListHead++, mode1List->modes[currLayer],
                                                     mode2List->modes[currLayer]);
            }
#endif
            // Iterate through all the displaylists on the current layer.
            while (currList != NULL) {
                // Add the display list's transformation to the master list.
                gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(currList->transform),
                          (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
#if SILHOUETTE
                if (phaseIndex == RENDER_PHASE_SILHOUETTE) {
                    // Add the current display list to the master list, with silhouette F3D.
                    gSPDisplayList(gDisplayListHead++, dl_silhouette_begin);
                    gSPDisplayList(gDisplayListHead++, currList->displayList);
                    gSPDisplayList(gDisplayListHead++, dl_silhouette_end);
                } else {
                    // Add the current display list to the master list.
                    gSPDisplayList(gDisplayListHead++, currList->displayList);
                }
#else
                // Add the current display list to the master list.
                gSPDisplayList(gDisplayListHead++, currList->displayList);
#endif
                // Move to the next DisplayListNode.
                currList = currList->next;
            }
        }
    }

    if (enableZBuffer) {
        // Disable z buffer.
        gDPPipeSync(gDisplayListHead++);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }
#ifdef OBJECTS_REJ
 #if defined(F3DEX_GBI_2) && defined(VISUAL_DEBUG)
    if (hitboxView) render_debug_boxes(DEBUG_UCODE_REJ);
 #endif
    switch_ucode(GRAPH_NODE_UCODE_DEFAULT);
#endif
#ifdef VISUAL_DEBUG
    if ( hitboxView) render_debug_boxes(DEBUG_UCODE_DEFAULT | DEBUG_BOX_CLEAR);
    // Load the world scale identity matrix
    gSPMatrix(gDisplayListHead++, &identityMatrixWorldScale, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    if (surfaceView) visual_surface_loop();
#endif
}

/**
 * Appends the display list to one of the master lists based on the layer
 * parameter. Look at the RenderModeContainer struct to see the corresponding
 * render modes of layers.
 */
void geo_append_display_list(void *displayList, s32 layer) {
    s32 ucode = GRAPH_NODE_UCODE_DEFAULT;
#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, gCurLookAt);
#endif
#if defined(OBJECTS_REJ) || SILHOUETTE
    if (gCurGraphNodeObject != NULL) {
 #ifdef OBJECTS_REJ
        ucode = gCurGraphNodeObject->ucode;
 #endif
 #if SILHOUETTE
        if (gCurGraphNodeObject->node.flags & GRAPH_RENDER_SILHOUETTE) {
            switch (layer) {
                case LAYER_OPAQUE: layer = LAYER_SILHOUETTE_OPAQUE; break;
                case LAYER_ALPHA:  layer = LAYER_SILHOUETTE_ALPHA;  break;
            }
        }
        if (gCurGraphNodeObject->node.flags & GRAPH_RENDER_OCCLUDE_SILHOUETTE) {
            switch (layer) {
                case LAYER_OPAQUE: layer = LAYER_OCCLUDE_SILHOUETTE_OPAQUE; break;
                case LAYER_ALPHA:  layer = LAYER_OCCLUDE_SILHOUETTE_ALPHA;  break;
            }
        }
 #endif // SILHOUETTE
    }
#endif // F3DEX_GBI_2 || SILHOUETTE
    if (gCurGraphNodeMasterList != NULL) {
        struct DisplayListNode *listNode =
            alloc_only_pool_alloc(gDisplayListHeap, sizeof(struct DisplayListNode));

        listNode->transform = gMatStackFixed[gMatStackIndex];
        listNode->displayList = displayList;
        listNode->next = NULL;
        if (gCurGraphNodeMasterList->listHeads[ucode][layer] == NULL) {
            gCurGraphNodeMasterList->listHeads[ucode][layer] = listNode;
        } else {
            gCurGraphNodeMasterList->listTails[ucode][layer]->next = listNode;
        }
        gCurGraphNodeMasterList->listTails[ucode][layer] = listNode;
    }
}

static void inc_mat_stack() {
    // increment a local version of gMatStackIndex to let GCC know not to account for overflow behavior
    s32 LocalIndex = gMatStackIndex + 1;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    mtxf_to_mtx(mtx, gMatStack[LocalIndex]);
    gMatStackFixed[LocalIndex] = mtx;
    gMatStackIndex = LocalIndex;
}

static void append_dl_and_return(struct GraphNodeDisplayList *node) {
    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
    gMatStackIndex--;
}

/**
 * Process the master list node.
 */
void geo_process_master_list(struct GraphNodeMasterList *node) {
    s32 ucode, layer;

    if (gCurGraphNodeMasterList == NULL && node->node.children != NULL) {
        gCurGraphNodeMasterList = node;
        for (ucode = 0; ucode < GRAPH_NODE_NUM_UCODES; ucode++) {
            for (layer = LAYER_FIRST; layer < LAYER_COUNT; layer++) {
                node->listHeads[ucode][layer] = NULL;
            }
        }
        geo_process_node_and_siblings(node->node.children);
        geo_process_master_list_sub(gCurGraphNodeMasterList);
        gCurGraphNodeMasterList = NULL;
    }
}

/**
 * Process an orthographic projection node.
 */
 void geo_process_ortho_projection(struct GraphNodeOrthoProjection *node) {
    if (node->node.children != NULL) {
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
        f32 scale = node->scale / 2.0f;
        f32 left = (gCurGraphNodeRoot->x - gCurGraphNodeRoot->width) * scale;
        f32 right = (gCurGraphNodeRoot->x + gCurGraphNodeRoot->width) * scale;
        f32 top = (gCurGraphNodeRoot->y - gCurGraphNodeRoot->height) * scale;
        f32 bottom = (gCurGraphNodeRoot->y + gCurGraphNodeRoot->height) * scale;

        guOrtho(mtx, left, right, bottom, top, -2.0f, 2.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Process a perspective projection node.
 */
void geo_process_perspective(struct GraphNodePerspective *node) {
    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    if (node->fnNode.node.children != NULL) {
        u16 perspNorm;
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
#ifdef WIDE
        if (gConfig.widescreen && gCurrLevelNum != 0x01){
            sAspectRatio = 16.0f / 9.0f; // 1.775f
            current_aspect_ratio = 1.775f;
        } else {
            sAspectRatio = 4.0f / 3.0f; // 1.33333f
            current_aspect_ratio = 1.33333f;
        }
#else
        sAspectRatio = 4.0f / 3.0f; // 1.33333f
#endif

        guPerspective(mtx, &perspNorm, node->fov, sAspectRatio, node->near / WORLD_SCALE, node->far / WORLD_SCALE, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, perspNorm);

        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

        gCurGraphNodeCamFrustum = node;
        geo_process_node_and_siblings(node->fnNode.node.children);
        gCurGraphNodeCamFrustum = NULL;
    }
}

UNUSED static f32 get_dist_from_camera(Vec3f pos) {
    return -((gCameraTransform[0][2] * pos[0])
           + (gCameraTransform[1][2] * pos[1])
           + (gCameraTransform[2][2] * pos[2])
           +  gCameraTransform[3][2]);
}


/**
 * Process a switch case node. The node's selection function is called
 * if it is 0, and among the node's children, only the selected child is
 * processed next.
 */
void geo_process_switch(struct GraphNodeSwitchCase *node) {
    struct GraphNode *selectedChild = node->fnNode.node.children;
    s32 i;

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    for (i = 0; selectedChild != NULL && node->selectedCase > i; i++) {
        selectedChild = selectedChild->next;
    }
    if (selectedChild != NULL) {
        geo_process_node_and_siblings(selectedChild);
    }
}

extern struct MarioState *gMarioState;

struct SceneLight gPointLights[MAX_POINT_LIGHTS];
s8 gLightDir[3] = {0x00, 0x5A, 0x28};
u8 gOverrideDirectionalLight = FALSE;
u8 gOverrideAmbientLight = FALSE;
u8 gUseGlobalLightAsCamLight = FALSE;
u8 gPointLightCount = 0;
u8 gAreaPointLightCount = 0;
u8 RGBLight[3] = {0xFF, 0xFF, 0xFF};
u8 RGBAmbient[3] = {0x11, 0x11, 0x11};
u8 CamLightCol[3] = {0x3c, 0x3c, 0x3c};
Vec3s gLightPosition;
Lights1* curLight;
Vec3f DirectionalLightPos;
u8 bDirectionalLightAsPoint;    
Lights1 camLight;
u8 LowestCamColor[3] = {5, 5, 5};
u8 LowestColor[3] = {0x0D, 0x13, 0x0E};
u8  gUseCameraLightAsPointLight = FALSE;  // flag: fade activo o no
f32 camLightMinDist             = 0.0f;
f32 camLightMaxDist             = 0.0f;   // distancia máxima del fade (en unidades)
s32 camLightBrightness          = 0;      // reservado (para futura luz posicionada)

/**
 * Gets the square of the distance between two vectors
 * The first vector is of floats, the second is of s16
 * All math operations are done on integers
 */
u32 vec3f_vec3s_dist_sq(Vec3f p1, Vec3s p2)
{
    s32 dx = p2[0] - (s32)p1[0];
    s32 dy = p2[1] - (s32)p1[1];
    s32 dz = p2[2] - (s32)p1[2];
    return (u32)(dx * dx) + (u32)(dy * dy) + (u32)(dz * dz);
}

#include "src/engine/surface_collision.h"
#include <math.h>

int gPointLightCompatibilityMode = 1;
Mat4 *viewMat;

float my_fmax(float a, float b) {
    return (a > b) ? a : b;
}

float my_fmin(float a, float b) {
    return (a < b) ? a : b;
}

Vec3f camera_pos;
/**
 * Creates a displaylist to set the active point lights closest to a given location
 */
Gfx* createPointLightsDl(struct Object *gCurObj) {
    Gfx *pointLightsDlHead, *pointLightsDl;
    struct SceneLight *lights[MAX_POINT_LIGHTS_ACTIVE];
    s32 numLightsPicked = 0;
    f32 distancesSq[MAX_POINT_LIGHTS_ACTIVE];
    s32 maxIndex = 0;
    u8 diffuse[3];
    s8 gOnShadowLightDir[3] = { 0x00, 0x5A, 0x00 };
    f32 currentObjShadowOpacity = 0.0f; 
    s32 LightQuantity = 0;
    s32 currentFloorType = (gCurObj->floor != NULL) ? (s32)gCurObj->floor->type : -1;
    s16 lightID = (currentFloorType != -1) ? (currentFloorType & 0xFF) : -1;

    f32 distanceFade = 1.0f;
    if (gUseCameraLightAsPointLight && camLightMaxDist > 0.0f) {
        f32 dx = camera_pos[0] - gCurObj->header.gfx.pos[0];
        f32 dy = camera_pos[1] - gCurObj->header.gfx.pos[1];
        f32 dz = camera_pos[2] - gCurObj->header.gfx.pos[2];
        f32 distSq = dx * dx + dy * dy + dz * dz;
        f32 dist = sqrtf(distSq);

        if (dist <= camLightMinDist) {
            distanceFade = 1.0f; // 100% brillante dentro de la distancia mínima
        } else if (dist >= camLightMaxDist) {
            distanceFade = 0.0f; // Completamente apagado al rebasar la distancia máxima
        } else {
            // Desvanecimiento suave y progresivo entre el mínimo y el máximo
            distanceFade = 1.0f - ((dist - camLightMinDist) / (camLightMaxDist - camLightMinDist));
        }
        distanceFade = my_fmax(0.0f, my_fmin(1.0f, distanceFade));
    }
    
    struct Surface *shadowSurf = NULL;
    f32 shadowHeight = FLOOR_LOWER_LIMIT;
    gCurObj->oShadowTarget = 0.0f;

    // 1. Detección de volumen de sombra
    shadowHeight = find_shadow_level((s32)gCurObj->oPosX, (s32)gCurObj->oPosY + 150, (s32)gCurObj->oPosZ, &shadowSurf);
    if (!(gCurrLevelNum == LEVEL_LLL && gCurrAreaIndex == 2)) {
        if (shadowSurf != NULL && gCurObj->oPosY < shadowHeight) {
            if ((((shadowSurf->type >> 12) & 0xF) == 0) && (((shadowSurf->type >> 4) & 0xF) == 0)) {
                gCurObj->oShadowTarget = 1.0f; 
            }
            if ((((shadowSurf->type >> 12) & 0xF) == 1)) {
                gCurObj->oShadowTarget = 1.0f; 
            }
        }
    }

    // 2. Detección de Agua (Activa la sombra base)
    f32 waterLevel = find_water_level(gCurObj->oPosX, gCurObj->oPosZ);
    u8 isUnderwater = ((gCurObj->oPosY + 100) < waterLevel);
    if (isUnderwater) gCurObj->oShadowTarget = 1.0f; 

    // 3. Suavizado (Lerp) de la transición de sombra base
    f32 lerpSpeed = 0.07f; 
    if (gCurObj->oShadowLerp < gCurObj->oShadowTarget) 
        gCurObj->oShadowLerp = my_fmin(gCurObj->oShadowTarget, gCurObj->oShadowLerp + lerpSpeed);
    else if (gCurObj->oShadowLerp > gCurObj->oShadowTarget) 
        gCurObj->oShadowLerp = my_fmax(gCurObj->oShadowTarget, gCurObj->oShadowLerp - lerpSpeed);

    currentObjShadowOpacity = gCurObj->oShadowLerp;
    
    // --- LÓGICA DE OSCURIDAD PROFUNDA CON DEGRADADO SUAVE ---
    // Determinamos el objetivo: 1.0 si AMBAS condiciones se cumplen, 0.0 si no.
    f32 deepDarknessTarget = 0.0f;
    if (shadowSurf != NULL && gCurObj->oPosY < shadowHeight && isUnderwater) {
        deepDarknessTarget = 1.0f;
    }

    // Aplicamos lerp a la oscuridad profunda (puedes ajustar 0.05f para más o menos suavidad)
    f32 deepLerpSpeed = 0.05f;
    if (gCurObj->oDeepDarknessLerp < deepDarknessTarget)
        gCurObj->oDeepDarknessLerp = my_fmin(deepDarknessTarget, gCurObj->oDeepDarknessLerp + deepLerpSpeed);
    else if (gCurObj->oDeepDarknessLerp > deepDarknessTarget)
        gCurObj->oDeepDarknessLerp = my_fmax(deepDarknessTarget, gCurObj->oDeepDarknessLerp - deepLerpSpeed);

    // El multiplicador final usa este nuevo lerp. 0.7f es la fuerza de la oscuridad.
    f32 deepDarknessMult = 1.0f - (0.7f * gCurObj->oDeepDarknessLerp); 
    // -------------------------------------------------------

    for (s32 i = 0; i < 3; i++) {
        diffuse[i] = (u8)((f32)RGBLight[i] * (1.0f - currentObjShadowOpacity) + (f32)RGBAmbient[i] * currentObjShadowOpacity);
    }

    Lights1 *WorldLight = (Lights1 *) alloc_display_list(sizeof(Lights1));
    bzero(WorldLight, sizeof(Lights1));

    f32 zoneAtten = 0.0f;
    f32 waterSurfaceY = 500.0f;
    f32 waterBottomY  = -830.0f;

    if (gCurrLevelNum == LEVEL_JRB) {
        zoneAtten = (waterSurfaceY - gCurObj->oPosY) / (waterSurfaceY - waterBottomY);
    } else if (gCurrLevelNum == LEVEL_LLL) {
        f32 LLL_High = 0; 
        f32 LLL_Low = 0.0f;

        if (gCurrAreaIndex != 2) {
            LLL_High = 5.0f;
            LLL_Low =  140.0f;
        }
            // Validamos PRIMERO que el objeto realmente esté tocando un suelo
            if (gCurObj->floor != NULL) {
                u32 phys = (gCurObj->floor->type >> 8) & 0xF;
                
                if (phys == SPECFLAG_BURNING) {
                    if (gCurrAreaIndex == 2)
                    {
                        LLL_Low = 0.0f;
                        LLL_High = 4000.0f;
                    }
                    else 
                    {
                        LLL_High = 0.0f;
                        LLL_Low =  2000.0f;
                    }
                }
            }
        //}
        zoneAtten = (LLL_High - gCurObj->oPosY) / (LLL_High - LLL_Low);
    }

    zoneAtten = my_fmax(0.0f, my_fmin(1.0f, zoneAtten));

    for (s32 i = 0; i < 3; i++) {
        f32 currentAmbient;

        if (gCurrLevelNum == LEVEL_JRB) {
            currentAmbient = (f32)RGBAmbient[i] * (1.0f - zoneAtten) + (f32)LowestColor[i] * zoneAtten;
        } else {
            currentAmbient = (f32)RGBAmbient[i];
        }
        currentAmbient *= deepDarknessMult;

        float finalColor = (float)diffuse[i] * (1.0f - zoneAtten) + currentAmbient * zoneAtten;

        // ═══ APLICAR FADE ═══
        f32 fadedColor   = my_fmax(0.0f, my_fmin(255.0f, finalColor))     * distanceFade;
        f32 fadedAmbient = my_fmax(0.0f, my_fmin(255.0f, currentAmbient)) * distanceFade;

        WorldLight->l->l.col[i]  = WorldLight->l->l.colc[i]  = (u8)fadedColor;
        WorldLight->a.l.col[i]   = WorldLight->a.l.colc[i]   = (u8)fadedAmbient;
        WorldLight->l->l.dir[i]  = (s8)((float)gLightDir[i] * (1.0f - currentObjShadowOpacity)
                                    + (float)gOnShadowLightDir[i] * currentObjShadowOpacity);
    }

    // --- Bucle de Point Lights ---
    for (s32 i = 0; i < gPointLightCount; i++) {
        if (gPointLights[i].flags & LIGHT_FLAG_IS_DIRECTIONAL) {
            if (shadowSurf != NULL && gCurObj->oPosY < shadowHeight) {
                u8 floorLight = ((shadowSurf->type >> 4) & 0xF);
                u8 lightType = ((gPointLights[i].floorType >> 4) & 0xF);

                if (floorLight != 0 && floorLight == lightType) {
                    lights[numLightsPicked] = &gPointLights[i];
                    distancesSq[numLightsPicked] = 0.0f;
                    numLightsPicked++;
                    continue;
                }
            }
        }
        if (gPointLights[i].flags & LIGHT_FLAG_IS_FLOORED) {
            if ((gPointLights[i].flags & LIGHT_FLAG_OCCLUDE) && currentObjShadowOpacity >= 1.0f) continue;
            if (gCurObj->floor != NULL) {
                u32 phys = (gCurObj->floor->type >> 8) & 0xF;
                if (phys == SPECFLAG_PAINTING) continue;
            }
            s16 extractedLightID = (s16)(lightID & 0xF); 
            if (lightID == -1 || extractedLightID != (s16)gPointLights[i].floorType) continue;
            f32 hDist = gCurObj->oPosY - gCurObj->floorHeight;
            if (hDist < -20.0f) continue; 
            if (gPointLights[i].bLerp && hDist >= gPointLights[i].maxDist) continue;
            if (numLightsPicked < MAX_POINT_LIGHTS_ACTIVE) {
                lights[numLightsPicked] = &gPointLights[i];
                distancesSq[numLightsPicked] = 0.0f;
                numLightsPicked++;
            }
            continue;
        }
        if (gPointLights[i].flags & (LIGHT_FLAG_IS_POINT | LIGHT_FLAG_IS_RELATIVE)) {
            f32 curDistSq;
            f32 dx = gPointLights[i].worldPos[0] - gCurObj->header.gfx.pos[0];
            f32 dz = gPointLights[i].worldPos[2] - gCurObj->header.gfx.pos[2];
            f32 dy;
            if (gPointLights[i].flags & LIGHT_FLAG_IS_RELATIVE) {
                f32 testY = gCurObj->header.gfx.pos[1] + gPointLights[i].RelativeYLoc;
                if (testY < gPointLights[i].minY) testY = gPointLights[i].minY;
                if (testY > gPointLights[i].maxY) testY = gPointLights[i].maxY;
                dy = testY - gCurObj->header.gfx.pos[1];
            } else {
                dy = gPointLights[i].worldPos[1] - gCurObj->header.gfx.pos[1];
            }
            curDistSq = (dx * dx + dy * dy + dz * dz);
            if (curDistSq > (gPointLights[i].maxDist * gPointLights[i].maxDist)) continue;
            if (numLightsPicked < MAX_POINT_LIGHTS_ACTIVE) {
                lights[numLightsPicked] = &gPointLights[i];
                distancesSq[numLightsPicked] = curDistSq;
                numLightsPicked++;
                maxIndex = 0;
                for (s32 j = 1; j < numLightsPicked; j++) if (distancesSq[j] > distancesSq[maxIndex]) maxIndex = j;
            } else if (curDistSq < distancesSq[maxIndex]) {
                lights[maxIndex] = &gPointLights[i];
                distancesSq[maxIndex] = curDistSq;
                maxIndex = 0;
                for (s32 j = 1; j < numLightsPicked; j++) if (distancesSq[j] > distancesSq[maxIndex]) maxIndex = j;
            }
        }
    }
    if (gUseGlobalLightAsCamLight == TRUE)
    {
        LightQuantity = 0;
    } 
    else 
    {
        LightQuantity = 1;
    }
    
    pointLightsDlHead = pointLightsDl = alloc_display_list(sizeof(Gfx) * (numLightsPicked + 6));  // +6
    gSPNumLights(pointLightsDl++, NUMLIGHTS_1 + LightQuantity + numLightsPicked);

    // LIGHT_1: directional
    if (gUseGlobalLightAsCamLight == FALSE) {
        gSPLight(pointLightsDl++, &WorldLight->l, LIGHT_1);
    } else {
        gSPLight(pointLightsDl++, &camLight.l[0], LIGHT_1);
    }

    // ═══ NUEVO: LIGHT_2 con camLight LOCAL fadeado ═══
    if (gUseGlobalLightAsCamLight == FALSE) {
        Light *fadedCamLight = (Light *) alloc_display_list(sizeof(Light));
        bzero(fadedCamLight, sizeof(Light));
        for (s32 f = 0; f < 3; f++) {
            fadedCamLight->l.col[f]  = fadedCamLight->l.colc[f] =
                (u8)(camLight.l->l.col[f] * distanceFade);
            fadedCamLight->l.dir[f]  = camLight.l[0].l.dir[f];
        }
        gSPLight(pointLightsDl++, fadedCamLight, LIGHT_2);
    }

    for (s32 i = 0; i < numLightsPicked; i++) {
        Light *currentLight = alloc_display_list(sizeof(Light));
        bzero(currentLight, sizeof(Light));
        if (lights[i]->flags & LIGHT_FLAG_IS_FLOORED) {
            f32 hDist = my_fmax(0.0f, gCurObj->oPosY - gCurObj->floorHeight);
            f32 attenuation = 1.0f;
            if (lights[i]->bLerp) attenuation = my_fmax(0.0f, 1.0f - (hDist / (lights[i]->maxDist + 1.0f)));
            f32 shadowFactor = 1.0f;
            if (lights[i]->flags & LIGHT_FLAG_OCCLUDE) shadowFactor = 1.0f - currentObjShadowOpacity;
            f32 intensity = attenuation * shadowFactor;
            for (s32 f = 0; f < 3; f++) {
                u8 finalComponent = (lights[i]->bLerp) 
                                    ? (u8)(lights[i]->RGBMultAdd[f] * intensity) 
                                    : (u8)(lights[i]->RGBMultAdd[f] * shadowFactor);
                currentLight->l.col[f] = currentLight->l.colc[f] = finalComponent;
                currentLight->l.dir[f] = lights[i]->l.l.dir[f];
            }
        }
        if (lights[i]->flags & (LIGHT_FLAG_IS_POINT | LIGHT_FLAG_IS_RELATIVE)) {
            f32 lightDist = sqrtf(distancesSq[i]);
            f32 normalized = my_fmin(1.0f, lightDist / (lights[i]->maxDist + 1.0f));
            f32 scale = my_fmax(0.0f, (0.1f * lights[i]->brightness) * (1.0f - (normalized * normalized)));
            for (s32 f = 0; f < 3; f++) {
                currentLight->l.col[f] = currentLight->l.colc[f] = (u8)(lights[i]->RGBMultAdd[f] * scale);
                f32 dVal;
                if (lights[i]->flags & LIGHT_FLAG_IS_RELATIVE) {
                    f32 targetY = gCurObj->header.gfx.pos[1] + lights[i]->RelativeYLoc;
                    if (targetY < lights[i]->minY) targetY = lights[i]->minY;
                    if (targetY > lights[i]->maxY) targetY = lights[i]->maxY;
                    dVal = (f == 1) ? (targetY - gCurObj->header.gfx.pos[1]) : (lights[i]->worldPos[f] - gCurObj->header.gfx.pos[f]);
                } else {
                    dVal = lights[i]->worldPos[f] - gCurObj->header.gfx.pos[f];
                }
                currentLight->l.dir[f] = (s8)((dVal / (lightDist + 1.0f)) * 126.0f);
            }
        }
        if (lights[i]->flags & LIGHT_FLAG_IS_DIRECTIONAL) {
            for (s32 f = 0; f < 3; f++) {
                currentLight->l.col[f] = currentLight->l.colc[f] = lights[i]->RGBMultAdd[f];
                currentLight->l.dir[f] = lights[i]->l.l.dir[f];
            }
        }
        gSPLight(pointLightsDl++, &currentLight->l, LIGHT_2 + LightQuantity + i);
    }

    gSPLight(pointLightsDl++, &WorldLight->a, LIGHT_2 + LightQuantity + numLightsPicked);
    gSPEndDisplayList(pointLightsDl);
    return pointLightsDlHead;
}

void set_ambient_light(u8 lightColor[3])
{
    for (s32 i = 0; i < 3; i++)
    {
        RGBAmbient[i] = lightColor[i];
    }
}

void set_directional_light(u8 lightColor[3], u8 lightDir[3])
{
    for (s32 i = 0; i < 3; i++)
    {
        RGBLight[i] = lightColor[i];
        gLightDir[i] = lightDir[i];
    }
}

void addPointLight(struct Object *obj, const u8 rgb[3], f32 maxDist, s32 brightness, s32 bOcclude) {
    struct SceneLight *l = &gPointLights[gPointLightCount];
    bzero(l, sizeof(struct SceneLight)); // Limpieza total de la entrada

    for (s32 i = 0; i < 3; i++) {
        l->RGBMultAdd[i] = rgb[i];
        l->worldPos[i] = obj->header.gfx.pos[i];
    }
    l->maxDist = maxDist;
    l->brightness = brightness;
    l->flags = LIGHT_FLAG_IS_POINT; // Asignación limpia, borra flags anteriores
    
    if (bOcclude) l->flags |= LIGHT_FLAG_OCCLUDE;

    gPointLightCount++;
}

void addRelativeLight(Vec3f pos, const u8 rgb[3], f32 maxDist, s32 brightness, s16 RelativeYloc, s16 minY, s16 maxY) {

    struct SceneLight *l = &gPointLights[gPointLightCount];
    bzero(l, sizeof(struct SceneLight));

    for (s32 i = 0; i < 3; i++) {
        l->RGBMultAdd[i] = rgb[i];
        l->worldPos[i] = pos[i];
    }
    l->maxDist = maxDist;
    l->minY = minY;
    l->maxY = maxY;
    l->RelativeYLoc = RelativeYloc;
    l->brightness = brightness;
    l->flags = LIGHT_FLAG_IS_RELATIVE;

    gPointLightCount++;
}

void addPositionedLight(Vec3f pos, const u8 rgb[3], f32 maxDist, s32 brightness) {

    struct SceneLight *l = &gPointLights[gPointLightCount];
    bzero(l, sizeof(struct SceneLight));

    for (s32 i = 0; i < 3; i++) {
        l->RGBMultAdd[i] = rgb[i];
        l->worldPos[i] = pos[i];
    }
    l->maxDist = maxDist;
    l->brightness = brightness;
    l->flags = LIGHT_FLAG_IS_POINT | LIGHT_FLAG_OCCLUDE;

    gPointLightCount++;
}

void addDirectionalLight(u8 rgb[3], s8 dir[3], s16 volumeID) {
    // Aseguramos que no nos pasemos del límite de luces
    if (gPointLightCount >= MAX_POINT_LIGHTS) return;

    struct SceneLight *l = &gPointLights[gPointLightCount];
    bzero(l, sizeof(struct SceneLight)); // Limpieza total para evitar basura

    l->flags = LIGHT_FLAG_IS_DIRECTIONAL;
    
    // Guardamos el volumeID en el segmento 'part' (bits 4-7) como acordamos
    l->floorType = (volumeID & 0xF) << 4;
    
    for (s32 i = 0; i < 3; i++) {
        // Guardamos el color original aquí para leerlo después
        l->RGBMultAdd[i] = rgb[i]; 
        
        // Guardamos la dirección
        l->l.l.dir[i] = dir[i];
    }
    
    gPointLightCount++;
}

void addDirectionalLightBasedOnFLoorType(const u8 rgb[3], s8 dir[3], s32 floorType) {

    struct SceneLight *l = &gPointLights[gPointLightCount];
    bzero(l, sizeof(struct SceneLight));

    for (s32 i = 0; i < 3; i++) {
        l->l.l.col[i] = l->l.l.colc[i] = rgb[i];
        l->l.l.dir[i] = dir[i];
    }
    l->flags = LIGHT_FLAG_IS_DIRECTIONAL;
    l->floorType = (s16)floorType;
    gPointLightCount++;
}

void addFlooredLight(const u8 rgb[3], s8 dir[3], s32 floorType, f32 maxDist, u8 bOcclude, u8 bLerp) {

    struct SceneLight *l = &gPointLights[gPointLightCount];
    bzero(l, sizeof(struct SceneLight));

    for (s32 i = 0; i < 3; i++) {
        l->RGBMultAdd[i] = rgb[i];
        l->l.l.dir[i] = dir[i];
    }
    l->flags = LIGHT_FLAG_IS_FLOORED;
    if (bOcclude) l->flags |= LIGHT_FLAG_OCCLUDE;
    l->floorType = (s16)floorType;
    l->maxDist = maxDist;
    l->bLerp = bLerp;

    gPointLightCount++;
}

struct PositionedLightConfig {
    s16 levelNum;
    s16 areaIndex;
    f32 pos[3];
    u8 rgb[3];
    f32 range;
    s32 intensity;
    // Parámetros específicos para luces relativas
    s16 relativeYloc; 
    s16 minY;
    s16 maxY;
    u8 isRelative; 
};

static const struct PositionedLightConfig sGlobalLightTable[] = {
    // Nivel | Área | Posición (X, Y, Z) | Color (R, G, B) | Rango | Int. | RelY | MinY | MaxY | ¿Relativa?

    // --- LEVEL SSL: ---
    { LEVEL_SSL, 3, { 0, -550, -2816}, {0xFF, 0xA9, 0x23}, 1500, 10, 150, -1214, -500, TRUE },
   
    // --- LEVEL LLL: ---
    { LEVEL_LLL, 2, { 0, 5170, -3100}, {0xFF, 0x44, 0x32}, 2500, 10, 0, 0, 5170, TRUE },

    // --- LEVEL HMC: Amarillas (sLightsRGB: 0xFB, 0xFF, 0x00) ---
    { LEVEL_HMC, 1, {-7845, 2775,  7826}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-7725, 2775,  6850}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-7725, 2775,  5849}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-7847, 2775, -7825}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6876, 2775,  7700}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6860, 2631,  5245}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6595, 2460,  4014}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6810, 2247,  3092}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6295, 2135,  2070}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5200, 2600,  6168}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-4141, 2600,  6699}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-4020, 2600,  5671}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-3025, 2600,  5500}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-3000, 2600,  4246}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-1779, 2600,  4240}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {   655,  393,  3410}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {   379,  393,  2630}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {   743,  393,  2266}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {   180, 2488,  3663}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-1371,  393,  1313}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-1189,  393,   832}, {0xFB, 0xFF, 0x00}, 1500, 10, 0, 0, 0, FALSE },

    // --- LEVEL HMC: Rojas (sRedLightsRGB: 0xFF, 0x32, 0x00) ---
    { LEVEL_HMC, 1, {-7480, 2049,   352}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5518, 2049,   866}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-4960, 2049,   334}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-4411, 2049,   610}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-3347, 2049,  -106}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-3597, 2049, -1106}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6506, 2049, -3662}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5376, 2049, -3662}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6506, 2100, -3662}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5476, 2100, -5190}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6727, 2255, -5191}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5475, 2255, -6722}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-6505, 2255, -6728}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5476, 1936, -3663}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5580, 3160, -7985}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5120, 3160, -6321}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-2814,   95, -6525}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-5115,-4487,  -487}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, {-1913,-4487,  -487}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 1540,-4200,  2047}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 2663,-4200,  2047}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 3790,-4200,  2047}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 4913,-4200,  2047}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 6044,-4200,  2047}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 1540,-4200,  2612}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 2663,-4200,  2612}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 3790,-4200,  2612}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 4913,-4200,  2612}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },
    { LEVEL_HMC, 1, { 6044,-4200,  2612}, {0xFF, 0x32, 0x00}, 1500, 10, 0, 0, 0, FALSE },

    // --- LEVEL WF: (sWFYellowLightsRGB: 0xFF, 0xFF, 0x7F) ---
    { LEVEL_WF, 1, {-2285,  520,  1726}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, {-2275,  900,  3218}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, {-1197,  900,  3584}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3399, 1292,  2547}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3399, 1775,  1200}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3500, 1425,  1075}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3841,  945, -1250}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3841,  945, -2315}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3400, 1140, -2836}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3420, 2223,  -247}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { -880, 2785,   445}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { -625, 2785, -1061}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 1326, 2811,  -642}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },
    { LEVEL_WF, 1, { 3342, 1428,  -375}, {0xFF, 0xFF, 0x7F},  750, 10, 0, 0, 0, FALSE },

    // --- LEVEL BITDW: Relative Light (Color sBitdwLightColor) ---
    { LEVEL_BITDW, 1, {-4600, 1000, -310}, {0x9D, 0xD5, 0xFF}, 1500, 10, -10, -155, 1600, TRUE },

    // --- LEVEL CCM Area 2 (cabinLight) ---
    { LEVEL_CCM, 2, {-6060, -3990, -6959}, {0xFF, 0xF0, 0xFA}, 1500, 10, 250, -6000, -3825, TRUE },

    // --- LEVEL PSS: (sRedLightsRGB: 0xFF, 0x32, 0x00) ---
    { LEVEL_PSS, 1, { 4790, 7771, -5765}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, { 2938, 6481, -5219}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, { 2938, 6481, -6147}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-3608, 4981, -6199}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-5772, 4741, -5502}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-6711, 4351, -3122}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-6693, 3961,    32}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-4999, 3573,  2394}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-4488,-3267, -3297}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-6116,-1977,  5385}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-5874,-4167,  3695}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-6810,-4032,  2300}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-5874,-4032,  2300}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-6810,-3911,   892}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-5874,-3911,   892}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },
    { LEVEL_PSS, 1, {-6819,-4181,  3701}, {0xFF, 0x32, 0x00}, 1000, 10, 0, 0, 0, FALSE },

    // --- LEVEL JRB: Relative Lights (Amarillas) ---
    { LEVEL_JRB, 1, {  360, -1078, -6642}, {0xFF, 0xF0, 0x9C}, 3200, 10, 250, -2700, 100, TRUE },
    { LEVEL_JRB, 1, { 4260, -1078, -6145}, {0xFF, 0xF0, 0x9C}, 3200, 10, 250, -2700, 100, TRUE },

    // --- LEVEL JRB: Relative Lights (Suaves) ---
    { LEVEL_JRB, 1, {-1933, -2966, -2664}, {0x1C, 0x29, 0x1E}, 3200, 10,  50, -2700, 100, TRUE },
    { LEVEL_JRB, 1, {-1825, -2812, -1628}, {0x1C, 0x29, 0x1E}, 3200, 10,  50, -2700, 100, TRUE },

    // --- LEVEL BOB: (sBOBLightsRGB) ---
    { LEVEL_BOB, 1, {-5694,  -528,  5600}, {0xDF, 0xFF, 0xFF}, 1750, 10, 0, 0, 0, FALSE },

    // Centinela final (Indica el fin del array)
    { 0, 0, {0}, {0}, 0.0f, 0, 0, 0, 0, FALSE }
};

void setup_lights_per_level(void) {
    s32 i;
    s32 tableSize = sizeof(sGlobalLightTable) / sizeof(struct PositionedLightConfig);

    for (i = 0; i < tableSize; i++) {
        const struct PositionedLightConfig *l = &sGlobalLightTable[i];

        // Detener si llegamos al final o el rango es 0
        if (l->range <= 0.0f) break;

        // Validar Nivel y Área
        if (l->levelNum == gCurrLevelNum && l->areaIndex == gCurrAreaIndex) {
            if (l->isRelative) {
                addRelativeLight(
                    (f32 *)l->pos, l->rgb, l->range, l->intensity, 
                    l->relativeYloc, l->minY, l->maxY
                );
            } else {
                addPositionedLight((f32 *)l->pos, l->rgb, l->range, l->intensity);
            }
        }
    }
}

struct FloorLightConfig {
    s16 levelNum;    // Nuevo: ID del nivel (LEVEL_BOB, etc.)
    s16 areaIndex;   // Nuevo: ID del área (usualmente 1, 2, 3...)
    u8 rgb[3];
    s8 dir[3];
    s16 surface;
    f32 range;
    u8 bOcclude;
    u8 bLerp;
};

static const struct FloorLightConfig sFloorLightTable[] = {
    // BOB - Área 1
    { LEVEL_BOB, 1, {0x60, 0xDC, 0x65}, {0, -127, 0}, 1, 350.0f, TRUE, TRUE },
    { LEVEL_BOB, 1, {0x7C, 0x7C, 0x7C}, {0, -127, 0}, 2, 500.0f, TRUE, TRUE },
    
    // CCM - Área 1
    { LEVEL_CCM, 1, {0x7C, 0x7C, 0x9C}, {0, -127, 0}, 1, 500.0f, TRUE, TRUE },
    
    // LLL - Área 1
    { LEVEL_LLL, 1, {0xFF, 0x7F, 0x00}, {0, -127, 0}, 1, 1000.0f, TRUE, TRUE },
    { LEVEL_LLL, 2, {0xFF, 0x7F, 0x00}, {0, -127, 0}, 1, 4000.0f, TRUE, TRUE },
    
    // CASTLE GROUNDS - Área 1
    { LEVEL_CASTLE_GROUNDS, 1, {0x3F, 0x9F, 0x00}, {0, -127, 0}, 1, 750.0f, TRUE, TRUE },
    { LEVEL_CASTLE_GROUNDS, 1, {0x7D, 0x72, 0x4F}, {0, -127, 0}, 2, 500.0f, TRUE, TRUE },
    { LEVEL_CASTLE_GROUNDS, 1, {0x5C, 0x5C, 0x5C}, {0, -127, 0}, 3, 350.0f, TRUE, TRUE },
    { LEVEL_CASTLE_GROUNDS, 1, {150, 39, 0},      {0, -127, 0}, 4, 500.0f, TRUE, TRUE },
    { LEVEL_CASTLE_COURTYARD, 1, {0x3F, 0x9F, 0x00}, {0, -127, 0}, 1, 750.0f, TRUE, TRUE },
    { LEVEL_CASTLE_COURTYARD, 1, {0x5C, 0x5C, 0x5C}, {0, -127, 0}, 5, 350.0f, TRUE, TRUE },

    // Centinela final para detener el bucle
    { 0, 0, {0}, {0}, 0, 0.0f, 0, 0 } 
};

static void process_floor_lights(void) {
    s32 i;
    // Obtenemos el número de elementos para evitar desbordamientos
    s32 tableSize = sizeof(sFloorLightTable) / sizeof(struct FloorLightConfig);

    for (i = 0; i < tableSize; i++) {
        const struct FloorLightConfig *light = &sFloorLightTable[i];

        // Si llegamos al final (range 0), terminamos
        if (light->range <= 0.0f) break;

        // Filtro: Solo procesar si coincide nivel Y área
        // Nota: Si quieres que una luz esté en todas las áreas de un nivel, 
        // podrías usar un valor como -1 para areaIndex.
        if (light->levelNum == gCurrLevelNum && light->areaIndex == gCurrAreaIndex) {
            addFlooredLight((u8 *)light->rgb, (s8 *)light->dir, light->surface, light->range, light->bOcclude, light->bLerp);
        }
    }
}

struct DirLightConfig {
    s16 levelNum;    // ID del nivel
    s16 areaIndex;   // ID del área
    s16 volumeID;    // El ID que debe tener el volumen (ID > 1)
    u8 rgb[3];       // Color de la luz direccional
    s8 dir[3];       // Vector de dirección de la luz
};

static const struct DirLightConfig sDirLightTable[] = {
    { LEVEL_CASTLE_GROUNDS, 1, 2, {0x3C, 0x3C, 0x3C}, {0, -25, 90} },
    { LEVEL_CASTLE, 1, 1, {0xFF, 0xFF, 0xFF}, {0, 90, 0} },
    { LEVEL_CASTLE, 1, 2, {0xFF, 0xFF, 0xFF}, {0, 45, 0} },
    { LEVEL_CASTLE, 1, 3, {0xFF, 0xFF, 0xFF}, {0, 90, 0} },
    { LEVEL_CASTLE, 1, 4, {0xFF, 0xFF, 0xFF}, {0, 90, 0} },
    { LEVEL_CASTLE, 1, 5, {0xFF, 0xFF, 0xFF}, {0, 90, 0} },
    { LEVEL_LLL, 1, 2, {0xFF, 0x1E, 0x00}, {0, -127, 0} },
    { 0, 0, 0, {0}, {0} } 
};

static void process_directional_lights(void) {
    s32 i;
    // No necesitamos calcular el tamaño manualmente si usamos el centinela, 
    // pero por seguridad lo hacemos:
    s32 tableSize = sizeof(sDirLightTable) / sizeof(struct DirLightConfig);

    for (i = 0; i < tableSize; i++) {
        const struct DirLightConfig *light = &sDirLightTable[i];

        // Detener si llegamos al centinela (color 0 y volumeID 0)
        if (light->volumeID == 0) break;

        // Filtro de Nivel y Área
        if (light->levelNum == gCurrLevelNum && light->areaIndex == gCurrAreaIndex) {
            // Llamamos a una función que añada la flag LIGHT_FLAG_IS_DIRECTIONAL
            // y asigne el volumeID para que el objeto sepa cuál le corresponde.
            addDirectionalLight((u8 *)light->rgb, (s8 *)light->dir, light->volumeID);
        }
    }
}

Mat4 gCameraTransform;

Vec3f globalLightDirection = { 0x28, 0x28, 0x28 };
/**
 * Process a camera node.
 */
void geo_process_camera(struct GraphNodeCamera *node) {
    Mtx *rollMtx = alloc_display_list(sizeof(*rollMtx));
    s32 i;
    Mtx *viewMtx = alloc_display_list(sizeof(Mtx));
    if (node->fnNode.func)
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    mtxf_rotate_xy(rollMtx, node->rollScreen);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(rollMtx), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    mtxf_lookat(gCameraTransform, node->pos, node->focus, node->roll);
    // Make a copy of the view matrix and scale its translation based on WORLD_SCALE
    Mat4* cameraMatrix = &gCameraTransform;
    gCurLookAt->l[0].l.dir[0] = (s8)(127.0f * (*cameraMatrix)[0][0]);
    gCurLookAt->l[0].l.dir[1] = (s8)(127.0f * (*cameraMatrix)[1][0]);
    gCurLookAt->l[0].l.dir[2] = (s8)(127.0f * (*cameraMatrix)[2][0]);
    gCurLookAt->l[1].l.dir[0] = (s8)(127.0f * -(*cameraMatrix)[0][1]);
    gCurLookAt->l[1].l.dir[1] = (s8)(127.0f * -(*cameraMatrix)[1][1]);
    gCurLookAt->l[1].l.dir[2] = (s8)(127.0f * -(*cameraMatrix)[2][1]);
    Mat4 scaledCamera;
    mtxf_copy(scaledCamera, gCameraTransform);
    for (int i = 0; i < 3; i++) {
        scaledCamera[3][i] /= WORLD_SCALE;
    }
    //if (gMarioObject != NULL) {print_text_fmt_int(20, 20, "%d", gMarioState->floor->room);}
    setup_lights_per_level();
    process_directional_lights();
    process_floor_lights();
    // Convert the scaled matrix to fixed-point and integrate it into the projection matrix stack
    guMtxF2L(scaledCamera, viewMtx);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(viewMtx), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    curLight = (Lights1 *) alloc_display_list(sizeof(Lights1));
    bzero(curLight, sizeof(Lights1));
    gSPSetLights1(gDisplayListHead++, (*curLight));
    f32 camVector[3];

    for (i = 0; i  < 3; i++) {
        camVector[i] = node->pos[i] - node->focus[i];
        camera_pos[i] = node->pos[i];
    }
    vec3f_normalize(camVector);
    f32 cameraLightColor;
    f32 zoneAttenforCam = 0.0f;
    f32 waterSurfaceY = 500.0f;
    f32 waterBottomY  = -830.0f;
    if (gCurrLevelNum == LEVEL_JRB)
    {   
        zoneAttenforCam = (waterSurfaceY - gLakituState.pos[1]) / (waterSurfaceY - waterBottomY);
        zoneAttenforCam = my_fmax(0.0f, my_fmin(1.0f, zoneAttenforCam));
        for (s32 f = 0; f < 3; f++) {
            cameraLightColor = (f32)CamLightCol[f] * (1.0f - zoneAttenforCam) + (f32)LowestCamColor[f] * zoneAttenforCam;
        }
    } else {
        for (s32 f = 0; f < 3; f++) {
            cameraLightColor = CamLightCol[f];
        }
    }
    for (i = 0; i  < 3; i++) {
        camLight.l[0].l.dir[i] = camVector[i] * 127.f;
        camLight.l->l.col[i] = camLight.l->l.colc[i] = cameraLightColor;
        if (gUseGlobalLightAsCamLight == FALSE)
        {
            curLight->l->l.dir[i] = gLightDir[i];
            curLight->l->l.col[i] = curLight->l->l.colc[i] = RGBLight[i];
            curLight->a.l.col[i] = curLight->a.l.colc[i] = RGBAmbient[i];
        }
        else
        {
            curLight->l->l.dir[i] = camVector[i] * 127.0f;
            curLight->l->l.col[i] = curLight->l->l.colc[i] = cameraLightColor;
        }
        curLight->a.l.col[i] = curLight->a.l.colc[i] = RGBAmbient[i];
    }
    gSPClearGeometryMode(gDisplayListHead++, G_POINT_LIGHTING);
    if (gUseGlobalLightAsCamLight == FALSE)
    {
        gSPLight(gDisplayListHead++, &camLight.l[0], LIGHT_2);
    }
    if (node->fnNode.node.children != 0) {
        gCurGraphNodeCamera = node;
        node->matrixPtr = &gCameraTransform;
        geo_process_node_and_siblings(node->fnNode.node.children);
        gCurGraphNodeCamera = NULL;
    }
    gMatStackIndex--;
}

/**
 * Process a translation / rotation node. A transformation matrix based
 * on the node's translation and rotation is created and pushed on both
 * the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_translation_rotation(struct GraphNodeTranslationRotation *node) {
    Vec3f translation;

    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate_and_mul(node->rotation, translation, gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex]);

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a translation node. A transformation matrix based on the node's
 * translation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_translation(struct GraphNodeTranslation *node) {
    Vec3f translation;

    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate_and_mul(gVec3sZero, translation, gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex]);

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a rotation node. A transformation matrix based on the node's
 * rotation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_rotation(struct GraphNodeRotation *node) {
    mtxf_rotate_zxy_and_translate_and_mul(node->rotation, gVec3fZero, gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex]);

    inc_mat_stack();
    append_dl_and_return(((struct GraphNodeDisplayList *)node));
}

/**
 * Process a scaling node. A transformation matrix based on the node's
 * scale is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_scale(struct GraphNodeScale *node) {
    Vec3f scaleVec;

    vec3f_set(scaleVec, node->scale, node->scale, node->scale);
    mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], scaleVec);

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a billboard node. A transformation matrix is created that makes its
 * children face the camera, and it is pushed on the floating point and fixed
 * point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
void geo_process_billboard(struct GraphNodeBillboard *node) {
    Vec3f translation;
    Vec3f scale = { 1.0f, 1.0f, 1.0f };

    vec3s_to_vec3f(translation, node->translation);

    if (gCurGraphNodeHeldObject != NULL) {
        vec3f_copy(scale, gCurGraphNodeHeldObject->objNode->header.gfx.scale);
    } else if (gCurGraphNodeObject != NULL) {
        vec3f_copy(scale, gCurGraphNodeObject->scale);
    }

    mtxf_billboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], translation, scale, gCurGraphNodeCamera->roll);

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}

/**
 * Process a display list node. It draws a display list without first pushing
 * a transformation on the stack, so all transformations are inherited from the
 * parent node. It processes its children if it has them.
 */
void geo_process_display_list(struct GraphNodeDisplayList *node) {
    append_dl_and_return((struct GraphNodeDisplayList *)node);

    gMatStackIndex++;
}

/**
 * Process a generated list. Instead of storing a pointer to a display list,
 * the list is generated on the fly by a function.
 */
void geo_process_generated_list(struct GraphNodeGenerated *node) {
    if (node->fnNode.func != NULL) {
        Gfx *list = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, (struct AllocOnlyPool *) gMatStack[gMatStackIndex]);

        if (list != NULL) {
            geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(list), GET_GRAPH_NODE_LAYER(node->fnNode.node.flags));
        }
    }
    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

/**
 * Process a background node. Tries to retrieve a background display list from
 * the function of the node. If that function is null or returns null, a black
 * rectangle is drawn instead.
 */
void geo_process_background(UNUSED struct GraphNodeBackground *node) {
    return;
}

/**
 * Render an animated part. The current animation state is not part of the node
 * but set in global variables. If an animated part is skipped, everything afterwards desyncs.
 */
void geo_process_animated_part(struct GraphNodeAnimatedPart *node) {
    Vec3s rotation = { 0, 0, 0 };
    Vec3f translation = { node->translation[0], node->translation[1], node->translation[2] };

    if (gCurrAnimType == ANIM_TYPE_TRANSLATION) {
        for (s32 i = 0; i < 3; i++) {
        translation[i] += gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)]
                          * gCurrAnimTranslationMultiplier;
        }
        gCurrAnimType = ANIM_TYPE_ROTATION;
    } else {
        if (gCurrAnimType == ANIM_TYPE_LATERAL_TRANSLATION) {
            translation[0] +=
                gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)]
                * gCurrAnimTranslationMultiplier;
            gCurrAnimAttribute += 2;
            translation[2] +=
                gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)]
                * gCurrAnimTranslationMultiplier;
            gCurrAnimType = ANIM_TYPE_ROTATION;
        } else {
            if (gCurrAnimType == ANIM_TYPE_VERTICAL_TRANSLATION) {
                gCurrAnimAttribute += 2;
                translation[1] +=
                    gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)]
                    * gCurrAnimTranslationMultiplier;
                gCurrAnimAttribute += 2;
                gCurrAnimType = ANIM_TYPE_ROTATION;
            } else if (gCurrAnimType == ANIM_TYPE_NO_TRANSLATION) {
                gCurrAnimAttribute += 6;
                gCurrAnimType = ANIM_TYPE_ROTATION;
            }
        }
    }

    if (gCurrAnimType == ANIM_TYPE_ROTATION) {
        for (s32 i = 0; i < 3; i++) {
            rotation[i] = gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)];
        }
    }

    mtxf_rotate_xyz_and_translate_and_mul(rotation, translation, gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex]);

    inc_mat_stack();
    append_dl_and_return(((struct GraphNodeDisplayList *)node));
}

/**
 * Render an animated part that has an initial rotation value
 */
void geo_process_bone(struct GraphNodeBone *node) {
    Vec3s rotation = { node->rotation[0], node->rotation[1], node->rotation[2] };
    Vec3f translation = { node->translation[0], node->translation[1], node->translation[2] };

    s32 animIndex;
    f32 animValue;

    switch (gCurrAnimType) {
        case ANIM_TYPE_TRANSLATION:
            animIndex = retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute);
            animValue = gCurrAnimData[animIndex] * gCurrAnimTranslationMultiplier;
            for (s32 i = 0; i < 3; i++) {
                translation[i] += animValue;
            }
            gCurrAnimType = ANIM_TYPE_ROTATION;
            break;

        case ANIM_TYPE_LATERAL_TRANSLATION:
            animIndex = retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute);
            translation[0] += gCurrAnimData[animIndex] * gCurrAnimTranslationMultiplier;
            gCurrAnimAttribute += 2;
            animIndex = retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute);
            translation[2] += gCurrAnimData[animIndex] * gCurrAnimTranslationMultiplier;
            gCurrAnimType = ANIM_TYPE_ROTATION;
            break;

        case ANIM_TYPE_VERTICAL_TRANSLATION:
            gCurrAnimAttribute += 2;
            animIndex = retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute);
            translation[1] += gCurrAnimData[animIndex] * gCurrAnimTranslationMultiplier;
            gCurrAnimAttribute += 2;
            gCurrAnimType = ANIM_TYPE_ROTATION;
            break;

        case ANIM_TYPE_NO_TRANSLATION:
            gCurrAnimAttribute += 6;
            gCurrAnimType = ANIM_TYPE_ROTATION;
            break;

        default:
            break;
    }

    if (gCurrAnimType == ANIM_TYPE_ROTATION) {
        for (s32 i = 0; i < 3; i++) {
            animIndex = retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute);
            rotation[i] += gCurrAnimData[animIndex];
        }
    }

    mtxf_rotate_xyz_and_translate_and_mul(rotation, translation, gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex]);

    inc_mat_stack();
    append_dl_and_return((struct GraphNodeDisplayList *)node);
}


/**
 * Initialize the animation-related global variables for the currently drawn
 * object's animation.
 */
void geo_set_animation_globals(struct AnimInfo *node, s32 hasAnimation) {
    struct Animation *anim = node->curAnim;

    if (hasAnimation) {
        node->animFrame = geo_update_animation_frame(node, &node->animFrameAccelAssist);
    }
    node->animTimer = gAreaUpdateCounter;
    if (anim->flags & ANIM_FLAG_HOR_TRANS) {
        gCurrAnimType = ANIM_TYPE_VERTICAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_VERT_TRANS) {
        gCurrAnimType = ANIM_TYPE_LATERAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_NO_TRANS) {
        gCurrAnimType = ANIM_TYPE_NO_TRANSLATION;
    } else {
        gCurrAnimType = ANIM_TYPE_TRANSLATION;
    }

    gCurrAnimFrame = node->animFrame;
    gCurrAnimEnabled = (anim->flags & ANIM_FLAG_DISABLED) == 0;
    gCurrAnimAttribute = segmented_to_virtual((void *) anim->index);
    gCurrAnimData = segmented_to_virtual((void *) anim->values);

    if (anim->animYTransDivisor == 0) {
        gCurrAnimTranslationMultiplier = 1.0f;
    } else {
        gCurrAnimTranslationMultiplier = (f32) node->animYTrans / (f32) anim->animYTransDivisor;
    }
}

/**
 * Process a shadow node. Renders a shadow under an object offset by the
 * translation of the first animated component and rotated according to
 * the floor below it.
 */
void geo_process_shadow(struct GraphNodeShadow *node) {
#ifndef DISABLE_SHADOWS
    if (gCurGraphNodeCamera == NULL || gCurGraphNodeObject == NULL) {
        if (node->node.children != NULL) {
            geo_process_node_and_siblings(node->node.children);
        }
        return;
    }

    Vec3f shadowPos;
    f32 shadowScale;

    if (gCurGraphNodeHeldObject != NULL) {
        vec3f_copy(shadowPos, gMatStack[gMatStackIndex][3]);
        shadowScale = node->shadowScale * gCurGraphNodeHeldObject->objNode->header.gfx.scale[0];
    } else {
        vec3f_copy(shadowPos, gCurGraphNodeObject->pos);
        shadowScale = node->shadowScale * gCurGraphNodeObject->scale[0];
    }

    s8 shifted = (gCurrAnimEnabled && (gCurrAnimType == ANIM_TYPE_TRANSLATION || gCurrAnimType == ANIM_TYPE_LATERAL_TRANSLATION));

    if (shifted) {
        struct GraphNode *geo = node->node.children;
        f32 objScale = 1.0f;
        if (geo != NULL && geo->type == GRAPH_NODE_TYPE_SCALE) {
            objScale = ((struct GraphNodeScale *) geo)->scale;
        }

        f32 animScale = gCurrAnimTranslationMultiplier * objScale;
        Vec3f animOffset;
        animOffset[0] = gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * animScale;
        animOffset[1] = 0.0f;
        gCurrAnimAttribute += 2;
        animOffset[2] = gCurrAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * animScale;
        gCurrAnimAttribute -= 6;

        // Simple matrix rotation so the shadow offset rotates along with the object
        f32 sinAng = sins(gCurGraphNodeObject->angle[1]);
        f32 cosAng = coss(gCurGraphNodeObject->angle[1]);

        shadowPos[0] += animOffset[0] * cosAng + animOffset[2] * sinAng;
        shadowPos[2] += -animOffset[0] * sinAng + animOffset[2] * cosAng;
    }

    Gfx *shadowList = create_shadow_below_xyz(shadowPos, shadowScale * 0.5f, node->shadowSolidity, node->shadowType, shifted);

    if (shadowList != NULL) {
        mtxf_shadow(gMatStack[gMatStackIndex + 1], gCurrShadow.floorNormal, shadowPos, gCurrShadow.scale, gCurGraphNodeObject->angle[1]);

        inc_mat_stack();
        geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(shadowList), gCurrShadow.isDecal ? LAYER_TRANSPARENT_DECAL : LAYER_TRANSPARENT);

        gMatStackIndex--;
    }
#endif
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}


/**
 * Check whether an object is in view to determine whether it should be drawn.
 * This is known as frustum culling.
 * It checks whether the object is far away, very close / behind the camera,
 * or horizontally out of view. It does not check whether it is vertically
 * out of view. It assumes a sphere of 300 units around the object's position
 * unless the object has a culling radius node that specifies otherwise.
 *
 * The matrix parameter should be the top of the matrix stack, which is the
 * object's transformation matrix times the camera 'look-at' matrix. The math
 * is counter-intuitive, but it checks column 3 (translation vector) of this
 * matrix to determine where the origin (0,0,0) in object space will be once
 * transformed to camera space (x+ = right, y+ = up, z = 'coming out the screen').
 * In 3D graphics, you typically model the world as being moved in front of a
 * static camera instead of a moving camera through a static world, which in
 * this case simplifies calculations. Note that the perspective matrix is not
 * on the matrix stack, so there are still calculations with the fov to compute
 * the slope of the lines of the frustum.
 *
 *        z-
 *
 *  \     |     /
 *   \    |    /
 *    \   |   /
 *     \  |  /
 *      \ | /
 *       \|/
 *        C       x+
 *
 * Since (0,0,0) is unaffected by rotation, columns 0, 1 and 2 are ignored.
 */
s32 obj_is_in_view(struct GraphNodeObject *node) {
    if (node->node.flags & GRAPH_RENDER_INVISIBLE) {
        return FALSE;
    }

    struct GraphNode *geo = node->sharedChild;

    s16 cullingRadius;

    if (geo != NULL && geo->type == GRAPH_NODE_TYPE_CULLING_RADIUS) {
        cullingRadius = ((struct GraphNodeCullingRadius *) geo)->cullingRadius;
    } else {
        cullingRadius = 300;
    }

    // Don't render if the object is close to or behind the camera
    if (node->cameraToObject[2] > -100.0f + cullingRadius) {
        return FALSE;
    }

    //! This makes the HOLP not update when the camera is far away, and it
    //  makes PU travel safe when the camera is locked on the main map.
    //  If Mario were rendered with a depth over 65536 it would cause overflow
    //  when converting the transformation matrix to a fixed point matrix.
    if (node->cameraToObject[2] < -20000.0f - cullingRadius) {
        return FALSE;
    }

    // half of the fov in in-game angle units instead of degrees
    s16 halfFov = (((((gCurGraphNodeCamFrustum->fov * sAspectRatio) / 2.0f) + 1.0f) * 32768.0f) / 180.0f) + 0.5f;

    f32 hScreenEdge = -node->cameraToObject[2] * tans(halfFov);
    // -matrix[3][2] is the depth, which gets multiplied by tan(halfFov) to get
    // the amount of units between the center of the screen and the horizontal edge
    // given the distance from the object to the camera.

    // This multiplication should really be performed on 4:3 as well,
    // but the issue will be more apparent on widescreen.
    // HackerSM64: This multiplication is done regardless of aspect ratio to fix object pop-in on the edges of the screen (which happens at 4:3 too)
    // hScreenEdge *= GFX_DIMENSIONS_ASPECT_RATIO;

    // Check whether the object is horizontally in view
    if (node->cameraToObject[0] > hScreenEdge + cullingRadius) {
        return FALSE;
    }
    if (node->cameraToObject[0] < -hScreenEdge - cullingRadius) {
        return FALSE;
    }

    return TRUE;
}

#ifdef VISUAL_DEBUG
void visualise_object_hitbox(struct Object *node) {
    Vec3f bnds1, bnds2;
    // This will create a cylinder that visualises their hitbox.
    // If they do not have a hitbox, it will be a small white cube instead.
    if (node->oIntangibleTimer != -1) {
        vec3f_set(bnds1, node->oPosX, (node->oPosY - node->hitboxDownOffset), node->oPosZ);
        vec3f_set(bnds2, node->hitboxRadius, node->hitboxHeight-node->hitboxDownOffset, node->hitboxRadius);
        if (node->behavior == segmented_to_virtual(bhvWarp)
            || node->behavior == segmented_to_virtual(bhvDoorWarp)
            || node->behavior == segmented_to_virtual(bhvFadingWarp)) {
            debug_box_color(COLOR_RGBA32_DEBUG_WARP);
        } else {
            debug_box_color(COLOR_RGBA32_DEBUG_HITBOX);
        }

        debug_box(bnds1, bnds2, (DEBUG_SHAPE_CYLINDER | DEBUG_UCODE_REJ));
        vec3f_set(bnds1, node->oPosX, (node->oPosY - node->hitboxDownOffset), node->oPosZ);
        vec3f_set(bnds2, node->hurtboxRadius, node->hurtboxHeight, node->hurtboxRadius);
        debug_box_color(COLOR_RGBA32_DEBUG_HURTBOX);
        debug_box(bnds1, bnds2, (DEBUG_SHAPE_CYLINDER | DEBUG_UCODE_REJ));
    } else {
        vec3f_set(bnds1, node->oPosX, (node->oPosY - 15), node->oPosZ);
        vec3f_set(bnds2, 30, 30, 30);
        debug_box_color(COLOR_RGBA32_DEBUG_POSITION);
        debug_box(bnds1, bnds2, (DEBUG_SHAPE_BOX | DEBUG_UCODE_REJ));
    }
}
#endif
Gfx *createResetLightsDl(void) {
    Gfx *gfx = alloc_display_list(5 * sizeof(Gfx));
    Gfx *dl = gfx;

    // Replicamos exactamente la configuración de luces estándar
    gSPNumLights(dl++, NUMLIGHTS_2);
    gSPLight(dl++, &curLight->l[0], 1);
    gSPLight(dl++, &camLight.l[0], 2);
    gSPLight(dl++, &curLight->a, 3);
    gSPEndDisplayList(dl++);

    return gfx;
}
/**
 * Process an object node.
 */
void geo_process_object(struct Object *node) {
    s32 i;
    Vec3f finalScale; // Variable temporal para la escala final calculada
    if (node->header.gfx.areaIndex == gCurGraphNodeRoot->areaIndex) {
        if (node->header.gfx.throwMatrix != NULL) {
            mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], *node->header.gfx.throwMatrix, node->header.gfx.scale);
        } else if (node->header.gfx.node.flags & GRAPH_RENDER_BILLBOARD) {
            mtxf_billboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex],
                           node->header.gfx.pos, node->header.gfx.scale, gCurGraphNodeCamera->roll);
        } else {
            mtxf_rotate_zxy_and_translate(gMatStack[gMatStackIndex + 1], node->header.gfx.pos, node->header.gfx.angle);
            mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1], node->header.gfx.scale);
        }

        node->header.gfx.throwMatrix = &gMatStack[++gMatStackIndex];
        linear_mtxf_mul_vec3f_and_translate(gCameraTransform, node->header.gfx.cameraToObject, (*node->header.gfx.throwMatrix)[3]);

        // FIXME: correct types
        if (node->header.gfx.animInfo.curAnim != NULL) {
            geo_set_animation_globals(&node->header.gfx.animInfo, (node->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0);
        }
        node->floorHeight = find_floor(node->oPosX, node->oPosY, node->oPosZ, &node->floor);

        if (obj_is_in_view(&node->header.gfx)) {            
            // Create the displaylist to set the active point lights
            Gfx* pointLightsDl = createPointLightsDl(node);

            // Put the lights on every layer, this can be optimized in the future
            // It will require some geolayout command to specify which layers this object uses
            // Maybe this can be implemented in a GEO_ASM call, where the parameter is a layer mask
            for (i = LAYER_FORCE; i <= LAYER_TRANSPARENT_INTER; i++)
            {
                geo_append_display_list(pointLightsDl, i);
            }
            gMatStackIndex--;
            inc_mat_stack();

            if (node->header.gfx.sharedChild != NULL) {
#ifdef VISUAL_DEBUG
                if (hitboxView) visualise_object_hitbox(node);
#endif
                gCurGraphNodeObject = (struct GraphNodeObject *) node;
                node->header.gfx.sharedChild->parent = &node->header.gfx.node;
                geo_process_node_and_siblings(node->header.gfx.sharedChild);
                node->header.gfx.sharedChild->parent = NULL;
                gCurGraphNodeObject = NULL;
            }
            if (node->header.gfx.node.children != NULL) {
                geo_process_node_and_siblings(node->header.gfx.node.children);
            }
        }
        Gfx* resetLightsDl = createResetLightsDl();
    
        // Lo aplicamos a todas las capas para limpiar el estado del RSP
        for (i = LAYER_FORCE; i <= LAYER_TRANSPARENT_INTER; i++) {
            geo_append_display_list(resetLightsDl, i);
        }
        if (node->header.gfx.areaIndex == gCurGraphNodeRoot->areaIndex) {

            if (node->header.gfx.throwMatrix != NULL) {
                // Usamos finalScale en lugar de node->header.gfx.scale
                mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], *node->header.gfx.throwMatrix, finalScale);
            } else if (node->header.gfx.node.flags & GRAPH_RENDER_BILLBOARD) {
                mtxf_billboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex],
                            node->header.gfx.pos, finalScale, gCurGraphNodeCamera->roll);
            } else {
                mtxf_rotate_zxy_and_translate(gMatStack[gMatStackIndex + 1], node->header.gfx.pos, node->header.gfx.angle);
                mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1], finalScale);
            }
        }

        gMatStackIndex--;
        gCurrAnimType = ANIM_TYPE_NONE;
        node->header.gfx.throwMatrix = NULL;
    }
}

/**
 * Process an object parent node. Temporarily assigns itself as the parent of
 * the subtree rooted at 'sharedChild' and processes the subtree, after which the
 * actual children are be processed. (in practice they are null though)
 */
void geo_process_object_parent(struct GraphNodeObjectParent *node) {
    if (node->sharedChild != NULL) {
        node->sharedChild->parent = (struct GraphNode *) node;
        geo_process_node_and_siblings(node->sharedChild);
        node->sharedChild->parent = NULL;
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Process a held object node.
 */
void geo_process_held_object(struct GraphNodeHeldObject *node) {
    Mat4 mat;
    Vec3f translation;
    Mat4 tempMtx;

#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, gCurLookAt);
#endif

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    if (node->objNode != NULL && node->objNode->header.gfx.sharedChild != NULL) {
        vec3_prod_val(translation, node->translation, 0.25f);

        mtxf_translate(mat, translation);
        mtxf_copy(gMatStack[gMatStackIndex + 1], *gCurGraphNodeObject->throwMatrix);
        vec3f_copy(gMatStack[gMatStackIndex + 1][3], gMatStack[gMatStackIndex][3]);
        mtxf_copy(tempMtx, gMatStack[gMatStackIndex + 1]);
        mtxf_mul(gMatStack[gMatStackIndex + 1], mat, tempMtx);
        mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1], node->objNode->header.gfx.scale);

        if (node->fnNode.func != NULL) {
            node->fnNode.func(GEO_CONTEXT_HELD_OBJ, &node->fnNode.node, (struct AllocOnlyPool *) gMatStack[gMatStackIndex + 1]);
        }

        inc_mat_stack();
        gGeoTempState.type = gCurrAnimType;
        gGeoTempState.enabled = gCurrAnimEnabled;
        gGeoTempState.frame = gCurrAnimFrame;
        gGeoTempState.translationMultiplier = gCurrAnimTranslationMultiplier;
        gGeoTempState.attribute = gCurrAnimAttribute;
        gGeoTempState.data = gCurrAnimData;
        gCurrAnimType = ANIM_TYPE_NONE;
        gCurGraphNodeHeldObject = (void *) node;
        if (node->objNode->header.gfx.animInfo.curAnim != NULL) {
            geo_set_animation_globals(&node->objNode->header.gfx.animInfo, (node->objNode->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0);
        }

        geo_process_node_and_siblings(node->objNode->header.gfx.sharedChild);
        gCurGraphNodeHeldObject = NULL;
        gCurrAnimType = gGeoTempState.type;
        gCurrAnimEnabled = gGeoTempState.enabled;
        gCurrAnimFrame = gGeoTempState.frame;
        gCurrAnimTranslationMultiplier = gGeoTempState.translationMultiplier;
        gCurrAnimAttribute = gGeoTempState.attribute;
        gCurrAnimData = gGeoTempState.data;
        gMatStackIndex--;
    }

    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

#include <stdio.h>

/**
 * Advanced lighting engine
 * Processes a scene light, setting its position and other properties
 */
void geo_process_scene_light(struct GraphNodeSceneLight *node)
{    
    switch (node->lightType)
    {
        case LIGHT_TYPE_DIRECTIONAL:
        if (!gOverrideDirectionalLight) {
            for (s32 i = 0; i < 3; i++) {
                RGBLight[i] = node->color[i];
            }
            // "Oscuro" = que la suma de los 3 canales sea despreciable.
            u32 total = (u32)node->color[0] + (u32)node->color[1] + (u32)node->color[2];
            gUseGlobalLightAsCamLight = (total == 0);   // o total < 30 si quieres tolerancia
            gLightDir[0] = node->a;
            gLightDir[1] = node->b;
            gLightDir[2] = node->c;
        }
        break;
        case LIGHT_TYPE_POINT:
        case LIGHT_TYPE_POINT_OCCLUDE:
            break;
        case LIGHT_TYPE_AMBIENT:
            if (!gOverrideAmbientLight)
            {
                // Set the ambient light color
                for (s32 i = 0; i < 3; i++) {
                    RGBAmbient[i] = node->color[i];
                }
            }
            break;

        case LIGHT_TYPE_CAMERA:
            for (s32 i = 0; i < 3; i++) {
                CamLightCol[i] = node->color[i];
            }
            // a -> Distancia mínima con 100% de brillo (multiplicada por 100.0)
            camLightMinDist = (node->a != 0) ? ((f32)node->a * 100.0f) : 0.0f;
            // b -> Distancia máxima donde el fade llega a 0
            camLightMaxDist = (node->b != 0) ? ((f32)node->b * 100.0f) : 0.0f;
            
            gUseCameraLightAsPointLight = (camLightMaxDist > 0.0f);
            camLightBrightness = node->c;
            break;

        case LIGHT_TYPE_VANILLA_STYLE:
            for (s32 i = 0; i < 3; i++) {
                RGBLight[i] = node->color[i];
            }
            Vec3f transformedLightDirection;
            globalLightDirection[0] = node->a;
            globalLightDirection[1] = node->b;
            globalLightDirection[2] = node->c;
            linear_mtxf_transpose_mul_vec3f(gCameraTransform, transformedLightDirection, globalLightDirection);
            gLightDir[0] = (s8)(transformedLightDirection[0]);
            gLightDir[1] = (s8)(transformedLightDirection[1]);
            gLightDir[2] = (s8)(transformedLightDirection[2]);
            break;
        }

    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}

void geo_process_light_pos(struct GraphNodeLightPos *node)
{
    for (s32 i = 0; i < 3; i++) {
        node->worldPos[i] = gLightPosition[i];
    }
    bDirectionalLightAsPoint = TRUE;
}

/**
 * Processes the children of the given GraphNode if it has any
 */
void geo_try_process_children(struct GraphNode *node) {
    if (node->children != NULL) {
        geo_process_node_and_siblings(node->children);
    }
}

// Una función que recibe un puntero a un nodo y no devuelve nada
typedef void (*GeoProcessFunc)(struct GraphNode *);

static const GeoProcessFunc sGeoProcessJumpTable[] = {
    [GRAPH_NODE_TYPE_ORTHO_PROJECTION]     = (GeoProcessFunc) geo_process_ortho_projection,
    [GRAPH_NODE_TYPE_PERSPECTIVE]          = (GeoProcessFunc) geo_process_perspective,
    [GRAPH_NODE_TYPE_MASTER_LIST]          = (GeoProcessFunc) geo_process_master_list,
    [GRAPH_NODE_TYPE_SWITCH_CASE]          = (GeoProcessFunc) geo_process_switch,
    [GRAPH_NODE_TYPE_CAMERA]               = (GeoProcessFunc) geo_process_camera,
    [GRAPH_NODE_TYPE_TRANSLATION_ROTATION] = (GeoProcessFunc) geo_process_translation_rotation,
    [GRAPH_NODE_TYPE_TRANSLATION]          = (GeoProcessFunc) geo_process_translation,
    [GRAPH_NODE_TYPE_ROTATION]             = (GeoProcessFunc) geo_process_rotation,
    [GRAPH_NODE_TYPE_OBJECT]               = (GeoProcessFunc) geo_process_object,
    [GRAPH_NODE_TYPE_ANIMATED_PART]        = (GeoProcessFunc) geo_process_animated_part,
    [GRAPH_NODE_TYPE_BILLBOARD]            = (GeoProcessFunc) geo_process_billboard,
    [GRAPH_NODE_TYPE_DISPLAY_LIST]         = (GeoProcessFunc) geo_process_display_list,
    [GRAPH_NODE_TYPE_SCALE]                = (GeoProcessFunc) geo_process_scale,
    [GRAPH_NODE_TYPE_SHADOW]               = (GeoProcessFunc) geo_process_shadow,
    [GRAPH_NODE_TYPE_OBJECT_PARENT]        = (GeoProcessFunc) geo_process_object_parent,
    [GRAPH_NODE_TYPE_GENERATED_LIST]       = (GeoProcessFunc) geo_process_generated_list,
    [GRAPH_NODE_TYPE_BACKGROUND]           = (GeoProcessFunc) geo_process_background,
    [GRAPH_NODE_TYPE_HELD_OBJ]             = (GeoProcessFunc) geo_process_held_object,
    [GRAPH_NODE_TYPE_BONE]                 = (GeoProcessFunc) geo_process_bone,
    // Tus nuevos nodos del motor de iluminación
    [GRAPH_NODE_TYPE_SCENE_LIGHT]          = (GeoProcessFunc) geo_process_scene_light,
    [GRAPH_NODE_TYPE_LIGHT_POS]            = (GeoProcessFunc) geo_process_light_pos,
};

// Definimos el conteo para seguridad en el loop
#define GRAPH_NODE_TYPE_COUNT (sizeof(sGeoProcessJumpTable) / sizeof(sGeoProcessJumpTable[0]))

/**
 * Process a generic geo node and its siblings.
 * The first argument is the start node, and all its siblings will
 * be iterated over.
 */
void geo_process_node_and_siblings(struct GraphNode *firstNode) {
    s32 iterateChildren = TRUE;
    struct GraphNode *curGraphNode = firstNode;
    struct GraphNode *parent = curGraphNode->parent;

    if (parent != NULL) {
        iterateChildren = (parent->type != GRAPH_NODE_TYPE_SWITCH_CASE);
    }

    do {
        if (curGraphNode->flags & GRAPH_RENDER_ACTIVE) {
            if (curGraphNode->flags & GRAPH_RENDER_CHILDREN_FIRST) {
                geo_try_process_children(curGraphNode);
            } else {
                // --- OPTIMIZACIÓN CON ARRAY (JUMP TABLE) ---
                if ((u32)curGraphNode->type < GRAPH_NODE_TYPE_COUNT && sGeoProcessJumpTable[curGraphNode->type]) {
                    sGeoProcessJumpTable[curGraphNode->type](curGraphNode);
                } else {
                    // Fallback para tipos desconocidos o sin función asignada
                    geo_try_process_children(curGraphNode);
                }
            }
        } else {
            if (curGraphNode->type == GRAPH_NODE_TYPE_OBJECT) {
                ((struct GraphNodeObject *) curGraphNode)->throwMatrix = NULL;
            }
        }
    } while (iterateChildren && (curGraphNode = curGraphNode->next) != firstNode);
}

/**
 * Process a root node. This is the entry point for processing the scene graph.
 * The root node itself sets up the viewport, then all its children are processed
 * to set up the projection and draw display lists.
 */
void geo_process_root(struct GraphNodeRoot *node, Vp *b, Vp *c, s32 clearColor) {
    if (!(node->node.flags & GRAPH_RENDER_ACTIVE)) return;

    Vp *viewport = alloc_display_list(sizeof(*viewport));
    gDisplayListHeap = alloc_only_pool_init(main_pool_available() - sizeof(struct AllocOnlyPool), MEMORY_POOL_LEFT);
    Mtx *initialMatrix = alloc_display_list(sizeof(*initialMatrix));
    gCurLookAt = (LookAt*)alloc_display_list(sizeof(LookAt));
    bzero(gCurLookAt, sizeof(LookAt));
    gCurLookAt->l[1].l.col[1] = 0x80;
    gCurLookAt->l[1].l.colc[1] = 0x80;
    gMatStackIndex = 0;
    gCurrAnimType = ANIM_TYPE_NONE;
    vec3s_set(viewport->vp.vtrans, node->x * 4, node->y * 4, 511);
    vec3s_set(viewport->vp.vscale, node->width * 4, node->height * 4, 511);

    if (b != NULL) {
        clear_framebuffer(clearColor);
        make_viewport_clip_rect(b);
        *viewport = *b;
    } else if (c != NULL) {
        clear_framebuffer(clearColor);
        make_viewport_clip_rect(c);
    }

    mtxf_identity(gMatStack[gMatStackIndex]);
    mtxf_to_mtx(initialMatrix, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = initialMatrix;
    gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(viewport));
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(gMatStackFixed[gMatStackIndex]),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gCurGraphNodeRoot = node;

    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }

    gCurGraphNodeRoot = NULL;
#ifdef VANILLA_DEBUG
    if (gShowDebugText) {
        print_text_fmt_int(180, 36, "MEM %d", gDisplayListHeap->totalSpace - gDisplayListHeap->usedSpace);
    }
#endif
    main_pool_free(gDisplayListHeap);
}

Gfx *background_translate(s32 callContext, struct GraphNode *node, UNUSED f32 b[4][4]) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) node;
        f32 intensity = (f32)asGenerated->parameter / 1000.0f;

        struct GraphNodeTranslation *transNode = (struct GraphNodeTranslation *) node->next;
        
        transNode->translation[0] = camera_pos[0] * intensity;
        transNode->translation[1] = camera_pos[1] * intensity;
        transNode->translation[2] = camera_pos[2] * intensity;
    }
    return NULL;
}