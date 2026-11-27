#include "src/game/envfx_snow.h"

const GeoLayout hmc_geo_000530[] = {
   GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, grill_door_000_displaylist_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, grill_door_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
