#include "src/game/envfx_snow.h"

const GeoLayout totwc_levell_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, totwc_levell_skinned_mesh_layer_5_with_revert),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, totwc_levell_skinned_mesh_layer_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
