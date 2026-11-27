void scroll_gfx_mat_sslArea2__6_layer1() {
	Gfx *mat = segmented_to_virtual(mat_sslArea2__6_layer1);

	shift_s(mat, 17, PACK_TILESIZE(0, 3));

};

void scroll_gfx_mat_sslArea2__8_layer1() {
	Gfx *mat = segmented_to_virtual(mat_sslArea2__8_layer1);

	shift_t_down(mat, 16, PACK_TILESIZE(0, 8));

};

void scroll_gfx_mat_sslArea2__9_layer5() {
	Gfx *mat = segmented_to_virtual(mat_sslArea2__9_layer5);

	shift_t(mat, 16, PACK_TILESIZE(0, 12));

};

void scroll_ssl_level_geo_sslArea2() {
	scroll_gfx_mat_sslArea2__6_layer1();
	scroll_gfx_mat_sslArea2__8_layer1();
	scroll_gfx_mat_sslArea2__9_layer5();
};
