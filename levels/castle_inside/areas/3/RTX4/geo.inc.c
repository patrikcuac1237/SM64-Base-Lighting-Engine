#include "src/game/envfx_snow.h"

const GeoLayout castle_inside_area_3_rtx4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX4_skinned_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, RTX4_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
