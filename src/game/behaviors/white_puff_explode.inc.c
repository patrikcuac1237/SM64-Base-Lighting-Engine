void bhv_white_puff_exploding_loop(void) {
    if (o->oTimer == 0) {
        cur_obj_compute_vel_xz();
        // Guardamos la escala inicial
        o->oWhitePuffScaleX = o->header.gfx.scale[0];
        
        // Sólido al principio (255 = Opaco)
        o->oOpacity = 255;
    }

    // Movimiento estándar del motor
    cur_obj_move_using_vel_and_gravity();
    cur_obj_apply_drag_xz(o->oDragStrength);

    // --- 1. DESVANECIMIENTO (OPACIDAD) ---
    // Ajustado para 30 frames: 255 / 30 = 8.5. 
    // Restamos 8 por frame para que dure toda la vida del objeto.
    s32 newOpacity = 255 - (o->oTimer * 8); 
    
    if (newOpacity < 0) newOpacity = 0;
    o->oOpacity = (u8) newOpacity;

    // --- 2. CRECIMIENTO LIGERO (ESCALA) ---
    // Mantenemos el crecimiento del 5% para que se vea más grande al final (frame 30)
    f32 growthFactor = o->oWhitePuffScaleX + (o->oTimer * 0.05f);
    cur_obj_scale(growthFactor);

    // --- 3. MUERTE ---
    // Ahora el límite es 30 frames o cuando la opacidad sea 0.
    if (o->oTimer > 30 || o->oOpacity == 0) {
        obj_mark_for_deletion(o);
    }
}