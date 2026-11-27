#include "src/game/envfx_snow.h"

const GeoLayout exclamation_box_outline_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(300),
		GEO_OPEN_NODE(),
			GEO_SHADOW(0, 180, 70),
			GEO_OPEN_NODE(),
				GEO_OPEN_NODE(),
					GEO_ASM(0, geo_apply_primitive_color),
				GEO_CLOSE_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, exclamation_box_outline_002_displaylist_mesh_layer_5_with_revert),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
