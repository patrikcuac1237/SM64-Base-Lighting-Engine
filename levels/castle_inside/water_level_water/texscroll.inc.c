void scroll_sts_mat_water_level_water_water_mat() {
	Gfx *mat = segmented_to_virtual(mat_water_level_water_water_mat);
	shift_s(mat, 11, PACK_TILESIZE(0, 1));
	shift_t(mat, 11, PACK_TILESIZE(0, 1));
};

void scroll_castle_inside_level_geo_water_level_water() {
	scroll_sts_mat_water_level_water_water_mat();
}
