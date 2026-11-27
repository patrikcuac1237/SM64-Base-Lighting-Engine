#include <PR/ultratypes.h>

#include "sm64.h"
#include "geo_misc.h"

#include "area.h"
#include "engine/math_util.h"
#include "level_update.h"
#include "levels/castle_inside/header.h"
#include "levels/castle_grounds/header.h"
#include "levels/ending/header.h"
#include "levels/rr/header.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "memory.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "save_file.h"
#include "segment2.h"
#include "levels/jrb/header.h"

/**
 * @file geo_misc.c
 * This file contains miscellaneous geo_asm scripts.
 *
 * In particular, it builds:
 *   - the light that shows the player where to look for Tower of the Wing Cap,
 *   - the flying carpets seen in Rainbow Ride, and
 *   - the end screen displaying Peach's delicious cake.
 */

#define NUM_FLYING_CARPET_VERTICES 21
extern const s16 flying_carpet_static_vertex_data[NUM_FLYING_CARPET_VERTICES];

static s16 sCurAreaTimer = 1;
static s16 sPrevAreaTimer = 0;
static s16 sFlyingCarpetRippleTimer = 0;

s8 gFlyingCarpetState;

/**
 * Create a vertex with the given parameters and insert it into `vtx` at
 * position `n`.
 *
 * Texture coordinates are s10.5 fixed-point, which means you should left-shift the actual coordinates by 5.
 */
#ifndef GBI_FLOATS
void make_vertex(Vtx *vtx, s32 n, s16 x, s16 y, s16 z, s16 tx, s16 ty, u8 r, u8 g, u8 b, u8 a) {
#else
void make_vertex(Vtx *vtx, s32 n, f32 x, f32 y, f32 z, s16 tx, s16 ty, u8 r, u8 g, u8 b, u8 a) {
#endif
    vtx[n].v.ob[0] = x;
    vtx[n].v.ob[1] = y;
    vtx[n].v.ob[2] = z;

    vtx[n].v.flag = 0;

    vtx[n].v.tc[0] = tx;
    vtx[n].v.tc[1] = ty;

    vtx[n].v.cn[0] = r;
    vtx[n].v.cn[1] = g;
    vtx[n].v.cn[2] = b;
    vtx[n].v.cn[3] = a;
}

#define NUM_STARS_REQUIRED_FOR_WING_CAP_LIGHT 10
/**
 * Create a display list for the light in the castle lobby that shows the
 * player where to look to enter Tower of the Wing Cap.
 */
#include "include/behavior_data.h"
Gfx *geo_exec_inside_castle_light(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    Gfx *displayListHead = NULL;
    Gfx *displayList = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        s32 flags = save_file_get_flags();
        if (gHudDisplay.stars >= NUM_STARS_REQUIRED_FOR_WING_CAP_LIGHT && !(flags & SAVE_FLAG_HAVE_WING_CAP)) {
            displayList = alloc_display_list(2 * sizeof(*displayList));
            s8 LightDir[3] = {0, 25, 0};
            s8 LightDir2[3] = {0, 155, 0};
            u8 RGBMultAdd[3] = {0xFF, 0xFF, 0xFF};
            u8 RGBMultAdd2[3] = {0x7F, 0x7F, 0x7F};
            addDirectionalLight(RGBMultAdd, (s8 *)LightDir, 6);
            addDirectionalLight(RGBMultAdd2, (s8 *)LightDir2, 6);
            if (displayList == NULL) {
                return NULL;
            } else {
                displayListHead = displayList;
            }
            struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
            SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_TRANSPARENT);

            gSPDisplayList(displayListHead++, dl_castle_lobby_wing_cap_light);
            gSPEndDisplayList(displayListHead);
        }
    }

    return displayList;
}

#undef NUM_STARS_REQUIRED_FOR_WING_CAP_LIGHT

Gfx *geo_exec_castle_grounds_shadows(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    Gfx *displayListHead = NULL;
    Gfx *displayList = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        s32 flags = save_file_get_flags();
        Gfx *dlToDisplay;
        if ((flags & SAVE_FLAG_MOAT_DRAINED)) {
            dlToDisplay = test_skinned_mesh_layer_1_with_revert;
        } else {
            dlToDisplay = leve_geometry_shaded_skinned_mesh_layer_1_with_revert;
        }
        displayList = alloc_display_list(2 * sizeof(*displayList));
        if (displayList == NULL) {
            return NULL;
        } else {
            displayListHead = displayList;
        }
        struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_OPAQUE);
        
        gSPDisplayList(displayListHead++, dlToDisplay);
        gSPEndDisplayList(displayListHead);
    }

    return displayList;
}

Gfx *geo_exec_castle_grounds_water_shadows(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    Gfx *displayListHead = NULL;
    Gfx *displayList = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        s32 flags = save_file_get_flags();
        Gfx *dlToDisplay;
        if ((flags & SAVE_FLAG_MOAT_DRAINED)) {
            dlToDisplay = test_skinned_mesh_layer_5_with_revert;
        } else {
            dlToDisplay = leve_geometry_shaded_skinned_mesh_layer_5_with_revert;
        }
        displayList = alloc_display_list(2 * sizeof(*displayList));
        if (displayList == NULL) {
            return NULL;
        } else {
            displayListHead = displayList;
        }
        struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_TRANSPARENT);
        
        gSPDisplayList(displayListHead++, dlToDisplay);
        gSPEndDisplayList(displayListHead);
    }

    return displayList;
}

Gfx *geo_exec_jrb_dark_area_opaques(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    Gfx *displayListHead = NULL;
    Gfx *displayList = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx *dlToDisplay;
        if ((save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_JRB)) & STAR_FLAG_ACT_1)) {
            dlToDisplay = jrbArea1_bright_skinned_mesh_layer_1_with_revert;
        } else {
            dlToDisplay = jrbArea1_skinned_mesh_layer_1_with_revert;
        }
        displayList = alloc_display_list(2 * sizeof(*displayList));
        if (displayList == NULL) {
            return NULL;
        } else {
            displayListHead = displayList;
        }
        struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_OPAQUE);
        
        gSPDisplayList(displayListHead++, dlToDisplay);
        gSPEndDisplayList(displayListHead);
    }

    return displayList;
}

Gfx *geo_exec_jrb_dark_area_transparents(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    Gfx *displayListHead = NULL;
    Gfx *displayList = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx *dlToDisplay;
        if ((save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_JRB)) & STAR_FLAG_ACT_1)) {
            dlToDisplay = jrbArea1_bright_skinned_mesh_layer_5_with_revert;
        } else {
            dlToDisplay = jrbArea1_skinned_mesh_layer_5_with_revert;
        }
        displayList = alloc_display_list(2 * sizeof(*displayList));
        if (displayList == NULL) {
            return NULL;
        } else {
            displayListHead = displayList;
        }
        struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_TRANSPARENT);
        
        gSPDisplayList(displayListHead++, dlToDisplay);
        gSPEndDisplayList(displayListHead);
    }

    return displayList;
}

Gfx *geo_exec_jrb_dark_area_alphas(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    Gfx *displayListHead = NULL;
    Gfx *displayList = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx *dlToDisplay;
        if ((save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_JRB)) & STAR_FLAG_ACT_1)) {
            dlToDisplay = jrbArea1_bright_skinned_mesh_layer_4_with_revert;
        } else {
            dlToDisplay = jrbArea1_skinned_mesh_layer_4_with_revert;
        }
        displayList = alloc_display_list(2 * sizeof(*displayList));
        if (displayList == NULL) {
            return NULL;
        } else {
            displayListHead = displayList;
        }
        struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_ALPHA);
        
        gSPDisplayList(displayListHead++, dlToDisplay);
        gSPEndDisplayList(displayListHead);
    }

    return displayList;
}
/**
 * Update static timer variables that control the flying carpets' ripple effect.
 */
Gfx *geo_exec_flying_carpet_timer_update(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext != GEO_CONTEXT_RENDER) {
        sFlyingCarpetRippleTimer = 0;
        sPrevAreaTimer = gAreaUpdateCounter - 1;
        sCurAreaTimer = gAreaUpdateCounter;
        gFlyingCarpetState = FLYING_CARPET_IDLE;
    } else {
        sPrevAreaTimer = sCurAreaTimer;
        sCurAreaTimer = gAreaUpdateCounter;
        if (sPrevAreaTimer != sCurAreaTimer) {
            sFlyingCarpetRippleTimer += 0x400;
        }
    }

    return NULL;
}

/**
 * Create a display list for a flying carpet with dynamic ripples.
 */
Gfx *geo_exec_flying_carpet_create(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    s16 n, row, col, x, y, z, tx, ty;
    Vtx *verts;
    struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;

    s16 *vertexData = segmented_to_virtual(&flying_carpet_static_vertex_data);
    Gfx *displayList = NULL;
    Gfx *displayListHead = NULL;
    struct Object *curGraphNodeObject;

    if (callContext == GEO_CONTEXT_RENDER) {
        verts = alloc_display_list(NUM_FLYING_CARPET_VERTICES * sizeof(*verts));
        displayList = alloc_display_list(7 * sizeof(*displayList));
        displayListHead = displayList;

        if (verts == NULL || displayList == NULL) {
            return NULL;
        }

        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_OPAQUE);

        for (n = 0; n <= 20; n++) {
            row = n / 3;
            col = n % 3;

            x = vertexData[n * 4 + 0];
            y = round_float(sins(sFlyingCarpetRippleTimer + (row << 12) + (col << 14)) * 20.0f);
            z = vertexData[n * 4 + 1];
            tx = vertexData[n * 4 + 2];
            ty = vertexData[n * 4 + 3];

            make_vertex(verts, n, x, y, z, tx, ty, 0, 127, 0, 255);
        }

        gSPDisplayList(displayListHead++, dl_flying_carpet_begin);

        // The forward half.
        gSPVertex(displayListHead++, verts, 12, 0);
        gSPDisplayList(displayListHead++, dl_flying_carpet_model_half);

        // The back half.
        gSPVertex(displayListHead++, verts + 9, 12, 0);
        gSPDisplayList(displayListHead++, dl_flying_carpet_model_half);

        gSPDisplayList(displayListHead++, dl_flying_carpet_end);
        gSPEndDisplayList(displayListHead);

        curGraphNodeObject = (struct Object *) gCurGraphNodeObject;
        if (gMarioObject->platform == curGraphNodeObject) {
            gFlyingCarpetState = FLYING_CARPET_MOVING_WITH_MARIO;
        } else if (curGraphNodeObject->oForwardVel != 0.0f) {
            gFlyingCarpetState = FLYING_CARPET_MOVING_WITHOUT_MARIO;
        } else {
            gFlyingCarpetState = FLYING_CARPET_IDLE;
        }
    }

    return displayList;
}

/**
 * Create a display list for the end screen with Peach's delicious cake.
 */
Gfx *geo_exec_cake_end_screen(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
    Gfx *displayList = NULL;
    Gfx *displayListHead = NULL;

    if (callContext == GEO_CONTEXT_RENDER) {
        displayList = alloc_display_list(3 * sizeof(*displayList));
        displayListHead = displayList;

        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_OPAQUE);
#if MULTILANG
        gSPDisplayList(displayListHead++, dl_cake_end_screen);
#else
        gSPDisplayList(displayListHead++, dl_proj_mtx_fullscreen);
#endif
#if MULTILANG
#ifdef EU_CUSTOM_CAKE_FIX
    gSPDisplayList(displayListHead++, dl_cake_end_screen_eu_fix);
#else
    switch (eu_get_language()) {
            case LANGUAGE_ENGLISH:
                gSPDisplayList(displayListHead++, dl_cake_end_screen_eu_english);
                break;
            case LANGUAGE_FRENCH:
                gSPDisplayList(displayListHead++, dl_cake_end_screen_eu_french );
                break;
            case LANGUAGE_GERMAN:
                gSPDisplayList(displayListHead++, dl_cake_end_screen_eu_german );
                break;
        }
#endif
#else
        gSPDisplayList(displayListHead++, dl_cake_end_screen);
#endif
        gSPEndDisplayList(displayListHead);
    }

    return displayList;
}

extern u8 RGBLight[3];
extern u8 RGBAmbient[3];
extern s8 gLightDir[3];
extern Lights1 camLight;
extern u8 CamLightCol[3];
extern u8 LowestColor[3];

Gfx *geo_apply_jrb_skybox_environment_color(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    Gfx *displayListHead = NULL;
    Gfx *displayList = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        s8 lightDir[3] = {0, 90, 25};
        for (s32 i = 0; i < 3; i++)
        {
            gLightDir[i] = lightDir[i];
        }
        
        displayList = alloc_display_list(2 * sizeof(*displayList));
        if (displayList == NULL) {
            return NULL;
        } else {
            displayListHead = displayList;
        }
        struct GraphNodeGenerated *generatedNode = (struct GraphNodeGenerated *) node;
        SET_GRAPH_NODE_LAYER(generatedNode->fnNode.node.flags, LAYER_OPAQUE);
        if ((save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_JRB)) & STAR_FLAG_ACT_1)) {
            RGBLight[0] = 0xCE;
            RGBLight[1] = 0xE0;
            RGBLight[2] = 0xF3;
            RGBAmbient[0] = 55; 
            RGBAmbient[1] = 80;
            RGBAmbient[2] = 90;
            CamLightCol[0] = 127;
            CamLightCol[1] = 127;
            CamLightCol[2] = 127;
            LowestColor[0] = 0x0D;
            LowestColor[1] = 0x13;
            LowestColor[2] = 0x0E;
            gDPSetEnvColor(displayListHead++, 255, 255, 255, 255);
        } else {
            CamLightCol[0] = 50;
            CamLightCol[1] = 50;
            CamLightCol[2] = 50;
            RGBLight[0] = 0x54;
            RGBLight[1] = 0x7B;
            RGBLight[2] = 0x5B;
            RGBAmbient[0] = 0x1C; 
            RGBAmbient[1] = 0x29;
            RGBAmbient[2] = 0x1B;
            LowestColor[0] = 0x1D;
            LowestColor[1] = 0x2A;
            LowestColor[2] = 0x30;
            gDPSetEnvColor(displayListHead++, 0x2E, 0x39, 0x19, 125);
        }
        gSPEndDisplayList(displayListHead);
    }

    return displayList;
}

Gfx *geo_jrb_switch_area(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;

    if (callContext == GEO_CONTEXT_RENDER) {
        if ((save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_JRB)) & STAR_FLAG_ACT_1)) {
            switchCase->selectedCase = 1;
        } else {    
            switchCase->selectedCase = 2;
        }
    } else {
        switchCase->selectedCase = 0;
    }

    return NULL;
}