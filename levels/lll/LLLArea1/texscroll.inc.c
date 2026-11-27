void scroll_LLLArea1_dl_mesh_layer_1_vtx_10() {
	int i = 0;
	int count = 4;
	int height = 128 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(LLLArea1_dl_mesh_layer_1_vtx_10);

	deltaY = (int)(0.05000000074505806 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_lll_level_geo_LLLArea1() {
	scroll_LLLArea1_dl_mesh_layer_1_vtx_10();
};
