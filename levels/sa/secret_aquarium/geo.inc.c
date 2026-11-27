#include "src/game/envfx_snow.h"

const GeoLayout secret_aquarium_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, secret_aquarium_sa_seg7_dl_07002DE8_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, secret_aquarium_sa_seg7_dl_07002DE8_mesh_layer_5_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
