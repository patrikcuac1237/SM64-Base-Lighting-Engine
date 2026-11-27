#include "src/game/envfx_snow.h"

const GeoLayout ccm_geo_0003D0[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(500),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, ropeway_lift_000_displaylist_mesh_layer_4),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, ropeway_lift_001_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ropeway_lift_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ropeway_lift_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
