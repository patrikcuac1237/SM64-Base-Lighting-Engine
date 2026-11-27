Vtx dark_skybox_Cube_mesh_layer_1_vtx_0[12] = {
	{{ {-20045, -5566, 0}, 0, {368, 752}, {52, 208, 105, 255} }},
	{{ {9955, -5566, -15000}, 0, {368, 496}, {52, 208, 105, 255} }},
	{{ {94, 16238, 0}, 0, {624, 496}, {52, 208, 105, 255} }},
	{{ {9955, -5566, -15000}, 0, {368, 496}, {140, 204, 0, 255} }},
	{{ {9955, -5566, 15000}, 0, {368, 240}, {140, 204, 0, 255} }},
	{{ {94, 16238, 0}, 0, {624, 240}, {140, 204, 0, 255} }},
	{{ {9955, -5566, 15000}, 0, {368, 240}, {52, 208, 151, 255} }},
	{{ {-20045, -5566, 0}, 0, {368, -16}, {52, 208, 151, 255} }},
	{{ {94, 16238, 0}, 0, {624, -16}, {52, 208, 151, 255} }},
	{{ {9955, -5566, 15000}, 0, {353, 464}, {0, 127, 0, 255} }},
	{{ {9955, -5566, -15000}, 0, {368, 496}, {0, 127, 0, 255} }},
	{{ {-20045, -5566, 0}, 0, {112, 240}, {0, 127, 0, 255} }},
};

Gfx dark_skybox_Cube_mesh_layer_1_tri_0[] = {
	gsSPVertex(dark_skybox_Cube_mesh_layer_1_vtx_0 + 0, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSPEndDisplayList(),
};


Gfx mat_dark_skybox_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetDepthSource(G_ZS_PRIM),
	gsDPSetPrimDepth(-1, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_dark_skybox_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetDepthSource(G_ZS_PIXEL),
	gsDPSetPrimDepth(0, 0),
	gsSPEndDisplayList(),
};

Gfx dark_skybox_Cube_mesh_layer_1_with_revert[] = {
	gsSPDisplayList(mat_dark_skybox_f3dlite_material),
	gsSPDisplayList(dark_skybox_Cube_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_dark_skybox_f3dlite_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

