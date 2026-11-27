#include "src/game/envfx_snow.h"

const GeoLayout castle_geo_001940[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(550),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, water_level_pillar_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, water_level_pillar_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
