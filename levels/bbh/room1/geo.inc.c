#include "src/game/envfx_snow.h"

const GeoLayout room1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, room1_bbh_geo_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, room1_bbh_geo_001_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
