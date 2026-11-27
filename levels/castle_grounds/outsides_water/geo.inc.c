#include "src/game/envfx_snow.h"

const GeoLayout outsides_water_geo[] = {
	GEO_CULLING_RADIUS(25000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, outsides_water_outsides_water_mesh_layer_5_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
