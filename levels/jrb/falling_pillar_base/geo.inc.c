#include "src/game/envfx_snow.h"

const GeoLayout jrb_geo_000918[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, falling_pillar_base_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, falling_pillar_base_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
