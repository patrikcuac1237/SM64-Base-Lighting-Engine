void scroll_LLLArea2_lvl_geo_mesh_layer_1_vtx_9() {
	int i = 0;
	int count = 30;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(LLLArea2_lvl_geo_mesh_layer_1_vtx_9);

	deltaX = (int)(4.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_lll_level_geo_LLLArea2() {
	scroll_LLLArea2_lvl_geo_mesh_layer_1_vtx_9();
};
