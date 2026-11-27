#include "src/game/envfx_snow.h"

const GeoLayout hmc_geo_0005D0[] = {
   GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, elevator_platform_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, elevator_platform_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
