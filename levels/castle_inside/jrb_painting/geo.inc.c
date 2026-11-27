#include "src/game/envfx_snow.h"

const GeoLayout jrb_painting_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_painting_dl_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_painting_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
