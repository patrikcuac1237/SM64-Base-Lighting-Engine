// 0x0E001958
const GeoLayout castle_geo_001958[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_skinned_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_skinned_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_skinned_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001980
const GeoLayout castle_geo_001980[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_skinned_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_skinned_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_material_revert_render_settings),
      GEO_ASM(   0, geo_painting_update),
      GEO_ASM( PAINTING_ID(4, 1), geo_painting_draw),
      GEO_ASM( PAINTING_ID(5, 1), geo_painting_draw),
      GEO_ASM(   0, geo_movtex_pause_control),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0019C8
const GeoLayout castle_geo_0019C8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX2_skinned_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX2_skinned_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX2_material_revert_render_settings),
      GEO_ASM(0, geo_painting_update),
      GEO_ASM(PAINTING_ID(6, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0019F8
const GeoLayout castle_geo_0019F8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX3_skinned_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX3_skinned_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX3_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX3_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001A30
const GeoLayout castle_geo_001A30[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX4_skinned_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX4_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0x6F, 0xFF, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 5, 20, 50, 0, 0, 0),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(7, 1), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001A58
const GeoLayout castle_geo_001A58[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_skinned_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_skinned_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_skinned_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_skinned_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_skinned_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_material_revert_render_settings),
      GEO_ASM(   0, geo_painting_update),
      GEO_ASM( PAINTING_ID(4, 1), geo_painting_draw),
      GEO_ASM( PAINTING_ID(5, 1), geo_painting_draw),
      //GEO_ASM(   0, geo_movtex_pause_control),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001AB8
const GeoLayout castle_geo_001AB8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_skinned_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_skinned_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_skinned_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX4_skinned_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX4_material_revert_render_settings),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(7, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0x6F, 0xFF, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 5, 20, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001AF8
const GeoLayout castle_geo_001AF8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_skinned_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_skinned_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_skinned_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX3_skinned_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX3_skinned_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX3_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX3_material_revert_render_settings),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001B48
const GeoLayout castle_geo_001B48[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_skinned_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_skinned_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX3_skinned_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX3_skinned_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX3_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX3_material_revert_render_settings),
      GEO_ASM(   0, geo_painting_update),
      GEO_ASM( PAINTING_ID(4, 1), geo_painting_draw),
      GEO_ASM( PAINTING_ID(5, 1), geo_painting_draw),
      //GEO_ASM(   0, geo_movtex_pause_control),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001BB0
const GeoLayout castle_geo_001BB0[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_skinned_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_skinned_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX2_skinned_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX2_skinned_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX2_material_revert_render_settings),
      GEO_ASM(   0, geo_painting_update),
      GEO_ASM( PAINTING_ID(4, 1), geo_painting_draw),
      GEO_ASM( PAINTING_ID(5, 1), geo_painting_draw),
      GEO_ASM( PAINTING_ID(6, 1), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 0, 0, 0, 0, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_CAMERA, 50, 50, 50, 90, 0, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 50, 50, 50, 0, 0, 0),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001C10
const GeoLayout castle_geo_001C10[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_BACKGROUND_COLOR(0x0001),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(64, 50, 6400, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(CAMERA_MODE_CLOSE, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
            GEO_OPEN_NODE(),
               GEO_SWITCH_CASE(10, geo_switch_area),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, castle_geo_001958), // 0x0E001958
                  GEO_BRANCH(1, castle_geo_001980), // 0x0E001980
                  GEO_BRANCH(1, castle_geo_0019C8), // 0x0E0019C8
                  GEO_BRANCH(1, castle_geo_0019F8), // 0x0E0019F8
                  GEO_BRANCH(1, castle_geo_001A30), // 0x0E001A30
                  GEO_BRANCH(1, castle_geo_001A58), // 0x0E001A58
                  GEO_BRANCH(1, castle_geo_001AB8), // 0x0E001AB8
                  GEO_BRANCH(1, castle_geo_001AF8), // 0x0E001AF8
                  GEO_BRANCH(1, castle_geo_001B48), // 0x0E001B48
                  GEO_BRANCH(1, castle_geo_001BB0), // 0x0E001BB0
               GEO_CLOSE_NODE(),
               GEO_RENDER_OBJ(),
               GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
