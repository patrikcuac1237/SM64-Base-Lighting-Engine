#include "src/game/envfx_snow.h"

const GeoLayout hmc_room2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_room2_hmc_geo_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_room2_hmc_geo_003_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_room2_hmc_geo_003_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
