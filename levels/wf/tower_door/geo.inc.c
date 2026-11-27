#include "src/game/envfx_snow.h"

const GeoLayout wf_tower_door_geo[] = {
	GEO_CULLING_RADIUS(320),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(320),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, tower_door_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tower_door_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
