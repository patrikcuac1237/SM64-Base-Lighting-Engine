Vtx level_death_floor_008_geometry_mesh_layer_1_vtx_0[4] = {
	{{ {-7500, -6553, 7500}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {7500, -6553, 7500}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {7500, -6553, -7500}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-7500, -6553, -7500}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx level_death_floor_008_geometry_mesh_layer_1_tri_0[] = {
	gsSPVertex(level_death_floor_008_geometry_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_level_death_floor_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_level_death_floor_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx level_death_floor_008_geometry_mesh_layer_1[] = {
	gsSPDisplayList(mat_level_death_floor_f3dlite_material),
	gsSPDisplayList(level_death_floor_008_geometry_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_level_death_floor_f3dlite_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

