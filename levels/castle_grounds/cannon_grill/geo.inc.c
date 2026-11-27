#include "src/game/envfx_snow.h"

const GeoLayout castle_grounds_geo_000724[] = {
	GEO_CULLING_RADIUS(15000),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, cannon_grill_000_displaylist_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, cannon_grill_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
