void scroll_gfx_mat_hmc_room2_toxic() {
	Gfx *mat = segmented_to_virtual(mat_hmc_room2_toxic);

	shift_s(mat, 10, PACK_TILESIZE(0, 1));

};

void scroll_hmc_level_geo_hmc_room2() {
	scroll_gfx_mat_hmc_room2_toxic();
};
