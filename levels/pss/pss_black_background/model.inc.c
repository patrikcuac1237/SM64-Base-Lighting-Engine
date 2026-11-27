Vtx pss_black_background_Circle_mesh_layer_1_vtx_0[12] = {
	{{ {-1443, -2819, -9167}, 0, {-16, 1008}, {151, 220, 61, 255} }},
	{{ {7217, -2819, 5833}, 0, {-16, 1008}, {151, 220, 61, 255} }},
	{{ {-1443, 14095, 833}, 0, {-16, 1008}, {151, 220, 61, 255} }},
	{{ {7217, -2819, 5833}, 0, {-16, 1008}, {30, 235, 134, 255} }},
	{{ {-4330, 0, 2500}, 0, {-16, 1008}, {30, 235, 134, 255} }},
	{{ {-1443, 14095, 833}, 0, {-16, 1008}, {30, 235, 134, 255} }},
	{{ {-4330, 0, 2500}, 0, {-16, 1008}, {120, 235, 35, 255} }},
	{{ {-1443, -2819, -9167}, 0, {-16, 1008}, {120, 235, 35, 255} }},
	{{ {-1443, 14095, 833}, 0, {-16, 1008}, {120, 235, 35, 255} }},
	{{ {-4330, 0, 2500}, 0, {-16, 1008}, {35, 120, 236, 255} }},
	{{ {7217, -2819, 5833}, 0, {-16, 1008}, {35, 120, 236, 255} }},
	{{ {-1443, -2819, -9167}, 0, {-16, 1008}, {35, 120, 236, 255} }},
};

Gfx pss_black_background_Circle_mesh_layer_1_tri_0[] = {
	gsSPVertex(pss_black_background_Circle_mesh_layer_1_vtx_0 + 0, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSPEndDisplayList(),
};


Gfx mat_pss_black_background__1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetDepthSource(G_ZS_PRIM),
	gsDPSetPrimDepth(-1, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_pss_black_background__1[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPSetDepthSource(G_ZS_PIXEL),
	gsDPSetPrimDepth(0, 0),
	gsSPEndDisplayList(),
};

Gfx pss_black_background_Circle_mesh_layer_1_with_revert[] = {
	gsSPDisplayList(mat_pss_black_background__1),
	gsSPDisplayList(pss_black_background_Circle_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_pss_black_background__1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

