#include "src/game/envfx_snow.h"

const GeoLayout ccm_water_level_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ccm_water_level_dl_mesh_layer_5_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
