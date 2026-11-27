#include "src/game/envfx_snow.h"

const GeoLayout mist_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_NODE_START(),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_update_layer_transparency),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mist_001_displaylist_mesh_layer_5_with_revert),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
