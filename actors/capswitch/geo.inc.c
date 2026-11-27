#include "src/game/envfx_snow.h"

const GeoLayout capswitch_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(600),
		GEO_OPEN_NODE(),
			GEO_OPEN_NODE(),
				GEO_ASM(1, geo_apply_primitive_color),
			GEO_CLOSE_NODE(),
			GEO_ASM(0, geo_object_fix_2cycle_issue),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, capswitch_000_displaylist_001_mesh_layer_1_with_revert),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
