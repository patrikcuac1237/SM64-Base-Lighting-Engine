// white_puff.inc.c

void bhv_white_puff_1_loop(void) {
    if (o->oTimer == 0) {
        obj_translate_xz_random(o, 40.0f);
        o->oPosY += 30.0f;
        
        // Sólido al nacer (255 = Opaco)
        o->oOpacity = 255; 
    }

    // --- ESCALA (Crecimiento rápido) ---
    // Frame 0: 0.5f
    // Frame 4: 1.5f (Un crecimiento equilibrado para efectos rápidos)
    cur_obj_scale(o->oTimer * 0.25f + 0.5f);

    // --- OPACIDAD (Desvanecimiento rápido) ---
    // Queremos que desaparezca en unos 8 frames.
    // 255 / 8 = ~32. Restamos 32 por cada frame.
    s32 newOpacity = 255 - (o->oTimer * 32);
    
    if (newOpacity < 0) newOpacity = 0;
    o->oOpacity = (u8) newOpacity;

    // Movimiento físico estándar
    cur_obj_move_using_fvel_and_gravity();

    // Muerte: Si ya es invisible o pasó su tiempo de vida
    if (o->oTimer > 8 || o->oOpacity <= 0) {
        obj_mark_for_deletion(o);
    }
}

void bhv_white_puff_2_loop(void) {
    if (o->oTimer == 0) {
        obj_translate_xz_random(o, 40.0f);
        
        // Sólido al nacer
        o->oOpacity = 255;
        
        // Escala inicial pequeña
        cur_obj_scale(0.5f);
    }

    // --- 1. DESVANECIMIENTO (OPACIDAD) ---
    // Queremos que desaparezca en 7 frames.
    // 255 / 7 = ~36. Restamos 36 por frame.
    s32 newOpacity = 255 - (o->oTimer * 36);
    
    if (newOpacity < 0) newOpacity = 0;
    o->oOpacity = (u8) newOpacity;

    // --- 2. CRECIMIENTO (ESCALA) ---
    // Crece de 0.5f a 1.2f aproximadamente en su corta vida.
    cur_obj_scale(0.5f + (o->oTimer * 0.1f));

    // Movimiento físico básico (si tiene velocidad)
    cur_obj_move_using_fvel_and_gravity();

    // --- 3. MUERTE ---
    // Se elimina al ser invisible o al pasar los 7 frames.
    if (o->oTimer > 7 || o->oOpacity <= 0) {
        obj_mark_for_deletion(o);
    }
}