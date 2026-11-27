// reds_star_marker.inc.c
// Filename is abbreviated to prevent compiler seg fault
u8 BlueColor[3];
void bhv_red_coin_star_marker_init(void) {
    BlueColor[0] = 30;
    BlueColor[1] = 50;
    BlueColor[2] = 230;
    o->header.gfx.scale[2] = 0.75f;
    o->oOpacity = 175;
    //emit_light1(o->header.gfx.pos, BlueColor, 1, 1500.f, 2);
}
