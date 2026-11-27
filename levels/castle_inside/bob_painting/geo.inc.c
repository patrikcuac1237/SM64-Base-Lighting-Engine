#include "src/game/envfx_snow.h"

const GeoLayout bob_painting_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bob_painting_paintings_dl_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bob_painting_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
