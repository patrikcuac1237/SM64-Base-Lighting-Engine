#include "src/game/envfx_snow.h"

const GeoLayout wf_geo_000AC8[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(800),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, tumbling_bridge_far_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tumbling_bridge_far_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
