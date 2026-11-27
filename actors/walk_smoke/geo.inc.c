#include "src/game/envfx_snow.h"

const GeoLayout walk_smoke_geo_opt_1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_opt_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout walk_smoke_geo_opt_2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_opt_2_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout walk_smoke_geo_opt_3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_opt_3_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout walk_smoke_geo_opt_4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_opt_4_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout walk_smoke_geo_opt_5[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_opt_5_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout walk_smoke_geo_opt_6[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_opt_6_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout walk_smoke_geo_opt_7[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_opt_7_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout walk_smoke_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(7, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, walk_smoke_000_displaylist_mesh_layer_5_with_revert),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, walk_smoke_geo_opt_1),
			GEO_BRANCH(1, walk_smoke_geo_opt_2),
			GEO_BRANCH(1, walk_smoke_geo_opt_3),
			GEO_BRANCH(1, walk_smoke_geo_opt_4),
			GEO_BRANCH(1, walk_smoke_geo_opt_5),
			GEO_BRANCH(1, walk_smoke_geo_opt_6),
			GEO_BRANCH(1, walk_smoke_geo_opt_7),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
