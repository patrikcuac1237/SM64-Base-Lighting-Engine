#include "src/game/envfx_snow.h"

const GeoLayout star_zone_geo1[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_zone_star_zone_mesh_layer_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};

const GeoLayout star_zone_geo[] = {
	GEO_CULLING_RADIUS(25000),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(2, geo_switch_anim_state),
		GEO_ASM(0, geo_object_fix_2cycle_issue),
		GEO_OPEN_NODE(),
			GEO_BRANCH(1, star_zone_geo1),
			GEO_BRANCH(1, star_zone_bright_geo),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};