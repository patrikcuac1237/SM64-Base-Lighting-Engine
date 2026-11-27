Vtx light_skybox_Cube_mesh_layer_0_vtx_0[4] = {
	{{ {16060, -5566, 28508}, 0, {368, 240}, {255, 255, 255, 255} }},
	{{ {-22296, -9200, 28508}, 0, {368, -16}, {255, 255, 255, 255} }},
	{{ {16060, 23505, 28508}, 0, {624, -16}, {255, 255, 255, 255} }},
	{{ {-22296, 23505, 28508}, 0, {-16, 1008}, {255, 255, 255, 255} }},
};

Gfx light_skybox_Cube_mesh_layer_0_tri_0[] = {
	gsSPVertex(light_skybox_Cube_mesh_layer_0_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 1, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_light_skybox_f3dlite_material_layer0[] = {
	gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING | G_SHADE),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsDPSetAlphaCompare(G_AC_THRESHOLD),
	gsDPSetDepthSource(G_ZS_PRIM),
	gsDPSetPrimDepth(-1, 0),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_light_skybox_f3dlite_material_layer0[] = {
	gsSPSetGeometryMode(G_CULL_BACK | G_LIGHTING | G_SHADE),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsDPSetDepthSource(G_ZS_PIXEL),
	gsDPSetPrimDepth(0, 0),
	gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx light_skybox_Cube_mesh_layer_0_with_revert[] = {
	gsSPDisplayList(mat_light_skybox_f3dlite_material_layer0),
	gsSPDisplayList(light_skybox_Cube_mesh_layer_0_tri_0),
	gsSPDisplayList(mat_revert_light_skybox_f3dlite_material_layer0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

