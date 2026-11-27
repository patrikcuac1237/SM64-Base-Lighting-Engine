void scroll_sts_mat_RTX1_water_mat() {
	Gfx *mat = segmented_to_virtual(mat_RTX1_water_mat);
	shift_s(mat, 11, PACK_TILESIZE(0, 1));
	shift_t(mat, 11, PACK_TILESIZE(0, 1));
};

void scroll_bob_level_geo_RTX1() {
	scroll_sts_mat_RTX1_water_mat();
}
