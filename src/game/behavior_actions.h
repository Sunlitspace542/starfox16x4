#ifndef BEHAVIOR_ACTIONS_H
#define BEHAVIOR_ACTIONS_H

void spawn_mist_particles_variable(s32 count, s32 offsetY, f32 size);
void spawn_triangle_break_particles(s16 numTris, s16 triModel, f32 triSize, s16 triAnimState);

void spawn_mist_from_global(void);
void clear_particle_flags(u32 flags);
s32 check_if_moving_over_floor(f32 maxDist, f32 offset);
s32 arc_to_goal_pos(Vec3f a0, Vec3f a1, f32 yVel, f32 gravity);
s32 update_angle_from_move_flags(s32 *angle);

// NEW STRATS
void elaser_Istrat(void); // player's single laser.
void nuke_Istrat(void); // player's special weapon.
void hard180yr_main(void);
// NEW STRATS

// WARPS

void bhv_fading_warp_loop(void);
void bhv_warp_loop(void);
void bhv_ddd_warp_loop(void);

// WARPS

// MENUS
void bhv_menu_button_init(void);
void bhv_menu_button_loop(void);
void bhv_menu_button_manager_init(void);
void bhv_menu_button_manager_loop(void);
void bhv_act_selector_star_type_loop(void);
void bhv_act_selector_init(void);
void bhv_act_selector_loop(void);
// MENUS

void bhv_sound_spawner_init(void);

Gfx *geo_move_mario_part_from_parent(s32 callContext, UNUSED struct GraphNode *node, Mat4 mtx);

// Water splash
extern struct WaterDropletParams gShallowWaterSplashDropletParams;
extern struct WaterDropletParams gShallowWaterWaveDropletParams;

#endif // BEHAVIOR_ACTIONS_H
