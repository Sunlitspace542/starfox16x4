#define OBJECT_FIELDS_INDEX_DIRECTLY

#include "sm64.h"

#include "object_constants.h"
#include "game/object_list_processor.h"
#include "game/interaction.h"
#include "game/behavior_actions.h"
#include "game/pstrats.h"
#include "game/mario_misc.h"
#include "game/object_helpers.h"
#include "game/debug.h"
#include "menu/file_select.h"
#include "engine/surface_load.h"

#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "levels/bbh/header.h"
#include "levels/castle_inside/header.h"
#include "levels/hmc/header.h"
#include "levels/ssl/header.h"
#include "levels/bob/header.h"
#include "levels/sl/header.h"
#include "levels/wdw/header.h"
#include "levels/jrb/header.h"
#include "levels/thi/header.h"
#include "levels/ttc/header.h"
#include "levels/rr/header.h"
#include "levels/castle_grounds/header.h"
#include "levels/bitdw/header.h"
#include "levels/lll/header.h"
#include "levels/sa/header.h"
#include "levels/bitfs/header.h"
#include "levels/ddd/header.h"
#include "levels/wf/header.h"
#include "levels/bowser_2/header.h"
#include "levels/ttm/header.h"

#include "make_const_nonconst.h"
#include "behavior_data.h"

#define BC_B(a) _SHIFTL(a, 24, 8)
#define BC_BB(a, b) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 16, 8))
#define BC_BBBB(a, b, c, d) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 16, 8) | _SHIFTL(c, 8, 8) | _SHIFTL(d, 0, 8))
#define BC_BBH(a, b, c) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 16, 8) | _SHIFTL(c, 0, 16))
#define BC_B0H(a, b) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 0, 16))
#define BC_H(a) _SHIFTL(a, 16, 16)
#define BC_HH(a, b) (_SHIFTL(a, 16, 16) | _SHIFTL(b, 0, 16))
#define BC_W(a) ((uintptr_t)(u32)(a))
#define BC_PTR(a) ((uintptr_t)(a))

enum BehaviorCommands {
	/*0x00*/ BHV_CMD_BEGIN,
	/*0x01*/ BHV_CMD_DELAY,
	/*0x02*/ BHV_CMD_CALL,
	/*0x03*/ BHV_CMD_RETURN,
	/*0x04*/ BHV_CMD_GOTO,
	/*0x05*/ BHV_CMD_BEGIN_REPEAT,
	/*0x06*/ BHV_CMD_END_REPEAT,
	/*0x07*/ BHV_CMD_END_REPEAT_CONTINUE,
	/*0x08*/ BHV_CMD_BEGIN_LOOP,
	/*0x09*/ BHV_CMD_END_LOOP,
	/*0x0A*/ BHV_CMD_BREAK,
	/*0x0B*/ BHV_CMD_BREAK_UNUSED,
	/*0x0C*/ BHV_CMD_CALL_NATIVE,
	/*0x0D*/ BHV_CMD_ADD_FLOAT,
	/*0x0E*/ BHV_CMD_SET_FLOAT,
	/*0x0F*/ BHV_CMD_ADD_INT,
	/*0x10*/ BHV_CMD_SET_INT,
	/*0x11*/ BHV_CMD_OR_INT,
	/*0x12*/ BHV_CMD_BIT_CLEAR,
	/*0x13*/ BHV_CMD_SET_INT_RAND_RSHIFT,
	/*0x14*/ BHV_CMD_SET_RANDOM_FLOAT,
	/*0x15*/ BHV_CMD_SET_RANDOM_INT,
	/*0x16*/ BHV_CMD_ADD_RANDOM_FLOAT,
	/*0x17*/ BHV_CMD_ADD_INT_RAND_RSHIFT,
	/*0x18*/ BHV_CMD_NOP_1,
	/*0x19*/ BHV_CMD_NOP_2,
	/*0x1A*/ BHV_CMD_NOP_3,
	/*0x1B*/ BHV_CMD_SET_MODEL,
	/*0x1C*/ BHV_CMD_SPAWN_CHILD,
	/*0x1D*/ BHV_CMD_DEACTIVATE,
	/*0x1E*/ BHV_CMD_DROP_TO_FLOOR,
	/*0x1F*/ BHV_CMD_SUM_FLOAT,
	/*0x20*/ BHV_CMD_SUM_INT,
	/*0x21*/ BHV_CMD_BILLBOARD,
	/*0x22*/ BHV_CMD_HIDE,
	/*0x23*/ BHV_CMD_SET_HITBOX,
	/*0x24*/ BHV_CMD_NOP_4,
	/*0x25*/ BHV_CMD_DELAY_VAR,
	/*0x26*/ BHV_CMD_BEGIN_REPEAT_UNUSED,
	/*0x27*/ BHV_CMD_LOAD_ANIMATIONS,
	/*0x28*/ BHV_CMD_ANIMATE,
	/*0x29*/ BHV_CMD_SPAWN_CHILD_WITH_PARam,
	/*0x2A*/ BHV_CMD_LOAD_COLLISION_DATA,
	/*0x2B*/ BHV_CMD_SET_HITBOX_WITH_OFFSet,
	/*0x2C*/ BHV_CMD_SPAWN_OBJ,
	/*0x2D*/ BHV_CMD_SET_HOME,
	/*0x2E*/ BHV_CMD_SET_HURTBOX,
	/*0x2F*/ BHV_CMD_SET_INTERACT_TYPE,
	/*0x30*/ BHV_CMD_SET_OBJ_PHYSICS,
	/*0x31*/ BHV_CMD_SET_INTERACT_SUBTYPE,
	/*0x32*/ BHV_CMD_SCALE,
	/*0x33*/ BHV_CMD_PARENT_BIT_CLEAR,
	/*0x34*/ BHV_CMD_ANIMATE_TEXTURE,
	/*0x35*/ BHV_CMD_DISABLE_RENDERING,
	/*0x36*/ BHV_CMD_SET_INT_UNUSED,
	/*0x37*/ BHV_CMD_SPAWN_WATER_DROPLET,
};


/**************************\
*  PATH64 language macros  *
\**************************/

// Defines the start of the PATH as well as the object list the object belongs to.
// Has some special behavior for certain objects.
#define p_initialize(objList) \
	BC_BB(BHV_CMD_BEGIN, objList)

// Delays the PATH for a certain number of frames.
#define p_wait(num) \
	BC_B0H(BHV_CMD_DELAY, num)

// Jumps to a new behavior command and stores the return address in the object's stack.
#define p_jsr(addr) \
	BC_B(BHV_CMD_CALL), \
	BC_PTR(addr)

// Jumps back to the behavior command stored in the object's stack.
#define p_rts() \
	BC_B(BHV_CMD_RETURN)

// Jumps to a new PATH without saving anything.
#define p_jmp(addr) \
	BC_B(BHV_CMD_GOTO), \
	BC_PTR(addr)

// Marks the start of a loop that will repeat a certain number of times.
#define p_do(count) \
	BC_B0H(BHV_CMD_BEGIN_REPEAT, count)

// Marks the end of a repeating loop.
#define p_next() \
	BC_B(BHV_CMD_END_REPEAT)

// Also marks the end of a repeating loop, but continues executing commands following the loop on the same frame.
#define p_next_imm() \
	BC_B(BHV_CMD_END_REPEAT_CONTINUE)

// Marks the beginning of an infinite loop.
#define p_while() \
	BC_B(BHV_CMD_BEGIN_LOOP)

// Marks the end of an infinite loop.
#define p_loop() \
	BC_B(BHV_CMD_END_LOOP)

// Exits the PATH.
// Often used to end PATHs that do not contain an infinite loop.
#define p_end() \
	BC_B(BHV_CMD_BREAK)

// Exits the PATH, unused.
#define p_exit() \
	BC_B(BHV_CMD_BREAK_UNUSED)

// Executes a native game function.
#define p_program(func) \
	BC_B(BHV_CMD_CALL_NATIVE), \
	BC_PTR(func)

// Adds a float to the specified field.
#define p_addf(field, value) \
	BC_BBH(BHV_CMD_ADD_FLOAT, field, value)

// Sets the specified field to a float.
#define p_setf(field, value) \
	BC_BBH(BHV_CMD_SET_FLOAT, field, value)

// Adds an integer to the specified field.
#define p_addd(field, value) \
	BC_BBH(BHV_CMD_ADD_INT, field, value)

// Sets the specified field to an integer.
#define p_setd(field, value) \
	BC_BBH(BHV_CMD_SET_INT, field, value)

// Performs a bitwise OR with the specified field and the given integer.
// Usually used to set an object's flags.
#define p_setbit(field, value) \
	BC_BBH(BHV_CMD_OR_INT, field, value)

// Performs a bit clear with the specified short. Unused in favor of the 32-bit version.
#define p_clrbit(field, value) \
	BC_BBH(BHV_CMD_BIT_CLEAR, field, value)

// TODO: this one needs a better name / labelling
// Gets a random short, right shifts it the specified amount and adds min to it, then sets the specified field to that value.
#define p_setangle_random(field, min, rshift) \
	BC_BBH(BHV_CMD_SET_INT_RAND_RSHIFT, field, min), \
	BC_H(rshift)

// Sets the specified field to a random float in the given range.
#define p_setf_random(field, min, range) \
	BC_BBH(BHV_CMD_SET_RANDOM_FLOAT, field, min), \
	BC_H(range)

// Sets the specified field to a random integer in the given range.
#define p_setd_random(field, min, range) \
	BC_BBH(BHV_CMD_SET_RANDOM_INT, field, min), \
	BC_H(range)

// Adds a random float in the given range to the specified field.
#define p_addf_random(field, min, range) \
	BC_BBH(BHV_CMD_ADD_RANDOM_FLOAT, field, min), \
	BC_H(range)

// TODO: better name (unused anyway)
// Gets a random short, right shifts it the specified amount and adds min to it, then adds the value to the specified field. Unused.
#define p_addd_random(field, min, rshift) \
	BC_BBH(BHV_CMD_ADD_INT_RAND_RSHIFT, field, min), \
	BC_H(rshift)

// No operation. Unused.
#define p_dprintf(field) \
	BC_BB(BHV_CMD_NOP_1, field)

// No operation. Unused.
#define p_dprintx(field) \
	BC_BB(BHV_CMD_NOP_2, field)

// No operation. Unused.
#define p_dprintd(field) \
	BC_BB(BHV_CMD_NOP_3, field)

// Sets the current shape of the object.
#define p_changeshape(shape) \
	BC_B0H(BHV_CMD_SET_MODEL, shape)

// Spawns a child object with the specified shape and strat.
#define p_makeshape(shape, behavior) \
	BC_B(BHV_CMD_SPAWN_CHILD), \
	BC_W(shape), \
	BC_PTR(behavior)

// Exits the PATH and despawns the object.
// Often used to end PATHs that do not contain an infinite loop.
#define p_killshape() \
	BC_B(BHV_CMD_DEACTIVATE)

// Finds the floor triangle directly under the object and moves the object down to it.
#define p_BGcheckYset() \
	BC_B(BHV_CMD_DROP_TO_FLOOR)

// Sets the destination float field to the sum of the values of the given float fields.
#define p_WADDf(fieldDst, fieldSrc1, fieldSrc2) \
	BC_BBBB(BHV_CMD_SUM_FLOAT, fieldDst, fieldSrc1, fieldSrc2)

// Sets the destination integer field to the sum of the values of the given integer fields. Unused.
#define p_WADDd(fieldDst, fieldSrc1, fieldSrc2) \
	BC_BBBB(BHV_CMD_SUM_INT, fieldDst, fieldSrc1, fieldSrc2)

// Billboards the current object, making it always face the camera.
#define p_softspritemodeON() \
	BC_B(BHV_CMD_BILLBOARD)

// Hides the current object.
#define P_shapeOFF() \
	BC_B(BHV_CMD_HIDE)

// Sets the size of the object's cylindrical hitbox.
#define p_sethitbox(radius, height) \
	BC_B(BHV_CMD_SET_HITBOX), \
	BC_HH(radius, height)

// No operation. Unused.
#define p_softspriteanime(field, value) \
	BC_BBH(BHV_CMD_NOP_4, field, value)

// Delays the PATH for the number of frames given by the value of the specified field.
#define p_wait_work(field) \
	BC_BB(BHV_CMD_DELAY_VAR, field)

// Unused. Marks the start of a loop that will repeat a certain number of times.
// Uses a u8 as the argument, instead of a s16 like the other version does.
#define p_do_work(count) \
	BC_BB(BHV_CMD_BEGIN_REPEAT_UNUSED, count)

#define p_set_pointer_long(field, value) p_set_pointer(field, value)

// Loads the animations for the object. <field> is always set to oAnimations.
#define p_set_pointer(field, anims) \
	BC_BB(BHV_CMD_LOAD_ANIMATIONS, field), \
	BC_PTR(anims)

// Begins animation and sets the object's current animation index to the specified value.
#define p_set_skelanime_number(animIndex) \
	BC_BB(BHV_CMD_ANIMATE, animIndex)

// Spawns a child object with the specified model and behavior, plus a behavior param.
#define p_makeobj(bhvParam, shape, behavior) \
	BC_B0H(BHV_CMD_SPAWN_CHILD_WITH_PARam, bhvParam), \
	BC_W(shape), \
	BC_PTR(behavior)

// Loads collision data for the object.
#define p_setshapeinfo(collisionData) \
	BC_B(BHV_CMD_LOAD_COLLISION_DATA), \
	BC_PTR(collisionData)

// Sets the size of the object's cylindrical hitbox, and applies a downwards offset.
#define p_sethitbox2(radius, height, downOffset) \
	BC_B(BHV_CMD_SET_HITBOX_WITH_OFFSet), \
	BC_HH(radius, height), \
	BC_H(downOffset)

// Spawns a new object with the specified model and behavior.
#define p_makeobj_child(shape, behavior) \
	BC_B(BHV_CMD_SPAWN_OBJ), \
	BC_W(shape), \
	BC_PTR(behavior)

// Sets the home position of the object to its current position.
#define p_save_nowpos() \
	BC_B(BHV_CMD_SET_HOME)

// Sets the size of the object's cylindrical hurtbox.
#define p_setdamagebox(radius, height) \
	BC_B(BHV_CMD_SET_HURTBOX), \
	BC_HH(radius, height)

// Sets the object's interaction type.
#define p_setobjname(type) \
	BC_B(BHV_CMD_SET_INTERACT_TYPE), \
	BC_W(type)

// Sets various parameters that the object uses for calculating physics.
#define p_setmovedata(wallHitboxRadius, gravity, bounciness, dragStrength, friction, buoyancy, unused1, unused2) \
	BC_B(BHV_CMD_SET_OBJ_PHYSICS), \
	BC_HH(wallHitboxRadius, gravity), \
	BC_HH(bounciness, dragStrength), \
	BC_HH(friction, buoyancy), \
	BC_HH(unused1, unused2)

// Sets the object's interaction subtype. Unused.
#define p_setobjinfo(subtype) \
	BC_B(BHV_CMD_SET_INTERACT_SUBTYPE), \
	BC_W(subtype)

// Sets the object's size to the specified percentage.
#define p_set_scale(unusedField, percent) \
	BC_BBH(BHV_CMD_SCALE, unusedField, percent)

// Performs a bit clear on the object's parent's field with the specified value.
// Used for clearing active particle flags fron Mario's object.
#define PARENT_p_clrbit(field, flags) \
	BC_BB(BHV_CMD_PARENT_BIT_CLEAR, field), \
	BC_W(flags)

// Animates an object using texture animation. <field> is always set to oAnimState.
#define p_inc_frame(field, rate) \
	BC_BBH(BHV_CMD_ANIMATE_TEXTURE, field, rate)

// Disables rendering for the object.
#define p_shapeDISABLE() \
	BC_B(BHV_CMD_DISABLE_RENDERING)

// Unused. Sets the specified field to an integer. Wastes 4 bytes of space for no reason at all.
#define p_setlong(field, value) \
	BC_BB(BHV_CMD_SET_INT_UNUSED, field), \
	BC_HH(0, value)

// Spawns a water droplet with the given parameters.
#define p_makeobj_initdata(dropletParams) \
	BC_B(BHV_CMD_SPAWN_WATER_DROPLET), \
	BC_PTR(dropletParams)

// WARPS
const BehaviorScript bhvExitPodiumWarp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_WARP),
	p_BGcheckYset(),
	p_setf(oDrawingDistance, 8000),
	p_setf(oCollisionDistance, 8000),
	p_setshapeinfo(ttm_seg7_collision_podium_warp),
	p_setd(oIntangibleTimer, 0),
	p_sethitbox(/*Radius*/ 50, /*Height*/ 50),
	p_while(),
		p_program(load_object_collision_model),
		p_setd(oInteractStatus, INT_STATUS_NONE),
	p_loop(),
};

const BehaviorScript bhvFadingWarp[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setd(oInteractionSubtype, INT_SUBTYPE_FADING_WARP),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_WARP),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_fading_warp_loop),
	p_loop(),
};

const BehaviorScript bhvWarp[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_WARP),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_warp_loop),
	p_loop(),
};

const BehaviorScript bhvDoorWarp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oInteractType, INTERACT_WARP_DOOR),
};

const BehaviorScript bhvDddWarp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oCollisionDistance, 30000),
	p_while(),
		p_program(bhv_ddd_warp_loop),
		p_program(load_object_collision_model),
	p_loop(),
};
// WARPS

// NEW PATHS

const BehaviorScript P_Elaser[] = {
	p_initialize(OBJ_LIST_LEVEL),
    p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_while(),
		p_program(elaser_Istrat),
	p_loop(),
};

const BehaviorScript P_nuke[] = {
	p_initialize(OBJ_LIST_LEVEL),
    p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_softspritemodeON(),
	p_while(),
		p_program(nuke_Istrat),
	p_loop(),
};

const BehaviorScript hard180yr_Istrat[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setobjname(INTERACT_DAMAGE),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 200),
	p_while(),
		p_program(hard180yr_main),
	p_loop(),
};

// NEW PATHS


// MARIO
UNUSED static const u64 behavior_data_unused_0 = 0;
// Mario PATH.
const BehaviorScript bhvMario[] = {
	p_initialize(OBJ_LIST_PLAYER),
	p_setd(oIntangibleTimer, 0),
	p_set_pointer_long(oFlags, (OBJ_FLAG_PLAYER | OBJ_FLAG_SILHOUETTE)),
	p_setbit(my_status, 0x0001),
	p_sethitbox(/*Radius*/ 37, /*Height*/ 160),
	p_while(),
#ifdef VANILLA_DEBUG
		p_program(try_print_debug_mario_level_info),
#endif
		p_program(bhv_mario_update),
#ifdef VANILLA_DEBUG
		p_program(try_do_mario_debug_object_spawn),
#endif
	p_loop(),
};
// MARIO

// WARPS (keep these for now)

const BehaviorScript bhvInstantActiveWarp[] = {
	p_end(),
};

const BehaviorScript bhvAirborneWarp[] = {
	p_end(),
};

const BehaviorScript bhvHardAirKnockBackWarp[] = {
	p_end(),
};

const BehaviorScript bhvSpinAirborneCircleWarp[] = {
	p_end(),
};

const BehaviorScript bhvDeathWarp[] = {
	p_end(),
};

const BehaviorScript bhvSpinAirborneWarp[] = {
	p_end(),
};

const BehaviorScript bhvFlyingWarp[] = {
	p_end(),
};

const BehaviorScript bhvPaintingStarCollectWarp[] = {
	p_end(),
};

const BehaviorScript bhvPaintingDeathWarp[] = {
	p_end(),
};

const BehaviorScript bhvAirborneDeathWarp[] = {
	p_end(),
};

const BehaviorScript bhvAirborneStarCollectWarp[] = {
	p_end(),
};

const BehaviorScript bhvLaunchStarCollectWarp[] = {
	p_end(),
};

const BehaviorScript bhvLaunchDeathWarp[] = {
	p_end(),
};

const BehaviorScript bhvSwimmingWarp[] = {
	p_end(),
};

// WARPS (keep these for now)

// MENU
const BehaviorScript bhvYellowBackgroundInMenu[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(beh_yellow_background_menu_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(beh_yellow_background_menu_loop),
	p_loop(),
};

const BehaviorScript bhvMenuButton[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_menu_button_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_menu_button_loop),
	p_loop(),
};

const BehaviorScript bhvMenuButtonManager[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM | OBJ_FLAG_UPDATE_TRANSFORM_FOR_THROW_MATRIX | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_menu_button_manager_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_menu_button_manager_loop),
	p_loop(),
};

const BehaviorScript bhvActSelectorStarType[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_act_selector_star_type_loop),
	p_loop(),
};

const BehaviorScript bhvActSelector[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_act_selector_init),
	p_while(),
		p_program(bhv_act_selector_loop),
	p_loop(),
};

// MENU

const BehaviorScript bhvSoundSpawner[] = {
    p_initialize(OBJ_LIST_UNIMPORTANT),
    p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    p_wait(3),
    p_program(bhv_sound_spawner_init),
    p_wait(30),
    p_killshape(),
};


