#include "src/game/envfx_snow.h"

const GeoLayout castle_inside_area_3_rtx1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_skinned_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_skinned_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, RTX1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
