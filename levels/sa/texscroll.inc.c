void scroll_sa_dl_Water_Box_Mesh_002_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 14;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 0.5;
	float frequencyX = 0.0;
	float offsetX = 0.5;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(sa_dl_Water_Box_Mesh_002_mesh_layer_5_vtx_0);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);
	deltaY = (int)(0.0 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	timeX += 1;	currentY += deltaY;
}

void scroll_sts_mat_sa_dl_sm64_water_mat() {
	static int intervalTex0 = 2;
	static int curInterval0 = 2;
	Gfx *mat = segmented_to_virtual(mat_sa_dl_sm64_water_mat);

	if (--curInterval0 <= 0) {
		shift_s(mat, 18, PACK_TILESIZE(0, 1));
		shift_t(mat, 18, PACK_TILESIZE(0, 1));
		curInterval0 = intervalTex0;
	}
};

void scroll_sa() {
	scroll_sa_dl_Water_Box_Mesh_002_mesh_layer_5_vtx_0();
	scroll_sts_mat_sa_dl_sm64_water_mat();
}
