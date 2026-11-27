#include "src/game/envfx_snow.h"

const GeoLayout wtr_lvl_wtr_geo[] = {
	GEO_CULLING_RADIUS(25000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, water_level_water_dl_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, water_level_water_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
