#include "src/game/envfx_snow.h"

const GeoLayout room4_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, room4_bbh_geo_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, room4_bbh_geo_004_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
