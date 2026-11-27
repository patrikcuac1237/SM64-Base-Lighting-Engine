void scroll_gfx_mat_sslArea1__13_layer1() {
	Gfx *mat = segmented_to_virtual(mat_sslArea1__13_layer1);

	shift_s(mat, 15, PACK_TILESIZE(0, 3));

};

void scroll_gfx_mat_sslArea1__14() {
	Gfx *mat = segmented_to_virtual(mat_sslArea1__14);

	shift_s(mat, 12, PACK_TILESIZE(0, 2));

};

void scroll_gfx_mat_sslArea1__15() {
	Gfx *mat = segmented_to_virtual(mat_sslArea1__15);

	shift_s(mat, 9, PACK_TILESIZE(0, 1));

};

void scroll_ssl_level_geo_sslArea1() {
	scroll_gfx_mat_sslArea1__13_layer1();
	scroll_gfx_mat_sslArea1__14();
	scroll_gfx_mat_sslArea1__15();
};
