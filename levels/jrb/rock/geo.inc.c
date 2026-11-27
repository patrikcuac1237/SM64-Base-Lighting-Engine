#include "src/game/envfx_snow.h"

const GeoLayout jrb_geo_000930[] = {
	GEO_CULLING_RADIUS(1100),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, rock_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
