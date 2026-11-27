#include "src/game/envfx_snow.h"

const GeoLayout black_background_geo[] = {
	GEO_CULLING_RADIUS(2000),
    GEO_OPEN_NODE(),
		GEO_ASM(1000, background_translate),
		GEO_TRANSLATE_NODE(0, 0, 0, 0),
        GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, black_background_seg7_mesh_layer_1_with_revert),
        GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_END(),
};
