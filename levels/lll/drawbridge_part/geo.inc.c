#include "src/game/envfx_snow.h"

const GeoLayout lll_geo_000B20[] = {
   GEO_CULLING_RADIUS(850),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, drawbridge_part_000_displaylist_mesh_layer_1_with_revert),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
