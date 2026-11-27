#include "src/game/envfx_snow.h"

const GeoLayout jrb_geo_000990[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_update_layer_transparency),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, wooden_ship_001_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wooden_ship_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
