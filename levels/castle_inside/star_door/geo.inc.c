#include "src/game/envfx_snow.h"

const GeoLayout castle_geo_000F00[] = {
   GEO_CULLING_RADIUS(400),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, star_door_000_displaylist_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_door_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
