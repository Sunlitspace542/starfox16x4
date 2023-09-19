#include "src/game/envfx_snow.h"

const GeoLayout nuke_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, nuke_Bone_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, nuke_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
