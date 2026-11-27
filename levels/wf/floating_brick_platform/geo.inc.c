#include "src/game/envfx_snow.h"

const GeoLayout floating_brick_platform_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(1000),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, floating_brick_platform_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, floating_brick_platform_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
