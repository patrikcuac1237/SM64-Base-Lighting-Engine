#include "src/game/envfx_snow.h"

const GeoLayout room6_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, room6_bbh_geo_006_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, room6_bbh_geo_006_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
