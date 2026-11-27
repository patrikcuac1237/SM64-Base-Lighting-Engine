#include "src/game/envfx_snow.h"

const GeoLayout bubble_geo_opt_1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bubble_000_displaylist_mesh_layer_4_opt_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout bubble_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(1, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, bubble_000_displaylist_mesh_layer_4_with_revert),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, bubble_geo_opt_1),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
