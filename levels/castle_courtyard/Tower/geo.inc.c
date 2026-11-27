#include "src/game/envfx_snow.h"

const GeoLayout castle_courtyard_tower_geo[] = {
	GEO_CULLING_RADIUS(2600),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, Tower_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, Tower_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
