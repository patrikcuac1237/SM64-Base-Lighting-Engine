#include "src/game/envfx_snow.h"

const GeoLayout hmc_geo_0005A0[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(550),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, arrow_platform_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, arrow_platform_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
