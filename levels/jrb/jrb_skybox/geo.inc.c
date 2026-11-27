#include "src/game/envfx_snow.h"

const GeoLayout jrb_skybox_geo[] = {
	GEO_CULLING_RADIUS(20000),
	GEO_OPEN_NODE(),
		GEO_ASM(950, background_translate),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_skybox_Icosphere_mesh_layer_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
