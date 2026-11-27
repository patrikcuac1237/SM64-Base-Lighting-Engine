#include "src/game/envfx_snow.h"

const GeoLayout CCMArea2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, CCMArea2_skinned_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, CCMArea2_skinned_mesh_layer_4_with_revert),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, CCMArea2_skinned_mesh_layer_5_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
