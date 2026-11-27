#include "src/game/envfx_snow.h"

const GeoLayout geo_bbh_0005F8[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(300),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, tumbling_platform_near_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tumbling_platform_near_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
