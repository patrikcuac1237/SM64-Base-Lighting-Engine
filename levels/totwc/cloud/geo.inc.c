#include "src/game/envfx_snow.h"

const GeoLayout totwc_geo_000160[] = {
   GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_OPEN_NODE(),
			GEO_BILLBOARD_WITH_PARAMS(LAYER_FORCE, 0, 0, 0),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cloud_000_displaylist_mesh_layer_5),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cloud_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
