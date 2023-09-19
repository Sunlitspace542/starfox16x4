Lights1 nuke_f3dlite_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFF, 0xFF, 0xFF, 0x28, 0x28, 0x28);

Gfx nuke_nuke_frame1_ci4_aligner[] = {gsSPEndDisplayList()};
u8 nuke_nuke_frame1_ci4[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 
	0x11, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x22, 
	0x22, 0x22, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 0x33, 
	0x33, 0x33, 0x32, 0x10, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x44, 
	0x44, 0x44, 0x43, 0x21, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 0x45, 0x55, 
	0x55, 0x55, 0x54, 0x32, 0x10, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x55, 0x55, 
	0x55, 0x55, 0x55, 0x43, 0x21, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x23, 0x45, 0x56, 0x67, 
	0x77, 0x77, 0x77, 0x54, 0x32, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x12, 0x34, 0x55, 0x66, 0x66, 
	0x67, 0x77, 0x75, 0x55, 0x43, 0x21, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x23, 0x45, 0x58, 0x66, 0x66, 
	0x66, 0x97, 0x55, 0x55, 0x54, 0x32, 0x10, 0x00, 
	0x00, 0x00, 0x12, 0x34, 0x55, 0x88, 0x66, 0x66, 
	0x69, 0x97, 0x75, 0x55, 0x55, 0x43, 0x21, 0x00, 
	0x00, 0x01, 0x23, 0x45, 0x58, 0x88, 0x66, 0x66, 
	0x99, 0x97, 0x75, 0x55, 0x55, 0x54, 0x32, 0x10, 
	0x00, 0x12, 0x34, 0x55, 0x88, 0x88, 0x66, 0x69, 
	0x99, 0x97, 0x77, 0x55, 0x55, 0x55, 0x43, 0x21, 
	0x01, 0x23, 0x45, 0x58, 0x88, 0x88, 0x66, 0x99, 
	0x99, 0x97, 0x77, 0x75, 0x55, 0x55, 0x43, 0x21, 
	0x01, 0x23, 0x45, 0x58, 0x88, 0x88, 0x69, 0x99, 
	0x99, 0x97, 0x77, 0x75, 0x55, 0x55, 0x43, 0x21, 
	0x01, 0x23, 0x45, 0x58, 0x88, 0x86, 0x99, 0x99, 
	0x99, 0x97, 0x77, 0x77, 0x55, 0x55, 0x43, 0x21, 
	0x01, 0x23, 0x45, 0x58, 0x88, 0x66, 0x69, 0x99, 
	0x99, 0x97, 0x77, 0x77, 0x55, 0x55, 0x43, 0x21, 
	0x01, 0x23, 0x45, 0x58, 0x86, 0x66, 0x66, 0x99, 
	0x99, 0x97, 0x77, 0x77, 0x75, 0x55, 0x43, 0x21, 
	0x01, 0x23, 0x45, 0x58, 0x66, 0x66, 0x66, 0x69, 
	0x99, 0x97, 0x77, 0x77, 0x75, 0x55, 0x43, 0x21, 
	0x01, 0x23, 0x45, 0x56, 0x66, 0x66, 0x66, 0x66, 
	0x99, 0x97, 0x77, 0x77, 0x77, 0x55, 0x43, 0x21, 
	0x00, 0x12, 0x34, 0x55, 0x66, 0x66, 0x66, 0x66, 
	0x69, 0x97, 0x77, 0x77, 0x77, 0x55, 0x43, 0x21, 
	0x00, 0x01, 0x23, 0x45, 0x56, 0x66, 0x66, 0x66, 
	0x66, 0x99, 0x99, 0x99, 0x95, 0x54, 0x32, 0x10, 
	0x00, 0x00, 0x12, 0x34, 0x55, 0x66, 0x66, 0x66, 
	0x69, 0x99, 0x99, 0x99, 0x55, 0x43, 0x21, 0x00, 
	0x00, 0x00, 0x01, 0x23, 0x45, 0x56, 0x66, 0x66, 
	0x99, 0x99, 0x99, 0x95, 0x54, 0x32, 0x10, 0x00, 
	0x00, 0x00, 0x00, 0x12, 0x34, 0x55, 0x66, 0x69, 
	0x99, 0x99, 0x99, 0x55, 0x43, 0x21, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x23, 0x45, 0x56, 0x99, 
	0x99, 0x99, 0x95, 0x54, 0x32, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x55, 0x55, 
	0x55, 0x55, 0x55, 0x43, 0x21, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 0x45, 0x55, 
	0x55, 0x55, 0x54, 0x32, 0x10, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x44, 
	0x44, 0x44, 0x43, 0x21, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 0x33, 
	0x33, 0x33, 0x32, 0x10, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x22, 
	0x22, 0x22, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 
	0x11, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	
};

Gfx nuke_nuke_frame1_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 nuke_nuke_frame1_ci4_pal_rgba16[] = {
	0x00, 0x00, 0x88, 0x83, 0xca, 0x4b, 0xe5, 0x11, 
	0xf6, 0x9b, 0xef, 0xbd, 0x74, 0xa1, 0xce, 0xf3, 
	0x43, 0x13, 0xa5, 0xa9, 
};

Vtx nuke_Bone_mesh_layer_4_vtx_0[4] = {
	{{ {-100, -100, 0}, 0, {-16, 1008}, {0, 0, 129, 255} }},
	{{ {-100, 100, 0}, 0, {-16, -16}, {0, 0, 129, 255} }},
	{{ {100, 100, 0}, 0, {1008, -16}, {0, 0, 129, 255} }},
	{{ {100, -100, 0}, 0, {1008, 1008}, {0, 0, 129, 255} }},
};

Gfx nuke_Bone_mesh_layer_4_tri_0[] = {
	gsSPVertex(nuke_Bone_mesh_layer_4_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_nuke_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, nuke_nuke_frame1_ci4_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(7, 9),
	gsDPLoadSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, nuke_nuke_frame1_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadBlock(7, 0, 0, 255, 1024),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(nuke_f3dlite_material_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_nuke_f3dlite_material[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx nuke_Bone_mesh_layer_4[] = {
	gsSPDisplayList(mat_nuke_f3dlite_material),
	gsSPDisplayList(nuke_Bone_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_nuke_f3dlite_material),
	gsSPEndDisplayList(),
};

Gfx nuke_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

