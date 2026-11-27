#include "src/game/envfx_snow.h"

const GeoLayout geo_bbh_000640[] = {
   GEO_CULLING_RADIUS(2300),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, merry_go_round_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, merry_go_round_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
