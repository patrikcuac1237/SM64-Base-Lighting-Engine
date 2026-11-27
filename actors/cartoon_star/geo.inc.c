#include "src/game/envfx_snow.h"

const GeoLayout cartoon_star_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(300),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_apply_star_primitive_color),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, cartoon_star_000_displaylist_mesh_layer_1_with_revert),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
