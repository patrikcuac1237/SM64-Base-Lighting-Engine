#include "src/game/envfx_snow.h"

const GeoLayout rotating_hexagonal_ring_geo[] = {
	GEO_CULLING_RADIUS(2100),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, rotating_hexagonal_ring_000_displaylist_mesh_layer_1_with_revert),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
