#include "src/game/envfx_snow.h"

const GeoLayout LevelRTXGeoLayout6[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo6_R4_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo6_R4_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, LevelRTXGeo6_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, LevelRTXGeo6_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
