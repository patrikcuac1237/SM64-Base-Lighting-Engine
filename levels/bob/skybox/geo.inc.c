#include "src/game/envfx_snow.h"

const GeoLayout bob_skybox_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, skybox_geolayout_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, skybox_geolayout_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, skybox_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, skybox_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
