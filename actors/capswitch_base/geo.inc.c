#include "src/game/envfx_snow.h"

const GeoLayout cap_switch_base[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(600),
		GEO_OPEN_NODE(),
			GEO_SWITCH_CASE(3, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, capswitch_base_000_displaylist_001_mesh_layer_1),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, capswitch_base_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
