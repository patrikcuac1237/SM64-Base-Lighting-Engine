Vtx cartoon_star_000_displaylist_mesh_layer_1_vtx_0[11] = {
	{{ {0, -8, 0}, 0, {-260, -260}, {255, 255, 255, 255} }},
	{{ {-52, 28, 0}, 0, {-260, -260}, {255, 255, 255, 255} }},
	{{ {-84, -52, 0}, 0, {-260, -260}, {255, 89, 0, 0} }},
	{{ {52, 28, 0}, 0, {-260, -260}, {255, 255, 255, 255} }},
	{{ {84, -52, 0}, 0, {-260, -260}, {255, 89, 0, 0} }},
	{{ {32, 80, 0}, 0, {-260, -260}, {255, 255, 255, 255} }},
	{{ {116, 80, 0}, 0, {-260, -260}, {255, 89, 0, 0} }},
	{{ {0, -8, 0}, 0, {-260, -260}, {255, 255, 255, 255} }},
	{{ {-32, 80, 0}, 0, {-260, -260}, {255, 255, 255, 255} }},
	{{ {0, 160, 0}, 0, {-260, -260}, {255, 89, 0, 0} }},
	{{ {-116, 80, 0}, 0, {-260, -260}, {255, 89, 0, 0} }},
};

Gfx cartoon_star_000_displaylist_mesh_layer_1_tri_0[] = {
	gsSPVertex(cartoon_star_000_displaylist_mesh_layer_1_vtx_0 + 0, 11, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(5, 3, 6, 0),
	gsSP1Triangle(7, 3, 5, 0),
	gsSP1Triangle(7, 5, 8, 0),
	gsSP1Triangle(8, 5, 9, 0),
	gsSP1Triangle(7, 8, 1, 0),
	gsSP1Triangle(1, 8, 10, 0),
	gsSPEndDisplayList(),
};


Gfx mat_cartoon_star_bilboard[] = {
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPPipeSync(),
	gsDPSetCombineLERP(ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, 0, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(4032, 4032, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_cartoon_star_bilboard[] = {
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx cartoon_star_000_displaylist_mesh_layer_1_with_revert[] = {
	gsSPDisplayList(mat_cartoon_star_bilboard),
	gsSPDisplayList(cartoon_star_000_displaylist_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_cartoon_star_bilboard),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

