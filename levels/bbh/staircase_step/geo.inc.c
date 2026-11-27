#include "src/game/envfx_snow.h"

const GeoLayout geo_bbh_0005B0[] = {
   GEO_CULLING_RADIUS(700),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, staircase_step_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, staircase_step_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
