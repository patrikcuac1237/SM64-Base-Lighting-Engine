void scroll_WFMainLevel_skinned_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 59;
	int width = 32 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 0.25;
	float frequencyY = 0.10000000149011612;
	float offsetY = 0.0;
	Vtx *vertices = segmented_to_virtual(WFMainLevel_skinned_mesh_layer_5_vtx_1);

	deltaX = (int)(0.25 * 0x20) % width;
	deltaY = (int)(amplitudeY * frequencyY * coss((frequencyY * timeY + offsetY) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

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
	currentX += deltaX;	currentY += deltaY;	timeY += 1;
}

void scroll_wf_level_geo_WFMainLevel() {
	scroll_WFMainLevel_skinned_mesh_layer_5_vtx_1();
};
