// 0x0E000F30
const GeoLayout castle_geo_000F30[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(0, geo_exec_inside_castle_light),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000F70
const GeoLayout castle_geo_000F70[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo3_R6_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo3_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),      GEO_ASM(0, geo_exec_inside_castle_light),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000F88
const GeoLayout castle_geo_000F88[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo8_R5_mesh_layer_1_with_revert),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_bowser_1_painting),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000FA8
const GeoLayout castle_geo_000FA8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo4_R7_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo4_R7_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo4_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo4_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000FD0
const GeoLayout castle_geo_000FD0[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo1_R1_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo1_R1_mesh_layer_4_with_revert),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(0, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001000
const GeoLayout castle_geo_001000[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo2_R3_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo2_R3_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo2_material_revert_render_settings),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(2, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001038
const GeoLayout castle_geo_001038[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo7_R2_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo7_R2_mesh_layer_4_with_revert),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, LevelRTXGeo7_R2_mesh_layer_5_with_revert),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(3, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 25, 25, 75, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001088
const GeoLayout castle_geo_001088[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo6_R4_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo6_R4_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo6_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo6_material_revert_render_settings),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(1, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0010C8
const GeoLayout castle_geo_0010C8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo9_R8_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo9_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001110
const GeoLayout castle_geo_001110[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_ASM(0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo3_R6_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo3_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001158
const GeoLayout castle_geo_001158[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo8_R5_mesh_layer_1_with_revert),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_bowser_1_painting),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0011A8
const GeoLayout castle_geo_0011A8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo4_R7_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo4_R7_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo4_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo4_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
            GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001200
const GeoLayout castle_geo_001200[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo1_R1_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo1_R1_mesh_layer_4_with_revert),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(0, 1), geo_painting_draw),
      GEO_ASM(  0, geo_exec_inside_castle_light),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001260
const GeoLayout castle_geo_001260[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(  0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo2_R3_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo2_R3_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo2_material_revert_render_settings),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(2, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0012C8
const GeoLayout castle_geo_0012C8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(  0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo7_R2_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo7_R2_mesh_layer_4_with_revert),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, LevelRTXGeo7_R2_mesh_layer_5_with_revert),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(3, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001348
const GeoLayout castle_geo_001348[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(  0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo6_R4_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo6_R4_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo6_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo6_material_revert_render_settings),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(1, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0013B8
const GeoLayout castle_geo_0013B8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo_R_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo_R_mesh_layer_4_with_revert),
      GEO_ASM(0, geo_exec_inside_castle_light),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo4_R7_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo4_R7_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo4_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo4_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001400
const GeoLayout castle_geo_001400[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            //GEO_BACKGROUND_COLOR(0x0001),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(64, 50, 7000, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(CAMERA_MODE_FIXED, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
            GEO_OPEN_NODE(),
            GEO_SWITCH_CASE(17, geo_switch_area),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, castle_geo_000F30), // 0x0E000F30
                  GEO_BRANCH(1, castle_geo_000F70), // 0x0E000F70
                  GEO_BRANCH(1, castle_geo_000F88), // 0x0E000F88
                  GEO_BRANCH(1, castle_geo_000FA8), // 0x0E000FA8
                  GEO_BRANCH(1, castle_geo_000FD0), // 0x0E000FD0
                  GEO_BRANCH(1, castle_geo_001000), // 0x0E001000
                  GEO_BRANCH(1, castle_geo_001038), // 0x0E001038
                  GEO_BRANCH(1, castle_geo_001088), // 0x0E001088
                  GEO_BRANCH(1, castle_geo_0010C8), // 0x0E0010C8
                  GEO_BRANCH(1, castle_geo_001110), // 0x0E001110
                  GEO_BRANCH(1, castle_geo_001158), // 0x0E001158
                  GEO_BRANCH(1, castle_geo_0011A8), // 0x0E0011A8
                  GEO_BRANCH(1, castle_geo_001200), // 0x0E001200
                  GEO_BRANCH(1, castle_geo_001260), // 0x0E001260
                  GEO_BRANCH(1, castle_geo_0012C8), // 0x0E0012C8
                  GEO_BRANCH(1, castle_geo_001348), // 0x0E001348
                  GEO_BRANCH(1, castle_geo_0013B8), // 0x0E0013B8
                  GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
                  GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
                  GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 0, 0, 0),               
               GEO_CLOSE_NODE(),
               GEO_RENDER_OBJ(),
               GEO_BRANCH(0, black_background_geo),
               GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
               GEO_ASM(0, geo_object_fix_2cycle_issue),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
