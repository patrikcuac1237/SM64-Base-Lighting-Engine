#include "levels/castle_grounds/header.h"
#include "levels/castle_grounds/texscroll.inc.c"
#include "levels/castle_grounds/test/texscroll.inc.c"
#include "levels/castle_grounds/outsides_water/texscroll.inc.c"
#include "levels/castle_grounds/leve_geometry_shaded/texscroll.inc.c"
void scroll_textures_castle_grounds() {
					scroll_castle_grounds();
	scroll_castle_grounds_level_geo_test();
	scroll_castle_grounds_level_geo_outsides_water();
	scroll_castle_grounds_level_geo_leve_geometry_shaded();
}
