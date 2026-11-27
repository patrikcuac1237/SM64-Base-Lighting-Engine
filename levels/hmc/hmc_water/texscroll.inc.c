void scroll_gfx_mat_hmc_water_water_mat() {
	Gfx *mat = segmented_to_virtual(mat_hmc_water_water_mat);

	shift_s(mat, 10, PACK_TILESIZE(0, 1));

};

void scroll_hmc_level_geo_hmc_water() {
	scroll_gfx_mat_hmc_water_water_mat();
};
