#include "src/game/envfx_snow.h"

const GeoLayout hmc_room4_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room4_hmc_geo_005_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room4_hmc_geo_005_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
