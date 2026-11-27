#include "src/game/envfx_snow.h"

const GeoLayout BOB_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, BOB_bob_seg7_level_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, BOB_bob_seg7_level_mesh_layer_4_with_revert),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, BOB_bob_seg7_level_mesh_layer_5_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
