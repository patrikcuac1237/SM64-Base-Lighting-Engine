#include "src/game/envfx_snow.h"

const GeoLayout bullet_bill_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_NODE_START(),
		GEO_OPEN_NODE(),
			GEO_SHADOW(1, 150, 420),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, bullet_bill_000_displaylist_mesh_layer_1_with_revert),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
