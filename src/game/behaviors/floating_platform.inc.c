// floating_platform.inc.c

f32 floating_platform_find_home_y(void) {
    struct Surface *floor;
    f32 waterLevel  = find_water_level(o->oPosX, o->oPosZ);
    f32 floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);

    if (waterLevel > floorHeight + o->oFloatingPlatformHeightOffset) {
        o->oFloatingPlatformIsOnFloor = FALSE;
        return (waterLevel + o->oFloatingPlatformHeightOffset);
    } else {
        o->oFloatingPlatformIsOnFloor = TRUE;
        return (floorHeight + o->oFloatingPlatformHeightOffset);
    }
}

void floating_platform_act_move_to_home(void) {
    // Calculamos la posición relativa de Mario respecto a la plataforma rotada
    // sp6 en el original
    f32 relX = (gMarioObject->header.gfx.pos[0] - o->oPosX) * coss(-o->oMoveAngleYaw) 
               + (gMarioObject->header.gfx.pos[2] - o->oPosZ) * sins(-o->oMoveAngleYaw);
    // sp4 en el original
    f32 relZ = (gMarioObject->header.gfx.pos[2] - o->oPosZ) * coss(-o->oMoveAngleYaw) 
               - (gMarioObject->header.gfx.pos[0] - o->oPosX) * sins(-o->oMoveAngleYaw);

    if (gMarioObject->platform == o) {
        o->oFaceAnglePitch = relZ * 2;
        o->oFaceAngleRoll = -relX * 2;

        o->oVelY -= 1.0f;
        if (o->oVelY < 0.0f) o->oVelY = 0.0f;

        o->oFloatingPlatformMarioWeightWobbleOffset += o->oVelY;
        if (o->oFloatingPlatformMarioWeightWobbleOffset > 90.0f) {
            o->oFloatingPlatformMarioWeightWobbleOffset = 90.0f;
        }
    } else {
        o->oFaceAnglePitch /= 2;
        o->oFaceAngleRoll /= 2;
        o->oFloatingPlatformMarioWeightWobbleOffset -= 5.0f;
        o->oVelY = 10.0f;

        if (o->oFloatingPlatformMarioWeightWobbleOffset < 0.0f) {
            o->oFloatingPlatformMarioWeightWobbleOffset = 0.0f;
        }
    }

    // Aplicar la oscilación de la superficie del agua y el peso de Mario
    o->oPosY = o->oHomeY - 64.0f - o->oFloatingPlatformMarioWeightWobbleOffset 
               + sins(o->oFloatingPlatformWaterSurfaceWobbleOffset * 0x800) * 10.0f;

    o->oFloatingPlatformWaterSurfaceWobbleOffset++;
    if (o->oFloatingPlatformWaterSurfaceWobbleOffset == 32) {
        o->oFloatingPlatformWaterSurfaceWobbleOffset = 0;
    }
}

void bhv_floating_platform_loop(void) {
    o->oHomeY = floating_platform_find_home_y();

    // Importante: Si NO está en el suelo (F4 == 0), se mueve.
    if (o->oFloatingPlatformIsOnFloor == FALSE) {
        floating_platform_act_move_to_home();
    } else {
        o->oPosY = o->oHomeY;
        // Resetear inclinación si toca el suelo
        o->oFaceAnglePitch = 0;
        o->oFaceAngleRoll = 0;
    }
}