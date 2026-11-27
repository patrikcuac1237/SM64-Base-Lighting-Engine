#include "src/game/envfx_snow.h"

const GeoLayout wf_tower_square[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(650),
		GEO_OPEN_NODE(),
			GEO_SHADOW(0, 200, 420),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, tower_square_000_displaylist_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tower_square_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
