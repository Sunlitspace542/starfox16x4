Lights1 dummy_dl_f3dlite_material_lights = gdSPDefLights1(
	0x6, 0x29, 0x17,
	0x18, 0x5A, 0x39, 0x28, 0x28, 0x28);

Vtx dummy_dl_Cube_mesh_layer_1_vtx_0[4] = {
	{{ {4699, 100, -31291}, 0, {624, 496}, {0, 127, 0, 255} }},
	{{ {-4699, 100, -31291}, 0, {880, 496}, {0, 127, 0, 255} }},
	{{ {-4699, 100, 31291}, 0, {880, 240}, {0, 127, 0, 255} }},
	{{ {4699, 100, 31291}, 0, {624, 240}, {0, 127, 0, 255} }},
};

Gfx dummy_dl_Cube_mesh_layer_1_tri_0[] = {
	gsSPVertex(dummy_dl_Cube_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_dummy_dl_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(dummy_dl_f3dlite_material_lights),
	gsSPEndDisplayList(),
};

Gfx dummy_dl_Cube_mesh_layer_1[] = {
	gsSPDisplayList(mat_dummy_dl_f3dlite_material),
	gsSPDisplayList(dummy_dl_Cube_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx dummy_dl_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

