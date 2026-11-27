#include "src/game/envfx_snow.h"

const GeoLayout level_geometry_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, level_geometry_castle_courtyard_level_mesh_layer_1_with_revert),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, level_geometry_castle_courtyard_level_mesh_layer_5_with_revert),
		GEO_DISPLAY_LIST(LAYER_ALPHA, level_geometry_castle_courtyard_level_mesh_layer_4_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
