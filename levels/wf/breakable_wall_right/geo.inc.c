#include "src/game/envfx_snow.h"

const GeoLayout wf_geo_000B78[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(750),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, breakable_wall_right_000_displaylist_mesh_layer_1_with_revert),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
