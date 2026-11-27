#include "src/game/envfx_snow.h"

const GeoLayout castle_inside_area_3_rtx2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX2_skinned_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX2_skinned_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, RTX2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
