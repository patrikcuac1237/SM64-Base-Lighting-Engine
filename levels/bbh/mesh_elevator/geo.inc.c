#include "src/game/envfx_snow.h"

const GeoLayout geo_bbh_000628[] = {
		GEO_CULLING_RADIUS(600),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, mesh_elevator_000_displaylist_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mesh_elevator_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
