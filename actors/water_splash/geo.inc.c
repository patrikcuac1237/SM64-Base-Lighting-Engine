#include "src/game/envfx_snow.h"

const GeoLayout water_splash_000_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__0_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_000_switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__1_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_000_switch_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__2_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_000_switch_opt4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__3_3),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_000_switch_opt5[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__4_4),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_000_switch_opt6[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__5_5),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_000_switch_opt7[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__6_6),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_000_switch_opt8[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4_mat_override__7_7),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout water_splash_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(8, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_000_displaylist_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, water_splash_000_switch_opt1),
			GEO_BRANCH(1, water_splash_000_switch_opt2),
			GEO_BRANCH(1, water_splash_000_switch_opt3),
			GEO_BRANCH(1, water_splash_000_switch_opt4),
			GEO_BRANCH(1, water_splash_000_switch_opt5),
			GEO_BRANCH(1, water_splash_000_switch_opt6),
			GEO_BRANCH(1, water_splash_000_switch_opt7),
			GEO_BRANCH(1, water_splash_000_switch_opt8),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, water_splash_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
