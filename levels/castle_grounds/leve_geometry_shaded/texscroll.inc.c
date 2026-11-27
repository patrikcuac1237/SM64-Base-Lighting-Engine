void scroll_leve_geometry_shaded_skinned_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 36;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(leve_geometry_shaded_skinned_mesh_layer_5_vtx_1);

	deltaX = (int)(4.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_leve_geometry_shaded_skinned_mesh_layer_5_vtx_2() {
	int i = 0;
	int count = 206;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(leve_geometry_shaded_skinned_mesh_layer_5_vtx_2);

	deltaX = (int)(2.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_castle_grounds_level_geo_leve_geometry_shaded() {
	scroll_leve_geometry_shaded_skinned_mesh_layer_5_vtx_1();
	scroll_leve_geometry_shaded_skinned_mesh_layer_5_vtx_2();
};
