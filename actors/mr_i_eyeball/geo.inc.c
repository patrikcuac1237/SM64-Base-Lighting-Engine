#include "src/game/envfx_snow.h"

const GeoLayout mr_i_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 155, 200),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, mr_i_eyeball_000_displaylist_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mr_i_eyeball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
