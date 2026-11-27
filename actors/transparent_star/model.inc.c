Vtx transparent_star_000_displaylist_mesh_layer_7_vtx_0[12] = {
	{{ {0, 8, -89}, 0, {-200, -371}, {0, 3, 129, 188} }},
	{{ {190, -201, 0}, 0, {-200, -371}, {86, 162, 0, 0} }},
	{{ {0, -129, 0}, 0, {-200, -371}, {0, 129, 0, 0} }},
	{{ {146, -42, 0}, 0, {-200, -371}, {125, 233, 0, 0} }},
	{{ {257, 84, 0}, 0, {-200, -371}, {119, 44, 0, 0} }},
	{{ {96, 99, 0}, 0, {-200, -371}, {55, 114, 0, 0} }},
	{{ {0, 246, 0}, 0, {-200, -371}, {0, 127, 0, 0} }},
	{{ {-95, 99, 0}, 0, {-200, -371}, {200, 114, 0, 0} }},
	{{ {-256, 84, 0}, 0, {-200, -371}, {137, 44, 0, 0} }},
	{{ {-145, -42, 0}, 0, {-200, -371}, {131, 233, 0, 0} }},
	{{ {-189, -201, 0}, 0, {-200, -371}, {171, 162, 0, 0} }},
	{{ {0, 8, 90}, 0, {-200, -371}, {0, 3, 127, 188} }},
};

Gfx transparent_star_000_displaylist_mesh_layer_7_tri_0[] = {
	gsSPVertex(transparent_star_000_displaylist_mesh_layer_7_vtx_0 + 0, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(5, 4, 0, 0),
	gsSP1Triangle(5, 0, 6, 0),
	gsSP1Triangle(0, 7, 6, 0),
	gsSP1Triangle(0, 8, 7, 0),
	gsSP1Triangle(0, 9, 8, 0),
	gsSP1Triangle(0, 10, 9, 0),
	gsSP1Triangle(0, 2, 10, 0),
	gsSP1Triangle(10, 2, 11, 0),
	gsSP1Triangle(2, 1, 11, 0),
	gsSP1Triangle(1, 3, 11, 0),
	gsSP1Triangle(11, 3, 4, 0),
	gsSP1Triangle(11, 4, 5, 0),
	gsSP1Triangle(6, 11, 5, 0),
	gsSP1Triangle(6, 7, 11, 0),
	gsSP1Triangle(7, 8, 11, 0),
	gsSP1Triangle(8, 9, 11, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSPEndDisplayList(),
};


Gfx mat_transparent_star_f3dlite_material[] = {
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, SHADE_ALPHA, 0, ENVIRONMENT, 0, ENVIRONMENT, 0, PRIMITIVE, 0, SHADE_ALPHA, 0, ENVIRONMENT, 0, ENVIRONMENT, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsSPTexture(4032, 1984, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 0, 27, 255, 191),
	gsDPSetEnvColor(2, 0, 183, 191),
	gsSPEndDisplayList(),
};

Gfx mat_revert_transparent_star_f3dlite_material[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx transparent_star_000_displaylist_mesh_layer_7_with_revert[] = {
	gsSPDisplayList(mat_transparent_star_f3dlite_material),
	gsSPDisplayList(transparent_star_000_displaylist_mesh_layer_7_tri_0),
	gsSPDisplayList(mat_revert_transparent_star_f3dlite_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

