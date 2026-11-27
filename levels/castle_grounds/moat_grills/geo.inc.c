#include "src/game/envfx_snow.h"

const GeoLayout castle_grounds_geo_00070C[] = {
	GEO_CULLING_RADIUS(15000),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, moat_grills_000_displaylist_mesh_layer_5),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, moat_grills_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
