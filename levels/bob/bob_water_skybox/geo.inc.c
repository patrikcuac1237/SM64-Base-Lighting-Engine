#include "src/game/envfx_snow.h"

const GeoLayout bob_water_skybox_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(950, background_translate),
		GEO_TRANSLATE_NODE(0, 0, 0, 0),
        GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_OPAQUE,  bob_water_skybox_Icosphere_mesh_layer_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
