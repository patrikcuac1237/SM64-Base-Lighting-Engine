// 0x0E0005E8
const GeoLayout hmc_geo_0005E8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room_hmc_geo_000_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room_hmc_geo_000_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room_hmc_geo_000_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000618
const GeoLayout hmc_geo_000618[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room1_hmc_geo_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room1_hmc_geo_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room1_hmc_geo_001_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000658
const GeoLayout hmc_geo_000658[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room2_hmc_geo_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room2_hmc_geo_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room2_hmc_geo_003_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_water_water_mesh_layer_5),
		
		
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0006A8
const GeoLayout hmc_geo_0006A8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room3_hmc_geo_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room3_hmc_geo_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room3_hmc_geo_004_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0006E0
const GeoLayout hmc_geo_0006E0[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room4_hmc_geo_005_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room4_hmc_geo_005_mesh_layer_4),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000700
const GeoLayout hmc_geo_000700[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room5_hmc_geo_006_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room5_hmc_geo_006_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room5_hmc_geo_006_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_water_water_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000748
const GeoLayout hmc_geo_000748[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room6_hmc_geo_007_mesh_layer_1),
      GEO_ASM(0, geo_painting_update),
      GEO_ASM(PAINTING_ID(0, 0), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000770
const GeoLayout hmc_geo_000770[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room7_hmc_geo_008_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room7_hmc_geo_008_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000798
const GeoLayout hmc_geo_000798[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room_hmc_geo_000_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room_hmc_geo_000_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room_hmc_geo_000_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room1_hmc_geo_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room1_hmc_geo_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room1_hmc_geo_001_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0007F8
const GeoLayout hmc_geo_0007F8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room_hmc_geo_000_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room_hmc_geo_000_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room_hmc_geo_000_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room3_hmc_geo_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room3_hmc_geo_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room3_hmc_geo_004_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000850
const GeoLayout hmc_geo_000850[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room1_hmc_geo_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room1_hmc_geo_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room1_hmc_geo_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room2_hmc_geo_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room2_hmc_geo_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room2_hmc_geo_003_mesh_layer_5),
		
		
      //GEO_ASM(   0, geo_movtex_pause_control),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0008D0
const GeoLayout hmc_geo_0008D0[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room1_hmc_geo_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room1_hmc_geo_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room1_hmc_geo_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room3_hmc_geo_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room3_hmc_geo_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room3_hmc_geo_004_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000938
const GeoLayout hmc_geo_000938[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room2_hmc_geo_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room2_hmc_geo_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room2_hmc_geo_003_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room4_hmc_geo_005_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room4_hmc_geo_005_mesh_layer_4),
		
		
      //GEO_ASM(   0, geo_movtex_pause_control),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000998
const GeoLayout hmc_geo_000998[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room2_hmc_geo_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room2_hmc_geo_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room2_hmc_geo_003_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room5_hmc_geo_006_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room5_hmc_geo_006_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room5_hmc_geo_006_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_water_water_mesh_layer_5),
		
		
      //GEO_ASM(   0, geo_movtex_pause_control),
		
		
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000A18
const GeoLayout hmc_geo_000A18[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room3_hmc_geo_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room3_hmc_geo_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room3_hmc_geo_004_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room5_hmc_geo_006_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room5_hmc_geo_006_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room5_hmc_geo_006_mesh_layer_5),
		//GEO_ASM(   0, geo_movtex_pause_control),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_water_water_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000A88
const GeoLayout hmc_geo_000A88[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room5_hmc_geo_006_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room5_hmc_geo_006_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room5_hmc_geo_006_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room6_hmc_geo_007_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_water_water_mesh_layer_5),
      GEO_ASM(   0, geo_painting_update),
      GEO_ASM(   PAINTING_ID(0, 0), geo_painting_draw),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000AE8
const GeoLayout hmc_geo_000AE8[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room5_hmc_geo_006_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room5_hmc_geo_006_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room5_hmc_geo_006_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room7_hmc_geo_008_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room7_hmc_geo_008_mesh_layer_5),
		//GEO_ASM(   0, geo_movtex_pause_control),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_water_water_mesh_layer_5),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000B48
const GeoLayout hmc_geo_000B48[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room3_hmc_geo_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room3_hmc_geo_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room3_hmc_geo_004_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room4_hmc_geo_005_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room4_hmc_geo_005_mesh_layer_4),
      GEO_SCENE_LIGHT(LIGHT_TYPE_DIRECTIONAL, 55, 45, 15, 0, 90, 0),
      GEO_SCENE_LIGHT(LIGHT_TYPE_AMBIENT, 15, 15, 15, 1, 0, 8),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000B90
const GeoLayout hmc_geo_000B90[] = {
    GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
    GEO_OPEN_NODE(),
        GEO_ZBUFFER(0),
         GEO_OPEN_NODE(),
            GEO_NODE_ORTHO(100),
            GEO_OPEN_NODE(),
               GEO_BACKGROUND(BACKGROUND_OCEAN_SKY, geo_skybox_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
         GEO_ZBUFFER(1),
        GEO_OPEN_NODE(),
            GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 12800, geo_camera_fov),
            GEO_OPEN_NODE(),
                GEO_CAMERA(16, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
                GEO_OPEN_NODE(),
                    GEO_SWITCH_CASE(18, geo_switch_area),
                    GEO_OPEN_NODE(),
                        GEO_BRANCH(1, hmc_geo_0005E8), // 0x0E0005E8
                        GEO_BRANCH(1, hmc_geo_000618), // 0x0E000618
                        GEO_BRANCH(1, hmc_geo_000658), // 0x0E000658
                        GEO_BRANCH(1, hmc_geo_0006A8), // 0x0E0006A8
                        GEO_BRANCH(1, hmc_geo_0006E0), // 0x0E0006E0
                        GEO_BRANCH(1, hmc_geo_000700), // 0x0E000700
                        GEO_BRANCH(1, hmc_geo_000748), // 0x0E000748
                        GEO_BRANCH(1, hmc_geo_000770), // 0x0E000770
                        GEO_BRANCH(1, hmc_geo_000798), // 0x0E000798
                        GEO_BRANCH(1, hmc_geo_0007F8), // 0x0E0007F8
                        GEO_BRANCH(1, hmc_geo_000850), // 0x0E000850
                        GEO_BRANCH(1, hmc_geo_0008D0), // 0x0E0008D0
                        GEO_BRANCH(1, hmc_geo_000938), // 0x0E000938
                        GEO_BRANCH(1, hmc_geo_000998), // 0x0E000998
                        GEO_BRANCH(1, hmc_geo_000A18), // 0x0E000A18
                        GEO_BRANCH(1, hmc_geo_000A88), // 0x0E000A88
                        GEO_BRANCH(1, hmc_geo_000AE8), // 0x0E000AE8
                        GEO_BRANCH(1, hmc_geo_000B48), // 0x0E000B48
                    GEO_CLOSE_NODE(),
                    GEO_RENDER_OBJ(),
                    GEO_BRANCH(0, dark_background_geo),
                    GEO_ASM(0, geo_envfx_main),
                GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_END(),
};
