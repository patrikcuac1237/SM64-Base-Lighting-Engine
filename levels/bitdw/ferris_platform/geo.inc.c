#include "src/game/envfx_snow.h"

const GeoLayout geo_bitdw_000588[] = {
	GEO_CULLING_RADIUS(600),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, ferris_platform_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ferris_platform_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
