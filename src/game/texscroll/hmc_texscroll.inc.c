#include "levels/hmc/header.h"
#include "levels/hmc/hmc_water/texscroll.inc.c"
#include "levels/hmc/hmc_toxic_mat/texscroll.inc.c"
#include "levels/hmc/hmc_room2/texscroll.inc.c"
void scroll_textures_hmc() {
	scroll_hmc_level_geo_hmc_water();
	scroll_hmc_level_geo_hmc_toxic_mat();
	scroll_hmc_level_geo_hmc_room2();
}
