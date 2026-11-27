#include "src/game/envfx_snow.h"

const GeoLayout castle_tower_geo[] = {
	GEO_CULLING_RADIUS(15000),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, castle_tower_000_displaylist_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, castle_tower_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
