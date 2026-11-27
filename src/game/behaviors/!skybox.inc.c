 // !skybox.inc.c

void bhv_custom_skybox_loop(void) {
    cur_obj_scale(1.0),
    o->oPosX = gLakituState.pos[0];
    o->oPosY = gLakituState.pos[1];
    o->oPosZ = gLakituState.pos[2];
    o->oDrawingDistance = 200000.f;
}

void bhv_torch_loop(void) {}

void bhv_Area2_loop() {
    load_object_collision_model();
}

void bhv_CastleLight_Loop() {
    o->oFlags |= OBJ_FLAG_COMPUTE_DIST_TO_MARIO;
    o->oFlags &= ~OBJ_FLAG_EMIT_LIGHT;
    if (gCurrLevelNum == LEVEL_CASTLE) {
        if (gMarioState->pos[0] > 1155) {
            if (gMarioState->pos[1] < 640 && gMarioState->pos[0] > 2000) {
                o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
                o->oLightColor = 0xFFFFFF00;    
                o->oLightBrightness = 10;
                o->oLightMaxDist = 15000;
                o->header.gfx.pos[0] = gMarioState->pos[0] + 25;
                o->header.gfx.pos[1] = gMarioState->pos[1] + 100;
                o->header.gfx.pos[2] = -1750;
                o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
            }
        }
    } else if (gCurrLevelNum == LEVEL_CCM) {
        o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
        if (gMarioState->pos[1] < -3825) {
            o->header.gfx.pos[1] = gMarioState->pos[1] + 250;
        } else {
            o->header.gfx.pos[1] = -3825;
        }
        o->oLightBrightness = 10;
        o->oLightColor = 0xFFF0A400;
        o->oLightMaxDist = 15000;   
    } else if (gCurrLevelNum == LEVEL_BBH) {
        o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
        o->oLightBrightness = 10;
        o->oLightMaxDist = 750;
        o->oLightColor = 0xFFF40000;
        if (gMarioState->pos[1] > 700.0f && o->header.gfx.pos[1] < 700) {
            o->oFlags &= ~OBJ_FLAG_EMIT_LIGHT;
        } else if (gMarioState->pos[1] < 700.0f && o->header.gfx.pos[1] > 700){
            o->oFlags &= ~OBJ_FLAG_EMIT_LIGHT;
        }
    } else if (gCurrLevelNum == LEVEL_BITDW) {
        if (o->oDistanceToMario < 1000.f) {
            o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
        } else {
            o->oFlags &= ~OBJ_FLAG_EMIT_LIGHT;
        }
        if (gMarioState->pos[1] < 1600 && gMarioState->pos[1] > -155) {
            o->header.gfx.pos[1] = gMarioState->pos[1];
        } else if (gMarioState->pos[1] < -155) {
            o->header.gfx.pos[1] = -155;
        } else if (gMarioState->pos[1] > 1600) {
            o->header.gfx.pos[1] = 1600;
        }
        o->oLightBrightness = 10;
        o->oLightColor = 0x9DD5FF00;
        o->oLightMaxDist = 1000;
    } else if (gCurrLevelNum == LEVEL_HMC) {
        o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
    }
    o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
}

void bhv_Aquariums_Lights_loop() {
    const u8 RGBMultAdd[3] = {0xFF, 0xFF, 0xFF};
    o->oFlags &= ~OBJ_FLAG_EMIT_LIGHT;
    if (gMarioState->pos[0] > 1155) {
        o->header.gfx.pos[0] = 2920;
        o->header.gfx.pos[1] = 1500;
        o->header.gfx.pos[2] = -200;
        o->oLightColor = 0x001F7F00;
        if (gMarioState->pos[1] < 640 && gMarioState->pos[0] > 2000) {
            addObjectPointLight((u8 *)RGBMultAdd, 15000, 10);
            o->oLightBrightness = 1;
            o->oLightMaxDist = 1500;
            o->header.gfx.pos[0] = gMarioState->pos[0] - 25;
            o->header.gfx.pos[1] = gMarioState->pos[1] + 100;
            o->header.gfx.pos[2] = 1300;
            o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
        }
    } else {
        o->oLightColor = 0x00000000;
    }
} 

void bhv_snowman_base_loop() {
    load_object_collision_model();
}

void bhv_bbh_red_light_loop() {
    if (gCurrLevelNum == LEVEL_BBH) {
        if (gMarioState->pos[1] > 750) {
            o->header.gfx.pos[1] = 1225;
        } else {
            o->header.gfx.pos[1] = 390;
        }
        o->oLightBrightness = 10;
    } 
}

void bhv_jrb_room_light() {
    o->oLightColor = 0xFFF0A400;
    o->oLightMaxDist = (((o->oBehParams & 0xFF000000) >> 24) * 10);
    o->oLightBrightness = ((o->oBehParams & 0x00FF0000) >> 16);
}

void bhv_volcano_light_loop() {
    o->header.gfx.pos[0] = gMarioState->pos[0];
    o->header.gfx.pos[1] = -200;
    o->header.gfx.pos[2] = gMarioState->pos[2];
}

void bhv_mansion_light_loop(){
}

void bhv_light_loop(void) {
    o->oFlags = OBJ_FLAG_EMIT_LIGHT;
    u8 RGBMultAdd[3];
    o->oLightMaxDist = (s16)(((((o->oBehParams & 0x7f000000) >> 24) * 20.f) + 120.f) * 2.f);    
    RGBMultAdd[0] = ((o->oBehParams & 0x00FF0000) >> 16);
    RGBMultAdd[1] = ((o->oBehParams & 0x0000FF00) >> 8);
    RGBMultAdd[2] = ((o->oBehParams & 0x000000FF));
    o->oLightColor = (RGBMultAdd[0] << 24) | (RGBMultAdd[1] << 16) | (RGBMultAdd[2] << 8);
    o->oLightBrightness = 10;
}

void bhv_hmc_lights_loop(void) {
    
}

void bhv_hmc_red_lights_loop(void) {
    
}
void bhv_bitdw_light_loop(void)
{
    if (gCurrLevelNum == LEVEL_BITDW) {
        //addRelativeLight(o, (u8*)sBitdwLightColor, 1000, 10, -10, -155, 1600);
    }
}

void bhv_ccm_cabin_light(void)
{
    if (gCurrAreaIndex == 2)
    {
        //addRelativeLight(o, (u8*)cabinLight, 1500, 10, 250, -6000, -3825);
    }
}

void bhv_bob_star_zone(void) 
{
    struct Object *ChainChompStar;
    struct Object *ChainChompStarCollect;
    ChainChompStar = cur_obj_nearest_object_with_behavior(bhvStar);
    ChainChompStarCollect = cur_obj_nearest_object_with_behavior(bhvCelebrationStar);
    if (ChainChompStarCollect != NULL || (ChainChompStar != NULL && (ChainChompStar->header.gfx.sharedChild == gLoadedGraphNodes[MODEL_STAR])))
    {
        o->oAnimState = 1;
    }
    else if (ChainChompStar == NULL)
    {
        o->oAnimState = 0;
    }
}