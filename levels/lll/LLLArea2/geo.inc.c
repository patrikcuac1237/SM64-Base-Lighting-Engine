#include "src/game/envfx_snow.h"

const GeoLayout LLLArea2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LLLArea2_lvl_geo_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, LLLArea2_lvl_geo_mesh_layer_5_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LLLArea2_lvl_geo_mesh_layer_4_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
