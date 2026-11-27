void scroll_cotmc_water_seg2_dl_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 20;
	int height = 128 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(cotmc_water_seg2_dl_mesh_layer_5_vtx_0);

	deltaY = (int)(6.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_cotmc_level_geo_cotmc_water() {
	scroll_cotmc_water_seg2_dl_mesh_layer_5_vtx_0();
}
