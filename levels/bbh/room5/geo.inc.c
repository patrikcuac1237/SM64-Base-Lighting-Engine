#include "src/game/envfx_snow.h"

const GeoLayout room5_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, room5_bbh_geo_005_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, room5_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
