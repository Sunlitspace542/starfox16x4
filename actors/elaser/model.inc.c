Lights1 elaser_f3dlite_material_lights = gdSPDefLights1(
	0xF, 0x3C, 0x7F,
	0x29, 0x7F, 0xFF, 0x28, 0x28, 0x28);

Vtx elaser_Bone_mesh_layer_1_vtx_0[24] = {
	{{ {35, 45, 25}, 0, {624, 496}, {58, 110, 229, 255} }},
	{{ {-2, 39, -75}, 0, {-16, 1008}, {58, 110, 229, 255} }},
	{{ {0, 63, 25}, 0, {624, 240}, {58, 110, 229, 255} }},
	{{ {2, 21, 25}, 0, {368, 496}, {73, 154, 236, 255} }},
	{{ {-2, 39, -75}, 0, {-16, 1008}, {73, 154, 236, 255} }},
	{{ {35, 45, 25}, 0, {624, 496}, {73, 154, 236, 255} }},
	{{ {-2, 39, 82}, 0, {-16, 1008}, {55, 105, 46, 255} }},
	{{ {35, 45, 25}, 0, {624, 496}, {55, 105, 46, 255} }},
	{{ {0, 63, 25}, 0, {624, 240}, {55, 105, 46, 255} }},
	{{ {2, 21, 25}, 0, {368, 496}, {71, 157, 36, 255} }},
	{{ {35, 45, 25}, 0, {624, 496}, {71, 157, 36, 255} }},
	{{ {-2, 39, 82}, 0, {-16, 1008}, {71, 157, 36, 255} }},
	{{ {-2, 39, -75}, 0, {-16, 1008}, {194, 146, 239, 255} }},
	{{ {2, 21, 25}, 0, {368, 496}, {194, 146, 239, 255} }},
	{{ {-35, 42, 25}, 0, {368, 240}, {194, 146, 239, 255} }},
	{{ {2, 21, 25}, 0, {368, 496}, {195, 148, 29, 255} }},
	{{ {-2, 39, 82}, 0, {-16, 1008}, {195, 148, 29, 255} }},
	{{ {-35, 42, 25}, 0, {368, 240}, {195, 148, 29, 255} }},
	{{ {0, 63, 25}, 0, {624, 240}, {192, 107, 232, 255} }},
	{{ {-2, 39, -75}, 0, {-16, 1008}, {192, 107, 232, 255} }},
	{{ {-35, 42, 25}, 0, {368, 240}, {192, 107, 232, 255} }},
	{{ {0, 63, 25}, 0, {624, 240}, {194, 104, 40, 255} }},
	{{ {-35, 42, 25}, 0, {368, 240}, {194, 104, 40, 255} }},
	{{ {-2, 39, 82}, 0, {-16, 1008}, {194, 104, 40, 255} }},
};

Gfx elaser_Bone_mesh_layer_1_tri_0[] = {
	gsSPVertex(elaser_Bone_mesh_layer_1_vtx_0 + 0, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSPVertex(elaser_Bone_mesh_layer_1_vtx_0 + 15, 9, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSPEndDisplayList(),
};


Gfx mat_elaser_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(elaser_f3dlite_material_lights),
	gsSPEndDisplayList(),
};

Gfx elaser_Bone_mesh_layer_1[] = {
	gsSPDisplayList(mat_elaser_f3dlite_material),
	gsSPDisplayList(elaser_Bone_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx elaser_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

