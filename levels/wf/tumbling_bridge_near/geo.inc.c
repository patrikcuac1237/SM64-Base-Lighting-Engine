#include "src/game/envfx_snow.h"

const GeoLayout wf_geo_000AB0[] = {
	GEO_CULLING_RADIUS(400),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, tumbling_bridge_near_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tumbling_bridge_near_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
