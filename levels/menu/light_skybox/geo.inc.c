#include "src/game/envfx_snow.h"

const GeoLayout light_skybox_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, background_translate),
		GEO_DISPLAY_LIST(LAYER_FORCE, light_skybox_Cube_mesh_layer_0_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
