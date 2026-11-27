#include "src/game/envfx_snow.h"

const GeoLayout totwc_cloud_floor_skybox_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_ASM(950, background_translate),
		GEO_TRANSLATE_NODE(0, 0, 0, 0),
        GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, totwc_cloud_floor_skybox_Icosphere_mesh_layer_1_with_revert),
        GEO_CLOSE_NODE(),
	GEO_END(),
};
