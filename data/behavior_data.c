#define OBJECT_FIELDS_INDEX_DIRECTLY

#include "sm64.h"

#include "object_constants.h"
#include "game/object_list_processor.h"
#include "game/interaction.h"
#include "game/behavior_actions.h"
#include "game/mario_actions_cutscene.h"
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

const BehaviorScript bhvThiHugeIslandTop[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(thi_seg7_collision_top_trap),
	p_while(),
		p_program(bhv_thi_huge_island_top_loop),
	p_loop(),
};

const BehaviorScript bhvThiTinyIslandTop[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_thi_tiny_island_top_loop),
	p_loop(),
};

const BehaviorScript bhvCapSwitchBase[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(capswitch_collision_05003448),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvCapSwitch[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(capswitch_collision_050033D0),
	p_while(),
		p_program(bhv_cap_switch_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvKingBobomb[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, king_bobomb_seg5_anims_0500FE30),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 100),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setd(oIntangibleTimer, 0),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_makeobj_child(/*Model*/ MODEL_NONE, /*Behavior*/ bhvBobombAnchorMario),
	p_setd(oHealth, 3),
	p_setd(oDamageOrCoinValue, 1),
	p_while(),
		p_program(bhv_king_bobomb_loop),
	p_loop(),
};

const BehaviorScript bhvBobombAnchorMario[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setf(oParentRelativePosX, 100),
	p_setf(oParentRelativePosZ, 150),
	p_while(),
		p_program(bhv_bobomb_anchor_mario_loop),
	p_loop(),
};

const BehaviorScript bhvBetaChestBottom[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_program(bhv_beta_chest_bottom_init),
	p_while(),
		p_program(bhv_beta_chest_bottom_loop),
	p_loop(),
};

const BehaviorScript bhvBetaChestLid[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_beta_chest_lid_loop),
	p_loop(),
};

const BehaviorScript bhvBubbleParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_shapeDISABLE(),
	p_setd_random(oWaterObjScaleXAngle, /*Minimum*/ 2, /*Range*/ 9),
	p_wait_work(oWaterObjScaleXAngle),
	p_makeshape(/*Model*/ MODEL_BUBBLE, /*Behavior*/ bhvSmallWaterWave),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_BUBBLE),
	p_killshape(),
};

const BehaviorScript bhvBubbleMaybe[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_program(bhv_bubble_wave_init),
	p_setf_random(oWaterObjScaleXAngle, /*Minimum*/ -75, /*Range*/ 150),
	p_setf_random(oWaterObjScaleYAngle, /*Minimum*/ -75, /*Range*/ 150),
	p_setf_random(oWaterObjScaleXAngleVel, /*Minimum*/ -75, /*Range*/ 150),
	p_WADDf(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oWaterObjScaleXAngle),
	p_WADDf(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oWaterObjScaleYAngle),
	p_WADDf(/*Dest*/ oPosY, /*Value 1*/ oPosY, /*Value 2*/ oWaterObjScaleXAngleVel),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(60),
		p_addd(oAnimState, 1),
		p_program(bhv_bubble_maybe_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvSmallWaterWave[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_program(bhv_bubble_wave_init),
	p_setf_random(oWaterObjScaleXAngle, /*Minimum*/ -50, /*Range*/ 100),
	p_setf_random(oWaterObjScaleYAngle, /*Minimum*/ -50, /*Range*/ 100),
	p_WADDf(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oWaterObjScaleXAngle),
	p_WADDf(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oWaterObjScaleYAngle),
	p_setf_random(oWaterObjScaleXAngleVel, /*Minimum*/ 0, /*Range*/ 50),
	p_WADDf(/*Dest*/ oPosY, /*Value 1*/ oPosY, /*Value 2*/ oWaterObjScaleXAngleVel),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_jsr(bhvSmallWaterWave398),
	p_do(60),
		p_jsr(bhvSmallWaterWave398),
		p_program(bhv_small_water_wave_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvSmallWaterWave398[] = {
	p_addd(oAnimState, 1),
	p_addf(oPosY, 7),
	p_setf_random(oWaterObjScaleXAngle, /*Minimum*/ -2, /*Range*/ 5),
	p_setf_random(oWaterObjScaleYAngle, /*Minimum*/ -2, /*Range*/ 5),
	p_WADDf(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oWaterObjScaleXAngle),
	p_WADDf(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oWaterObjScaleYAngle),
	p_rts(),
};

const BehaviorScript bhvWaterAirBubble[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 400, /*Height*/ 150, /*Downwards offset*/ -150),
	p_setd(oIntangibleTimer, 0),
	p_setobjname(INTERACT_WATER_RING),
	p_setd(oDamageOrCoinValue, 5),
	p_program(bhv_water_air_bubble_init),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_program(bhv_water_air_bubble_loop),
	p_loop(),
};

const BehaviorScript bhvSmallParticle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_particle_init),
	p_do(70),
		p_program(bhv_particle_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvPlungeBubble[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_PLUNGE_BUBBLE),
	p_shapeDISABLE(),
	p_program(bhv_water_waves_init),
	p_killshape(),
};

const BehaviorScript bhvSmallParticleSnow[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_particle_init),
	p_do(30),
		p_program(bhv_particle_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvSmallParticleBubbles[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_particle_init),
	p_do(70),
		p_program(bhv_small_bubbles_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvFishGroup[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
		p_program(bhv_fish_group_loop),
	p_loop(),
};

const BehaviorScript bhvCannon[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_makeshape(/*Model*/ MODEL_CANNON_BARREL, /*Behavior*/ bhvCannonBarrel),
	p_setd(oInteractType, INTERACT_CANNON_BASE),
	p_addf(oPosY, -340),
	p_save_nowpos(),
	p_sethitbox(/*Radius*/ 150, /*Height*/ 150),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_cannon_base_loop),
	p_loop(),
};

const BehaviorScript bhvCannonBarrel[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_while(),
		p_program(bhv_cannon_barrel_loop),
	p_loop(),
};

const BehaviorScript bhvCannonBaseUnused[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(8),
		p_program(bhv_cannon_base_unused_loop),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvChuckya[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, chuckya_seg8_anims_0800C070),
	p_set_skelanime_number(CHUCKYA_ANIM_SPAWN),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_sethitbox(/*Radius*/ 150, /*Height*/ 100),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_makeobj_child(/*Model*/ MODEL_NONE, /*Behavior*/ bhvChuckyaAnchorMario),
	p_setd(oNumLootCoins, 5),
	p_setd(oIntangibleTimer, 0),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_chuckya_loop),
	p_loop(),
};

const BehaviorScript bhvChuckyaAnchorMario[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setf(oParentRelativePosY, -60),
	p_setf(oParentRelativePosZ, 150),
	p_while(),
		p_program(bhv_chuckya_anchor_mario_loop),
	p_loop(),
};

const BehaviorScript bhvRotatingPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_rotating_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTower[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_tower),
	p_setf(oCollisionDistance, 3000),
	p_setf(oDrawingDistance, 20000),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBulletBillCannon[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(wf_seg7_collision_bullet_bill_cannon),
	p_setf(oCollisionDistance, 300),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWfBreakableWallRight[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(wf_seg7_collision_breakable_wall),
	p_jmp(bhvWfBreakableWallLeft + 1 + 2),
};

const BehaviorScript bhvWfBreakableWallLeft[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(wf_seg7_collision_breakable_wall_2),
	// WF breakable walls - common:
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_sethitbox(/*Radius*/ 300, /*Height*/ 400),
	p_setf(oDrawingDistance, 4500),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_wf_breakable_wall_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvKickableBoard[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_kickable_board),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 1200),
	p_setdamagebox(/*Radius*/ 1, /*Height*/ 1),
	p_setf(oCollisionDistance, 1500),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_kickable_board_loop),
	p_loop(),
};

const BehaviorScript bhvTowerDoor[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_tower_door),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 100),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_tower_door_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvRotatingCounterClockwise[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_end(),
};

const BehaviorScript bhvWfRotatingWoodenPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_clocklike_rotation),
	p_while(),
		p_program(bhv_wf_rotating_wooden_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvKoopaShellUnderwater[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_set_pointer_long(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
	p_while(),
		p_program(bhv_koopa_shell_underwater_loop),
	p_loop(),
};

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

const BehaviorScript bhvWarpPipe[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_WARP),
	p_setshapeinfo(warp_pipe_seg3_collision_03009AC8),
	p_setf(oDrawingDistance, 16000),
	p_setd(oIntangibleTimer, 0),
	p_sethitbox(/*Radius*/ 70, /*Height*/ 50),
	p_while(),
		p_program(bhv_warp_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWhitePuffExplosion[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_white_puff_exploding_loop),
	p_loop(),
};

const BehaviorScript bhvSpawnedStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oBehParams2ndByte, SPAWN_STAR_POS_CUTSCENE_BP_SPAWN_AT_HOME),
	p_jmp(bhvSpawnedStarNoLevelExit + 1 + 1),
};

const BehaviorScript bhvSpawnedStarNoLevelExit[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	// Spawned star - common:
	p_save_nowpos(),
	p_program(bhv_spawned_star_init),
	p_while(),
		p_program(bhv_spawned_star_loop),
	p_loop(),
};

const BehaviorScript bhvMrIBlueCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setd(oInteractType, INTERACT_COIN),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setd(oIntangibleTimer, 0),
	p_setf(oCoinBaseYVel, 20),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_coin_init),
	p_setd(oDamageOrCoinValue, 5),
	p_sethitbox(/*Radius*/ 120, /*Height*/ 64),
	p_while(),
		p_program(bhv_coin_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvCoinInsideBoo[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 64),
	p_setd(oInteractType, INTERACT_COIN),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_softspritemodeON(),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_coin_inside_boo_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvCoinFormationSpawnedCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_coin_formation_spawned_coin_loop),
	p_loop(),
};

const BehaviorScript bhvCoinFormation[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_coin_formation_init),
	p_while(),
		p_program(bhv_coin_formation_loop),
	p_loop(),
};

const BehaviorScript bhvOneCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setd(oBehParams2ndByte, YELLOW_COIN_BP_ONE_COIN),
	p_jmp(bhvYellowCoin + 1),
};

const BehaviorScript bhvYellowCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	// Yellow coin - common:
	p_softspritemodeON(),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_init_room),
	p_program(bhv_yellow_coin_init),
	p_while(),
		p_program(bhv_yellow_coin_loop),
	p_loop(),
};

const BehaviorScript bhvTemporaryYellowCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_init_room),
	p_program(bhv_yellow_coin_init),
	p_while(),
		p_program(bhv_temp_coin_loop),
	p_loop(),
};

const BehaviorScript bhvThreeCoinsSpawn[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_do(3),
		p_makeshape(/*Model*/ MODEL_YELLOW_COIN, /*Behavior*/ bhvSingleCoinGetsSpawned),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvTenCoinsSpawn[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_do(10),
		p_makeshape(/*Model*/ MODEL_YELLOW_COIN, /*Behavior*/ bhvSingleCoinGetsSpawned),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvSingleCoinGetsSpawned[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_program(bhv_coin_init),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_coin_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvCoinSparkles[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, 25),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(8),
		p_addd(oAnimState, 1),
	p_next(),
	p_do(2),
		p_program(bhv_coin_sparkles_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvCoinSparklesSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_shapeDISABLE(),
	p_do(3),
		p_program(bhv_golden_coin_sparkles_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvWallTinyStarParticle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_do(10),
		p_program(bhv_wall_tiny_star_particle_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvVertStarParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_shapeDISABLE(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_V_STAR),
	p_program(bhv_tiny_star_particles_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvPoundTinyStarParticle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_do(10),
		p_program(bhv_pound_tiny_star_particle_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvHorStarParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_shapeDISABLE(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_H_STAR),
	p_program(bhv_pound_tiny_star_particle_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvPunchTinyTriangle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_punch_tiny_triangle_loop),
	p_loop(),
};

const BehaviorScript bhvTriangleParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_shapeDISABLE(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_TRIANGLE),
	p_program(bhv_punch_tiny_triangle_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvDoorWarp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oInteractType, INTERACT_WARP_DOOR),
	p_jmp(bhvDoor + 1 + 1),
};

const BehaviorScript bhvDoor[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oInteractType, INTERACT_DOOR),
	// Door - common:
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, door_seg3_anims_030156C0),
	p_set_skelanime_number(DOOR_ANIM_CLOSED),
	p_setshapeinfo(door_seg3_collision_door),
	p_sethitbox(/*Radius*/ 80, /*Height*/ 100),
	p_setd(oIntangibleTimer, 0),
	p_setf(oCollisionDistance, 1000),
	p_save_nowpos(),
	p_program(bhv_door_init),
	p_while(),
		p_program(bhv_door_loop),
	p_loop(),
};

const BehaviorScript bhvGrindel[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ssl_seg7_collision_grindel),
	p_BGcheckYset(),
	p_addf(oPosY, 1),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_grindel_thwomp_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvThwomp2[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(thwomp_seg5_collision_0500B92C),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_addf(oPosY, 1),
	p_save_nowpos(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 140),
	p_setf(oDrawingDistance, 4000),
	p_while(),
		p_program(bhv_grindel_thwomp_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvThwomp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(thwomp_seg5_collision_0500B7D0),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_addf(oPosY, 1),
	p_set_scale(/*Unused*/ 0, /*Field*/ 140),
	p_save_nowpos(),
	p_setf(oDrawingDistance, 4000),
	p_while(),
		p_program(bhv_grindel_thwomp_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTumblingBridgePlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oCollisionDistance, 300),
	p_while(),
		p_program(bhv_tumbling_bridge_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWfTumblingBridge[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_tumbling_bridge_loop),
	p_loop(),
};

const BehaviorScript bhvBbhTumblingBridge[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setd(oBehParams2ndByte, TUMBLING_BRIDGE_BP_BBH),
	p_while(),
		p_program(bhv_tumbling_bridge_loop),
	p_loop(),
};

const BehaviorScript bhvLllTumblingBridge[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setd(oBehParams2ndByte, TUMBLING_BRIDGE_BP_LLL),
	p_while(),
		p_program(bhv_tumbling_bridge_loop),
	p_loop(),
};

const BehaviorScript bhvFlame[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_save_nowpos(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 700),
	p_setobjname(INTERACT_FLAME),
	p_sethitbox2(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_init_room),
	p_while(),
		p_setd(oInteractStatus, INT_STATUS_NONE),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvAnotherElavator[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(hmc_seg7_collision_elevator),
	p_save_nowpos(),
	p_program(bhv_elevator_init),
	p_while(),
		p_program(bhv_elevator_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvRrElevatorPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(rr_seg7_collision_elevator_platform),
	p_save_nowpos(),
	p_program(bhv_elevator_init),
	p_while(),
		p_program(bhv_elevator_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvHmcElevatorPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(hmc_seg7_collision_elevator),
	p_save_nowpos(),
	p_program(bhv_elevator_init),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_elevator_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWaterMist[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setd(oOpacity, 254),
	p_setf(oForwardVel, 20),
	p_setf(oVelY, -8),
	p_addf(oPosY, 62),
	p_while(),
		p_program(bhv_water_mist_loop),
	p_loop(),
};

const BehaviorScript bhvBreathParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_do(8),
		p_program(bhv_water_mist_spawn_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvBreakBoxTriangle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_do(18),
		p_program(cur_obj_rotate_face_angle_using_vel),
		p_program(cur_obj_move_using_fvel_and_gravity),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvWaterMist2[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setd(oFaceAnglePitch, 0xC000),
	p_set_scale(/*Unused*/ 0, /*Field*/ 2100),
	p_while(),
		p_program(bhv_water_mist_2_loop),
	p_loop(),
};

const BehaviorScript bhvMistCircParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_pound_white_puffs_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvDirtParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_ground_sand_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvSnowParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_ground_snow_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvWind[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_wind_loop),
	p_loop(),
};

const BehaviorScript bhvEndToad[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, toad_seg6_anims_0600FB58),
	p_set_skelanime_number(TOAD_ANIM_WEST_WAVE_THEN_TURN),
	p_while(),
		p_program(bhv_end_toad_loop),
	p_loop(),
};

const BehaviorScript bhvEndPeach[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, peach_seg5_anims_0501C41C),
	p_set_skelanime_number(PEACH_ANIM_0),
	p_while(),
		p_program(bhv_end_peach_loop),
	p_loop(),
};

const BehaviorScript bhvUnusedParticleSpawn[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setd(oIntangibleTimer, 0),
	p_sethitbox(/*Radius*/ 40, /*Height*/ 40),
	p_while(),
		p_program(bhv_unused_particle_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvUkiki[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_jmp(bhvMacroUkiki + 1),
};

const BehaviorScript bhvUkikiCageChild[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oPosX, 2560),
	p_setf(oPosY, 1457),
	p_setf(oPosZ, 1898),
	p_end(),
};

const BehaviorScript bhvUkikiCageStar[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_ukiki_cage_star_loop),
	p_loop(),
};

const BehaviorScript bhvUkikiCage[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_save_nowpos(),
	p_setshapeinfo(ttm_seg7_collision_ukiki_cage),
	p_makeshape(/*Model*/ MODEL_STAR, /*Behavior*/ bhvUkikiCageStar),
	p_makeshape(/*Model*/ MODEL_NONE, /*Behavior*/ bhvUkikiCageChild),
	p_setf(oCollisionDistance, 20000),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_ukiki_cage_loop),
	p_loop(),
};

const BehaviorScript bhvBitfsSinkingPlatforms[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bitfs_seg7_collision_sinking_platform),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_bitfs_sinking_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBitfsSinkingCagePlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bitfs_seg7_collision_sinking_cage_platform),
	p_save_nowpos(),
	p_makeshape(/*Model*/ MODEL_BITFS_BLUE_POLE, /*Behavior*/ bhvDddMovingPole),
	p_while(),
		p_program(bhv_bitfs_sinking_cage_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvDddMovingPole[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_POLE),
	p_sethitbox(/*Radius*/ 80, /*Height*/ 710),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_ddd_moving_pole_loop),
	p_loop(),
};

const BehaviorScript bhvBitfsTiltingInvertedPyramid[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bitfs_seg7_collision_inverted_pyramid),
	p_save_nowpos(),
	p_program(bhv_platform_normals_init),
	p_while(),
		p_program(bhv_tilting_inverted_pyramid_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSquishablePlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_setshapeinfo(bitfs_seg7_collision_squishable_platform),
	p_setf(oCollisionDistance, 10000),
	p_program(bhv_platform_normals_init),
	p_while(),
		p_program(bhv_squishable_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvCutOutObject[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_shapeDISABLE(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_end(),
};

const BehaviorScript bhvBetaMovingFlamesSpawn[] = {
	p_while(),
		p_program(bhv_beta_moving_flames_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvBetaMovingFlames[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_beta_moving_flames_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvRrRotatingBridgePlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(rr_seg7_collision_rotating_platform_with_fire),
	p_setf(oCollisionDistance, 1500),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_rr_rotating_bridge_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvFlamethrower[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_flamethrower_loop),
	p_loop(),
};

const BehaviorScript bhvFlamethrowerFlame[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_sethitbox2(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
	p_softspritemodeON(),
	p_save_nowpos(),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_flamethrower_flame_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBouncingFireball[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_shapeDISABLE(),
	p_while(),
		p_program(bhv_bouncing_fireball_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvBouncingFireballFlame[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_setf(oGraphYOffset, 30),
	p_sethitbox2(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_bouncing_fireball_flame_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBowserShockWave[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oOpacity, 255),
	p_while(),
		p_program(bhv_bowser_shock_wave_loop),
	p_loop(),
};

const BehaviorScript bhvFireParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, 70),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_addd(oAnimState, 1),
		p_program(bhv_flame_mario_loop),
	p_loop(),
};

const BehaviorScript bhvBlackSmokeMario[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, 50),
#ifdef BURN_SMOKE_FIX
	p_setd(oOpacity, 255),
	p_while(),
		p_program(bhv_black_smoke_mario_loop),
	p_loop(),
#else
	p_do(8),
		p_program(bhv_black_smoke_mario_loop),
		p_wait(1),
		p_program(bhv_black_smoke_mario_loop),
		p_wait(1),
		p_program(bhv_black_smoke_mario_loop),
	p_next(),
	p_killshape(),
#endif
};

const BehaviorScript bhvBlackSmokeBowser[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, 0),
	p_do(8),
		p_program(bhv_black_smoke_bowser_loop),
		p_inc_frame(oAnimState, 4),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvBlackSmokeUpward[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_do(4),
		p_program(bhv_black_smoke_upward_loop),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvBetaFishSplashSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_shapeDISABLE(),
	p_while(),
		p_program(bhv_beta_fish_splash_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvSpindrift[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, spindrift_seg5_anims_05002D68),
	p_set_skelanime_number(SPINDRIFT_ANIM_DEFAULT),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_setd(oInteractionSubtype, INT_SUBTYPE_TWIRL_BOUNCE),
	p_while(),
		p_program(bhv_spindrift_loop),
	p_loop(),
};

const BehaviorScript bhvTowerPlatformGroup[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_shapeDISABLE(),
	p_addf(oPosY, 300),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_tower_platform_group_loop),
	p_loop(),
};

const BehaviorScript bhvWfSlidingTowerPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_platform),
	p_while(),
		p_program(bhv_wf_sliding_tower_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWfElevatorTowerPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_platform),
	p_while(),
		p_program(bhv_wf_elevator_tower_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWfSolidTowerPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_platform),
	p_while(),
		p_program(bhv_wf_solid_tower_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLeafParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_snow_leaf_particle_spawn_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvTreeSnow[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_tree_snow_or_leaf_loop),
	p_loop(),
};

const BehaviorScript bhvTreeLeaf[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_tree_snow_or_leaf_loop),
	p_loop(),
};

const BehaviorScript bhvAnotherTiltingPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_program(bhv_platform_normals_init),
	p_while(),
		p_program(bhv_tilting_inverted_pyramid_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSquarishPathMoving[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bitdw_seg7_collision_moving_pyramid),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_squarish_path_moving_loop),
	p_loop(),
};

const BehaviorScript bhvFloorSwitchAnimatesObject[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oBehParams2ndByte, PURPLE_SWITCH_BP_ANIMATES),
	p_jmp(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvFloorSwitchGrills[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_jmp(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvFloorSwitchHardcodedModel[] = {
	p_initialize(OBJ_LIST_SURFACE),
	// Floor switch - common:
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(purple_switch_seg8_collision_0800C7A8),
	p_while(),
		p_program(bhv_purple_switch_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvFloorSwitchHiddenObjects[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oBehParams2ndByte, PURPLE_SWITCH_BP_REVEAL_HIDDEN),
	p_jmp(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvHiddenObject[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(breakable_box_seg8_collision),
	p_setf(oCollisionDistance, 300),
	p_while(),
		p_program(bhv_hidden_object_loop),
	p_loop(),
};

const BehaviorScript bhvBreakableBox[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_setshapeinfo(breakable_box_seg8_collision),
	p_setf(oCollisionDistance, 1000),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_breakable_box_loop),
		p_program(load_object_collision_model),
	p_loop(),
	p_end(),
};

const BehaviorScript bhvPushableMetalBox[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(metal_box_seg8_collision_08024C28),
	p_setf(oCollisionDistance, 500),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_pushable_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvHeaveHo[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, heave_ho_seg5_anims_0501534C),
	p_set_skelanime_number(HEAVE_HO_ANIM_MOVING),
	p_setmovedata(/*Wall hitbox radius*/ 200, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
	p_makeobj_child(/*Model*/ MODEL_NONE, /*Behavior*/ bhvHeaveHoThrowMario),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_setd(oInteractionSubtype, (INT_SUBTYPE_NOT_GRABBABLE | INT_SUBTYPE_GRABS_MARIO)),
	p_sethitbox(/*Radius*/ 120, /*Height*/ 100),
	p_save_nowpos(),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_heave_ho_loop),
	p_loop(),
};

const BehaviorScript bhvHeaveHoThrowMario[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_heave_ho_throw_mario_loop),
	p_loop(),
};

const BehaviorScript bhvCcmTouchedStarSpawn[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_sethitbox(/*Radius*/ 500, /*Height*/ 500),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_ccm_touched_star_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvUnusedPoundablePlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(sl_seg7_collision_pound_explodes),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_unused_poundable_platform),
	p_loop(),
};

const BehaviorScript bhvBetaTrampolineTop[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(springboard_collision_05001A28),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_beta_trampoline_top_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBetaTrampolineSpring[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_beta_trampoline_spring_loop),
	p_loop(),
};

const BehaviorScript bhvJumpingBox[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO  | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_jumping_box_loop),
	p_loop(),
};

const BehaviorScript bhvBooCage[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oGraphYOffset, 10),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_boo_cage_loop),
	p_loop(),
};

const BehaviorScript bhvStub[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_shapeDISABLE(),
	p_end(),
};

const BehaviorScript bhvIgloo[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_IGLOO_BARRIER),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 200),
	p_setd(oIntangibleTimer, 0),
	p_save_nowpos(),
	p_while(),
		p_setd(oInteractStatus, INT_STATUS_NONE),
	p_loop(),
};

const BehaviorScript bhvBowserKey[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_bowser_key_loop),
	p_loop(),
};

const BehaviorScript bhvGrandStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_STAR_OR_KEY),
	p_setd(oInteractionSubtype, INT_SUBTYPE_GRAND_STAR),
	p_sethitbox(/*Radius*/ 160, /*Height*/ 100),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_grand_star_loop),
	p_loop(),
};

const BehaviorScript bhvBetaBooKey[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 32, /*Height*/ 64),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_beta_boo_key_loop),
	p_loop(),
};

const BehaviorScript bhvAlphaBooKey[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 32, /*Height*/ 64),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_alpha_boo_key_loop),
	p_loop(),
};

const BehaviorScript bhvBulletBill[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_sethitbox2(/*Radius*/ 50, /*Height*/ 50, /*Downwards offset*/ 50),
	p_setobjname(INTERACT_DAMAGE),
	p_setd(oDamageOrCoinValue, 3),
	p_set_scale(/*Unused*/ 0, /*Field*/ 40),
	p_setd(oIntangibleTimer, 0),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_program(bhv_bullet_bill_init),
	p_while(),
		p_program(bhv_bullet_bill_loop),
	p_loop(),
};

const BehaviorScript bhvWhitePuffSmoke[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_addf(oPosY, -100),
	p_program(bhv_white_puff_smoke_init),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(10),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvBowserTailAnchor[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_sethitbox2(/*Radius*/ 100, /*Height*/ 50, /*Downwards offset*/ -50),
	p_setd(oIntangibleTimer, 0),
	p_shapeDISABLE(),
	p_while(),
		p_program(bhv_bowser_tail_anchor_loop),
	p_loop(),
};

const BehaviorScript bhvBowser[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_sethitbox(/*Radius*/ 400, /*Height*/ 400),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_set_pointer(oAnimations, bowser_seg6_anims_06057690),
	p_makeshape(/*Model*/ MODEL_NONE, /*Behavior*/ bhvBowserBodyAnchor),
	p_makeshape(/*Model*/ MODEL_BOWSER_BOMB_CHILD_OBJ, /*Behavior*/ bhvBowserFlameSpawn),
	p_makeobj_child(/*Model*/ MODEL_NONE, /*Behavior*/ bhvBowserTailAnchor),
	// Beta leftover that spawn 50 coins when Bowser is defeated
	p_setd(oNumLootCoins, 50),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_program(bhv_bowser_init),
	p_while(),
		p_program(bhv_bowser_loop),
	p_loop(),
};

const BehaviorScript bhvBowserBodyAnchor[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 300),
	p_setobjname(INTERACT_DAMAGE),
	p_setd(oInteractionSubtype, INT_SUBTYPE_BIG_KNOCKBACK),
	p_shapeDISABLE(),
	p_setd(oDamageOrCoinValue, 2),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_bowser_body_anchor_loop),
	p_loop(),
};

const BehaviorScript bhvBowserFlameSpawn[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_changeshape(MODEL_NONE),
	p_while(),
		p_program(bhv_bowser_flame_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvTiltingBowserLavaPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_setshapeinfo(bowser_2_seg7_collision_tilting_platform),
	p_setf(oDrawingDistance, 20000),
	p_setf(oCollisionDistance, 20000),
	p_setd(oFaceAngleYaw, 0x0),
	p_save_nowpos(),
	p_while(),
		p_program(cur_obj_rotate_face_angle_using_vel),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvFallingBowserPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_setf(oDrawingDistance, 20000),
	p_setf(oCollisionDistance, 20000),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_falling_bowser_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBlueBowserFlame[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_blue_bowser_flame_init),
	p_while(),
		p_program(bhv_blue_bowser_flame_loop),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvFlameFloatingLanding[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_flame_floating_landing_init),
	p_while(),
		p_program(bhv_flame_floating_landing_loop),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvBlueFlamesGroup[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_blue_flames_group_loop),
	p_loop(),
};

const BehaviorScript bhvFlameBouncing[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_program(bhv_flame_bouncing_init),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_flame_bouncing_loop),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvFlameMovingForwardGrowing[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_program(bhv_flame_moving_forward_growing_init),
	p_while(),
		p_program(bhv_flame_moving_forward_growing_loop),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvFlameBowser[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_program(bhv_flame_bowser_init),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_flame_bowser_loop),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvFlameLargeBurningOut[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_program(bhv_flame_large_burning_out_init),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_flame_bowser_loop),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvBlueFish[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_set_pointer(oAnimations, blue_fish_seg3_anims_0301C2B0),
	p_set_skelanime_number(FISH_ANIM_DEFAULT),
	p_while(),
		p_program(bhv_blue_fish_movement_loop),
	p_loop(),
};

const BehaviorScript bhvTankFishGroup[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_tank_fish_group_loop),
	p_loop(),
};

const BehaviorScript bhvCheckerboardElevatorGroup[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_checkerboard_elevator_group_init),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvCheckerboardPlatformSub[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(checkerboard_platform_seg8_collision_platform),
	p_program(bhv_checkerboard_platform_init),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_checkerboard_platform_loop),
	p_loop(),
};

const BehaviorScript bhvBowserKeyUnlockDoor[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_set_pointer(oAnimations, bowser_key_seg3_anims_list),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_bowser_key_unlock_door_loop),
	p_loop(),
};

const BehaviorScript bhvBowserKeyCourseExit[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_set_pointer(oAnimations, bowser_key_seg3_anims_list),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_bowser_key_course_exit_loop),
	p_loop(),
};

const BehaviorScript bhvInvisibleObjectsUnderBridge[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_program(bhv_invisible_objects_under_bridge_init),
	p_end(),
};

const BehaviorScript bhvWaterLevelPillar[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(inside_castle_seg7_collision_water_level_pillar),
	p_program(bhv_water_level_pillar_init),
	p_while(),
		p_program(bhv_water_level_pillar_loop),
		p_program(load_object_collision_model),
	p_loop(),
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

const BehaviorScript bhvMoatGrills[] = {
	p_initialize(OBJ_LIST_SURFACE),
#ifdef UNLOCK_ALL
	p_killshape(),
#else
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(castle_grounds_seg7_collision_moat_grills),
	p_setf(oCollisionDistance, 30000),
	p_while(),
		p_program(bhv_moat_grills_loop),
	p_loop(),
#endif
};

const BehaviorScript bhvClockMinuteHand[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setd(oAngleVelRoll, -0x180),
	p_jmp(bhvClockHourHand + 1 + 1),
};

const BehaviorScript bhvClockHourHand[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setd(oAngleVelRoll, -0x20),
	// Clock hand - common:
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_rotating_clock_arm_loop),
	p_loop(),
};

const BehaviorScript bhvMacroUkiki[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	// Ukiki - common:
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_setd(oInteractionSubtype, INT_SUBTYPE_HOLDABLE_NPC),
	p_sethitbox(/*Radius*/ 40, /*Height*/ 40),
	p_setd(oIntangibleTimer, 0),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, ukiki_seg5_anims_05015784),
	p_set_skelanime_number(UKIKI_ANIM_RUN),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_program(bhv_ukiki_init),
	p_while(),
		p_program(bhv_ukiki_loop),
	p_loop(),
};

const BehaviorScript bhvLllRotatingHexagonalPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_setshapeinfo(lll_seg7_collision_hexagonal_platform),
	p_save_nowpos(),
	p_while(),
		p_setd(oAngleVelYaw,  0x100),
		p_addd(oMoveAngleYaw, 0x100),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllSinkingRockBlock[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_floating_block),
	p_addf(oPosY, -50),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_lll_sinking_rock_block_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllMovingOctagonalMeshPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_addf(oPosY, -50),
	p_setshapeinfo(lll_seg7_collision_octagonal_moving_platform),
	p_while(),
		p_program(bhv_lll_moving_octagonal_mesh_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSnowBall[] = {
	p_end(),
};

const BehaviorScript bhvLllRotatingBlockWithFireBars[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_rotating_fire_bars),
	p_setf(oCollisionDistance, 4000),
	p_while(),
		p_program(bhv_lll_rotating_block_fire_bars_loop),
	p_loop(),
};

const BehaviorScript bhvLllRotatingHexFlame[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setobjname(INTERACT_FLAME),
	p_sethitbox2(/*Radius*/ 50, /*Height*/ 100, /*Downwards offset*/ 50),
	p_setd(oIntangibleTimer, 0),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_lll_rotating_hex_flame_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvLllWoodPiece[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_wood_piece),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_lll_wood_piece_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllFloatingWoodBridge[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_changeshape(MODEL_NONE),
	p_while(),
		p_program(bhv_lll_floating_wood_bridge_loop),
	p_loop(),
};

const BehaviorScript bhvVolcanoFlames[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_while(),
		p_addd(oAnimState, 1),
		p_program(bhv_volcano_flames_loop),
	p_loop(),
};

const BehaviorScript bhvLllRotatingHexagonalRing[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_rotating_platform),
	p_while(),
		p_program(bhv_lll_rotating_hexagonal_ring_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllSinkingRectangularPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_slow_tilting_platform),
	p_setf(oCollisionDistance, 2000),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_lll_sinking_rectangular_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllSinkingSquarePlatforms[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_sinking_pyramids),
	p_addf(oPosY, 5),
	p_setf(oCollisionDistance, 2000),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_lll_sinking_square_platforms_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllTiltingInvertedPyramid[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_inverted_pyramid),
	p_addf(oPosY, 5),
	p_save_nowpos(),
	p_program(bhv_platform_normals_init),
	p_while(),
		p_program(bhv_tilting_inverted_pyramid_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvKoopaShell[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_set_pointer_long(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)), //! Silhouette doesn't show up in-game, due to combiner modes.
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_addd(oPosZ, 24),
		p_program(bhv_koopa_shell_loop),
	p_loop(),
};

const BehaviorScript P_Elaser[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(elaser_Istrat),
	p_loop(),
};

const BehaviorScript hard180yr_Istrat[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setobjname(INTERACT_DAMAGE),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 200),
	//p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
	//p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(hard180yr_main),
	p_loop(),
};

const BehaviorScript bhvKoopaShellFlame[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_FLAME),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_koopa_shell_flame_loop),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvToxBox[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ssl_seg7_collision_tox_box),
	p_addf(oPosY, 256),
	p_setf(oDrawingDistance, 8000),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_tox_box_loop),
	p_loop(),
};

const BehaviorScript bhvLllBowserPuzzlePiece[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_setshapeinfo(lll_seg7_collision_puzzle_piece),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 3000),
	p_while(),
		p_program(bhv_lll_bowser_puzzle_piece_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllBowserPuzzle[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_shapeDISABLE(),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_lll_bowser_puzzle_loop),
	p_loop(),
};

const BehaviorScript bhvTuxiesMother[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, penguin_seg5_anims_05008B74),
	p_set_skelanime_number(PENGUIN_ANIM_IDLE),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_setobjname(INTERACT_TEXT),
	p_sethitbox(/*Radius*/ 200, /*Height*/ 300),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_tuxies_mother_loop),
	p_loop(),
};

const BehaviorScript bhvPenguinBaby[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_end(),
};

const BehaviorScript bhvSmallPenguinReturned[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_end(),
};

const BehaviorScript bhvSmallPenguin[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, penguin_seg5_anims_05008B74),
	p_set_skelanime_number(PENGUIN_ANIM_WALK),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_setd(oInteractionSubtype, INT_SUBTYPE_HOLDABLE_NPC),
	p_setd(oIntangibleTimer, 0),
	p_sethitbox(/*Radius*/ 40, /*Height*/ 40),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_small_penguin_loop),
	p_loop(),
};

const BehaviorScript bhvManyBlueFishSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setd(oBehParams2ndByte, FISH_SPAWNER_BP_MANY_BLUE),
	p_jmp(bhvFishSpawner + 1),
};

const BehaviorScript bhvFewBlueFishSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setd(oBehParams2ndByte, FISH_SPAWNER_BP_FEW_BLUE),
	p_jmp(bhvFishSpawner + 1),
};

const BehaviorScript bhvFishSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	// Fish Spawner - common:
	p_shapeDISABLE(),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_fish_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvFish[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_fish_loop),
	p_loop(),
};

const BehaviorScript bhvWdwExpressElevator[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wdw_seg7_collision_express_elevator_platform),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_wdw_express_elevator_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWdwExpressElevatorPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wdw_seg7_collision_express_elevator_platform),
	p_save_nowpos(),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBubSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setd(oCheepCheepSpawnerSpawnAmount, 1),
	p_shapeDISABLE(),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_bub_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvBub[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, bub_seg6_anims_06012354),
	p_set_skelanime_number(BUB_ANIM_SWIM),
	p_sethitbox2(/*Radius*/ 20, /*Height*/ 10, /*Downwards offset*/ 10),
	p_setobjname(INTERACT_DAMAGE),
	p_setd(oDamageOrCoinValue, 1),
	p_save_nowpos(),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_bub_loop),
	p_loop(),
};

const BehaviorScript bhvExclamationBox[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(exclamation_box_outline_seg8_collision_08025F78),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oCollisionDistance, 300),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_exclamation_box_loop),
	p_loop(),
};

const BehaviorScript bhvRotatingExclamationMark[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_scale(/*Unused*/ 0, /*Field*/ 200),
	p_while(),
		p_program(bhv_rotating_exclamation_mark_loop),
		p_addd(oMoveAngleYaw, 0x800),
	p_loop(),
};

const BehaviorScript bhvSoundSpawner[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_wait(3),
	p_program(bhv_sound_spawner_init),
	p_wait(30),
	p_killshape(),
};

const BehaviorScript bhvRockSolid[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(jrb_seg7_collision_rock_solid),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBowserSubDoor[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ddd_seg7_collision_bowser_sub_door),
	p_setf(oDrawingDistance, 20000),
	p_setf(oCollisionDistance, 20000),
	p_while(),
		p_program(bhv_bowsers_sub_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBowsersSub[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oDrawingDistance, 20000),
	p_setf(oCollisionDistance, 20000),
	p_setshapeinfo(ddd_seg7_collision_submarine),
	p_while(),
		p_program(bhv_bowsers_sub_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSushiShark[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, sushi_seg5_anims_0500AE54),
	p_sethitbox2(/*Radius*/ 100, /*Height*/ 50, /*Downwards offset*/ 50),
	p_setobjname(INTERACT_DAMAGE),
	p_setd(oDamageOrCoinValue, 3),
	p_save_nowpos(),
	p_set_skelanime_number(SUSHI_ANIM_SWIM),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_sushi_shark_loop),
	p_loop(),
};

const BehaviorScript bhvJrbSlidingBox[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(jrb_seg7_collision_floating_box),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_jrb_sliding_box_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvShipPart3[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_ship_part_3_loop),
	p_loop(),
};

const BehaviorScript bhvInSunkenShip3[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(jrb_seg7_collision_in_sunken_ship_3),
	p_save_nowpos(),
	p_setf(oDrawingDistance, 4000),
	p_setf(oCollisionDistance, 4000),
	p_while(),
		p_program(bhv_ship_part_3_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSunkenShipPart[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_scale(/*Unused*/ 0, /*Field*/ 50),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_sunken_ship_part_loop),
	p_loop(),
};

const BehaviorScript bhvSunkenShipSetRotation[] = {
	p_setd(oFaceAnglePitch, 0xE958),
	p_setd(oFaceAngleYaw, 0xEE6C),
	p_setd(oFaceAngleRoll, 0x0C80),
	p_rts(),
};

const BehaviorScript bhvSunkenShipPart2[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_scale(/*Unused*/ 0, /*Field*/ 100),
	p_setf(oDrawingDistance, 6000),
	p_save_nowpos(),
	p_jsr(bhvSunkenShipSetRotation),
	p_end(),
};

const BehaviorScript bhvInSunkenShip[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(jrb_seg7_collision_in_sunken_ship),
	p_jmp(bhvInSunkenShip2 + 1 + 2),
};

const BehaviorScript bhvInSunkenShip2[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(jrb_seg7_collision_in_sunken_ship_2),
	// Sunken ship - common:
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oDrawingDistance, 4000),
	p_setf(oCollisionDistance, 4000),
	p_jsr(bhvSunkenShipSetRotation),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvMistParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_DUST),
	p_shapeDISABLE(),
	p_makeshape(/*Model*/ MODEL_MIST, /*Behavior*/ bhvWhitePuff1),
	p_makeshape(/*Model*/ MODEL_SMOKE, /*Behavior*/ bhvWhitePuff2),
	p_wait(1),
	p_killshape(),
};

const BehaviorScript bhvWhitePuff1[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_DUST),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_white_puff_1_loop),
	p_loop(),
};

const BehaviorScript bhvWhitePuff2[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(7),
		p_program(bhv_white_puff_2_loop),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvWhitePuffSmoke2[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(7),
		p_program(bhv_white_puff_2_loop),
		p_program(cur_obj_move_using_fvel_and_gravity),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvPurpleSwitchHiddenBoxes[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oBehParams2ndByte, PURPLE_SWITCH_BP_REVEAL_HIDDEN),
	p_jmp(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvBlueCoinSwitch[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(blue_coin_switch_seg8_collision_08000E98),
	p_while(),
		p_program(bhv_blue_coin_switch_loop),
	p_loop(),
};

const BehaviorScript bhvHiddenBlueCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setd(oInteractType, INTERACT_COIN),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 64),
	p_setd(oDamageOrCoinValue, 5),
	p_setd(oIntangibleTimer, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_program(bhv_hidden_blue_coin_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvOpenableCageDoor[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_openable_cage_door_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvOpenableGrill[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_openable_grill_loop),
	p_loop(),
};

const BehaviorScript bhvWaterLevelDiamond[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 70, /*Height*/ 30),
	p_setf(oCollisionDistance, 200),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_water_level_diamond_loop),
	p_loop(),
};

const BehaviorScript bhvInitializeChangingWaterLevel[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
		p_program(bhv_init_changing_water_level_loop),
	p_loop(),
};

const BehaviorScript bhvTweesterSandParticle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_tweester_sand_particle_loop),
	p_loop(),
};

const BehaviorScript bhvTweester[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_tweester_loop),
	p_loop(),
};

const BehaviorScript bhvMerryGoRoundBooManager[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_merry_go_round_boo_manager_loop),
	p_loop(),
};

const BehaviorScript bhvAnimatedTexture[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_animated_texture_loop),
		p_addd(oAnimState, 1),
		p_inc_frame(oAnimState, 2),
	p_loop(),
};

const BehaviorScript bhvBooInCastle[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setf(oGraphYOffset, 60),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_boo_in_castle_loop),
	p_loop(),
};

const BehaviorScript bhvBooWithCage[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setd(oDamageOrCoinValue, 3),
	p_setdamagebox(/*Radius*/ 80, /*Height*/ 120),
	p_sethitbox(/*Radius*/ 180, /*Height*/ 140),
	p_setf(oGraphYOffset, 60),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_boo_with_cage_init),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_boo_with_cage_loop),
	p_loop(),
};

const BehaviorScript bhvBalconyBigBoo[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setd(oBehParams2ndByte, BIG_BOO_BP_BALCONY),
	p_setd(oBigBooNumMinionBoosKilled, 10),
	p_jmp(bhvGhostHuntBigBoo + 1),
};

const BehaviorScript bhvMerryGoRoundBigBoo[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setd(oBehParams2ndByte, BIG_BOO_BP_MERRY_GO_ROUND),
	// Set number of minion boos killed to 10, which is greater than 5 so that the boo always loads without needing to kill any boos.
	p_setd(oBigBooNumMinionBoosKilled, 10),
	p_jmp(bhvGhostHuntBigBoo + 1),
};

const BehaviorScript bhvGhostHuntBigBoo[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	// Big boo - common:
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_init_room),
	p_program(bhv_boo_init),
	p_while(),
		p_program(bhv_big_boo_loop),
	p_loop(),
};

const BehaviorScript bhvCourtyardBooTriplet[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_shapeDISABLE(),
	p_program(bhv_courtyard_boo_triplet_init),
	p_killshape(),
};

const BehaviorScript bhvBoo[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setd(oBehParams2ndByte, BOO_BP_NORMAL),
	p_jmp(bhvGhostHuntBoo + 1),
};

const BehaviorScript bhvMerryGoRoundBoo[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setd(oBehParams2ndByte, BOO_BP_MERRY_GO_ROUND),
	p_jmp(bhvGhostHuntBoo + 1),
};

const BehaviorScript bhvGhostHuntBoo[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	// Boo - common:
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oIntangibleTimer, 0),
	p_save_nowpos(),
	p_setd(oDamageOrCoinValue, 2),
	p_sethitbox(/*Radius*/ 140, /*Height*/ 80),
	p_setdamagebox(/*Radius*/ 40, /*Height*/ 60),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_init_room),
	p_makeshape(/*Model*/ MODEL_YELLOW_COIN, /*Behavior*/ bhvCoinInsideBoo),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_boo_init),
	p_while(),
		p_program(bhv_boo_loop),
	p_loop(),
};

const BehaviorScript bhvHiddenStaircaseStep[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bbh_seg7_collision_staircase_step),
	p_setd(oRoom, 1),
	p_setf(oCollisionDistance, 1000),
	p_save_nowpos(),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBooStaircase[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(bbh_seg7_collision_staircase_step),
	p_setd(oRoom, 1),
	p_setf(oCollisionDistance, 1000),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_boo_staircase),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBbhTiltingTrapPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bbh_seg7_collision_tilt_floor_platform),
	p_save_nowpos(),
	p_setd(oRoom, 2),
	p_while(),
		p_program(bhv_bbh_tilting_trap_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvHauntedBookshelf[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bbh_seg7_collision_haunted_bookshelf),
	p_save_nowpos(),
	p_setd(oRoom, 6),
	p_while(),
		p_program(bhv_haunted_bookshelf_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvMeshElevator[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(bbh_seg7_collision_mesh_elevator),
	p_save_nowpos(),
	p_setd(oRoom, 12),
	p_setd(oBehParams2ndByte, ELEVATOR_BP_BBH_MESH),
	p_program(bhv_elevator_init),
	p_while(),
		p_program(bhv_elevator_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvMerryGoRound[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(bbh_seg7_collision_merry_go_round),
	p_setf(oCollisionDistance, 2000),
	p_setd(oRoom, 10),
	p_while(),
		p_program(bhv_merry_go_round_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvPlaysMusicTrackWhenTouched[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_play_music_track_when_touched_loop),
	p_loop(),
};

const BehaviorScript bhvBetaBowserAnchor[] = {
	p_initialize(OBJ_LIST_DESTRUCTIVE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_save_nowpos(),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 300),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_addd(oAnimState, 1),
		p_program(bhv_beta_bowser_anchor_loop),
	p_loop(),
};

const BehaviorScript bhvStaticCheckeredPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(checkerboard_platform_seg8_collision_platform),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_static_checkered_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvStaticObject[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_end(),
};

const BehaviorScript bhvCastleFloorTrap[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_shapeDISABLE(),
	p_program(bhv_castle_floor_trap_init),
	p_while(),
		p_program(bhv_castle_floor_trap_loop),
	p_loop(),
};

const BehaviorScript bhvFloorTrapInCastle[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(inside_castle_seg7_collision_floor_trap),
	p_while(),
		p_program(bhv_floor_trap_in_castle_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTree[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_softspritemodeON(),
	p_set_pointer_long(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_OPACITY_FROM_CAMERA_DIST)),
	p_setd(oInteractType, INTERACT_POLE),
	p_sethitbox(/*Radius*/ 80, /*Height*/ 500),
	p_setd(oIntangibleTimer, 0),
	p_while(),
//		p_program(bhv_pole_base_loop),
	p_loop(),
};

const BehaviorScript bhvSparkle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(9),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvSparkleSpawn[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_sparkle_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvSparkleParticleSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_SPARKLES),
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oGraphYOffset, 25),
	p_setf_random(oMarioParticleFlags, /*Minimum*/ -50, /*Range*/ 100),
	p_WADDf(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oMarioParticleFlags),
	p_setf_random(oMarioParticleFlags, /*Minimum*/ -50, /*Range*/ 100),
	p_WADDf(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oMarioParticleFlags),
	p_setf_random(oMarioParticleFlags, /*Minimum*/ -50, /*Range*/ 100),
	p_WADDf(/*Dest*/ oPosY, /*Value 1*/ oPosY, /*Value 2*/ oMarioParticleFlags),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(12),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

const BehaviorScript bhvScuttlebug[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, scuttlebug_seg6_anims_06015064),
	p_set_skelanime_number(SCUTTLEBUG_ANIM_JUMP),
	p_setmovedata(/*Wall hitbox radius*/ 80, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_scuttlebug_loop),
	p_loop(),
};

const BehaviorScript bhvScuttlebugSpawn[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_scuttlebug_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvWhompKingBoss[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oBehParams2ndByte, WHOMP_BP_KING),
	p_setd(oHealth, 3),
	p_jmp(bhvSmallWhomp + 1 + 1),
};

const BehaviorScript bhvSmallWhomp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setd(oNumLootCoins, 5),
	// Whomp - common:
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, whomp_seg6_anims_06020A04),
	p_setshapeinfo(whomp_seg6_collision_06020A0C),
	p_set_skelanime_number(WHOMP_ANIM_WALK),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_whomp_loop),
	p_loop(),
};

// The large splash Mario makes when he jumps into a pool of water.
const BehaviorScript bhvWaterSplash[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(3),
		p_addd(oAnimState, 1),
		p_program(bhv_water_splash_spawn_droplets),
		p_wait(1),
		p_program(bhv_water_splash_spawn_droplets),
	p_next(),
	p_do(5),
		p_addd(oAnimState, 1),
		p_wait(1),
	p_next(),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_WATER_SPLASH),
	p_killshape(),
};

// Droplets of water that spawn as a result of various water splashes.
const BehaviorScript bhvWaterDroplet[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_water_droplet_loop),
	p_loop(),
};

// Small splashes that are seen when a water droplet lands back into the water.
const BehaviorScript bhvWaterDropletSplash[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oFaceAnglePitch, 0),
	p_setd(oFaceAngleYaw, 0),
	p_setd(oFaceAngleRoll, 0),
	p_program(bhv_water_droplet_splash_init),
	p_addf(oPosY, 5),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(6),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

// The splash created when an air bubble hits the surface of the water.
const BehaviorScript bhvBubbleSplash[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oFaceAnglePitch, 0),
	p_setd(oFaceAngleYaw, 0),
	p_setd(oFaceAngleRoll, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_bubble_splash_init),
	p_do(6),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

// The water wave surrounding Mario when he is idle in a pool of water.
const BehaviorScript bhvIdleWaterWave[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oFaceAnglePitch, 0),
	p_setd(oFaceAngleYaw, 0),
	p_setd(oFaceAngleRoll, 0),
	p_while(),
		p_program(bhv_idle_water_wave_loop),
		p_addd(oAnimState, 1),
		p_do(6),
			p_program(bhv_idle_water_wave_loop),
		p_next(),
		p_program(bhv_idle_water_wave_loop),
	p_loop(),
};

// Water splashes similar to the splashes created by water droplets, but are created by other objects.
const BehaviorScript bhvObjectWaterSplash[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oFaceAnglePitch, 0),
	p_setd(oFaceAngleYaw, 0),
	p_setd(oFaceAngleRoll, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(6),
		p_addd(oAnimState, 1),
	p_next(),
	p_killshape(),
};

// Waves that are generated when running in shallow water.
const BehaviorScript bhvShallowWaterWave[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_shapeDISABLE(),
	p_do(5),
		p_makeobj_initdata(&gShallowWaterWaveDropletParams),
	p_next_imm(),
	p_wait(1),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_SHALLOW_WATER_WAVE),
	p_killshape(),
};

// A small water splash that occurs when jumping in and out of shallow water.
// Unlike the larger water splash it has no visible model of its own.
// It has a 1 in 256 chance of spawning the fish particle easter egg.
const BehaviorScript bhvShallowWaterSplash[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_shapeDISABLE(),
	p_do(18),
		p_makeobj_initdata(&gShallowWaterSplashDropletParams),
	p_next_imm(),
	p_program(bhv_shallow_water_splash_init),
	p_wait(1),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_SHALLOW_WATER_SPLASH),
	p_killshape(),
};

// Waves created by other objects along the water's surface, specifically the koopa shell and Sushi.
const BehaviorScript bhvObjectWaveTrail[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_jmp(bhvWaveTrail + 1 + 1 + 2), // Wave trail - common
};

// The waves created by Mario while he is swimming.
const BehaviorScript bhvWaveTrail[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	PARENT_p_clrbit(oActiveParticleFlags, ACTIVE_PARTICLE_WAVE_TRAIL),
	// Wave trail - common:
	p_setd(oFaceAnglePitch, 0),
	p_setd(oFaceAngleYaw, 0),
	p_setd(oFaceAngleRoll, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_do(8),
		p_addd(oAnimState, 1),
		p_program(bhv_wave_trail_shrink),
		p_wait(1),
		p_program(bhv_wave_trail_shrink),
	p_next(),
	p_killshape(),
};

// Tiny wind particles that provide aesthetics to the strong winds generated by the Snowman and Fwoosh.
// As they are unimportant objects, they don't have collision with Mario.
const BehaviorScript bhvTinyStrongWindParticle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_strong_wind_particle_loop),
	p_loop(),
};

// Strong wind particles generated by the Snowman and Fwoosh that blow Mario back and knock his cap off.
const BehaviorScript bhvStrongWindParticle[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_strong_wind_particle_loop),
	p_loop(),
};

// The handler for the strong wind blown by the Snowman in SL. Triggers dialog and then aims towards Mario.
const BehaviorScript bhvSLSnowmanWind[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_sl_snowman_wind_loop),
	p_loop(),
};

// The penguin that walks erratically along the ice bridge in front of the Snowman in SL.
// Blocks strong wind particles, allowing Mario to walk behind it.
const BehaviorScript bhvSLWalkingPenguin[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(penguin_seg5_collision_05008B88),
	p_set_pointer(oAnimations, penguin_seg5_anims_05008B74),
	p_set_skelanime_number(PENGUIN_ANIM_WALK),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_set_scale(/*Unused*/ 0, /*Field*/ 600),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_sl_walking_penguin_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvYellowBall[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_end(),
};

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

const BehaviorScript bhvToadMessage[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, toad_seg6_anims_0600FB58),
	p_set_skelanime_number(TOAD_ANIM_WEST_WAVING_BOTH_ARMS),
	p_setobjname(INTERACT_TEXT),
	p_sethitbox(/*Radius*/ 80, /*Height*/ 100),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_init_room),
	p_program(bhv_toad_message_init),
	p_while(),
		p_program(bhv_toad_message_loop),
	p_loop(),
};

const BehaviorScript bhvUnlockDoorStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_unlock_door_star_init),
	p_while(),
		p_program(bhv_unlock_door_star_loop),
	p_loop(),
};

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

UNUSED static const u64 behavior_data_unused_1 = 0;
const BehaviorScript bhvRandomAnimatedTexture[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oGraphYOffset, -16),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_addd(oAnimState, 1),
	p_loop(),
};

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

const BehaviorScript bhvMovingYellowCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 64),
	p_setd(oInteractType, INTERACT_COIN),
	p_setd(oIntangibleTimer, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_moving_yellow_coin_init),
	p_while(),
		p_program(bhv_moving_yellow_coin_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvMovingBlueCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setd(oIntangibleTimer, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_moving_blue_coin_init),
	p_while(),
		p_program(bhv_moving_blue_coin_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBlueCoinSliding[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setd(oIntangibleTimer, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_blue_coin_sliding_jumping_init),
	p_while(),
		p_program(bhv_blue_coin_sliding_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBlueCoinJumping[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setd(oIntangibleTimer, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_blue_coin_sliding_jumping_init),
	p_while(),
		p_program(bhv_blue_coin_jumping_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvSeaweed[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, seaweed_seg6_anims_0600A4D4),
	p_set_skelanime_number(SEAWEED_ANIM_WAVE),
	p_program(bhv_seaweed_init),
	p_while(),
	p_loop(),
};

const BehaviorScript bhvSeaweedBundle[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_program(bhv_seaweed_bundle_init),
	p_while(),
	p_loop(),
};

const BehaviorScript bhvBobomb[] = {
	p_initialize(OBJ_LIST_DESTRUCTIVE),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, bobomb_seg8_anims_0802396C),
	p_BGcheckYset(),
	p_set_skelanime_number(BOBOMB_ANIM_WALKING),
	p_setd(oIntangibleTimer, 0),
	p_save_nowpos(),
	p_program(bhv_bobomb_init),
	p_while(),
		p_program(bhv_bobomb_loop),
	p_loop(),
};

const BehaviorScript bhvBobombFuseSmoke[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_bobomb_fuse_smoke_init),
	p_wait(1),
	p_while(),
		p_program(bhv_dust_smoke_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBobombBuddy[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oBobombBuddyRole, 0),
	p_set_pointer(oAnimations, bobomb_seg8_anims_0802396C),
	p_setobjname(INTERACT_TEXT),
	p_BGcheckYset(),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 60),
	p_set_skelanime_number(BOBOMB_ANIM_WALKING),
	p_save_nowpos(),
	p_program(bhv_bobomb_buddy_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_bobomb_buddy_loop),
	p_loop(),
};

const BehaviorScript bhvBobombBuddyOpensCannon[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oBobombBuddyRole, 1),
	p_jmp(bhvBobombBuddy + 1 + 2),
};

const BehaviorScript bhvCannonClosed[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(cannon_lid_seg8_collision_08004950),
	p_save_nowpos(),
	p_program(bhv_cannon_closed_init),
	p_while(),
		p_program(bhv_cannon_closed_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWhirlpool[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_whirlpool_init),
	p_while(),
		p_program(bhv_whirlpool_loop),
	p_loop(),
};

const BehaviorScript bhvJetStream[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_jet_stream_loop),
	p_loop(),
};

const BehaviorScript bhvMessagePanel[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wooden_signpost_seg3_collision_0302DD80),
	p_setf(oCollisionDistance, 150),
	p_setobjname(INTERACT_TEXT),
	p_setd(oInteractionSubtype, INT_SUBTYPE_SIGN),
	p_BGcheckYset(),
	p_sethitbox(/*Radius*/ 150, /*Height*/ 80),
	p_setd(oWoodenPostTotalMarioAngle, 0),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(load_object_collision_model),
		p_setd(oInteractStatus, INT_STATUS_NONE),
	p_loop(),
};

const BehaviorScript bhvSignOnWall[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setobjname(INTERACT_TEXT),
	p_setd(oInteractionSubtype, INT_SUBTYPE_SIGN),
	p_sethitbox(/*Radius*/ 150, /*Height*/ 80),
	p_setd(oWoodenPostTotalMarioAngle, 0),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_setd(oInteractStatus, INT_STATUS_NONE),
	p_loop(),
};

const BehaviorScript bhvHomingAmp[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, dAmpAnimsList),
	p_set_skelanime_number(AMP_ANIM_DEFAULT),
	p_setf(oGraphYOffset, 40),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_homing_amp_init),
	p_while(),
		p_program(bhv_homing_amp_loop),
	p_loop(),
};

const BehaviorScript bhvCirclingAmp[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, dAmpAnimsList),
	p_set_skelanime_number(AMP_ANIM_DEFAULT),
	p_setf(oGraphYOffset, 40),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_circling_amp_init),
	p_while(),
		p_program(bhv_circling_amp_loop),
	p_loop(),
};

const BehaviorScript bhvButterfly[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, butterfly_seg3_anims_030056B0),
	p_BGcheckYset(),
	p_setf(oGraphYOffset, 5),
	p_program(bhv_butterfly_init),
	p_while(),
		p_program(bhv_butterfly_loop),
	p_loop(),
};

const BehaviorScript bhvHoot[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, hoot_seg5_anims_05005768),
	p_setd(oInteractType, INTERACT_HOOT),
	p_sethitbox(/*Radius*/ 75, /*Height*/ 75),
	p_program(bhv_hoot_init),
	p_while(),
		p_program(bhv_hoot_loop),
	p_loop(),
};

const BehaviorScript bhvBetaHoldableObject[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_BGcheckYset(),
	p_sethitbox(/*Radius*/ 40, /*Height*/ 50),
	p_program(bhv_beta_holdable_object_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_beta_holdable_object_loop),
	p_loop(),
};

const BehaviorScript bhvCarrySomethingHeld[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_end(),
};

const BehaviorScript bhvCarrySomethingDropped[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_end(),
};

const BehaviorScript bhvCarrySomethingThrown[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_end(),
};

const BehaviorScript bhvObjectBubble[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_object_bubble_init),
	p_setf_random(oVelY, /*Minimum*/ 3, /*Range*/ 6),
	p_setangle_random(oMoveAngleYaw, /*Minimum*/ 0, /*Right shift*/ 0),
	p_wait(1),
	p_while(),
		p_program(bhv_object_bubble_loop),
	p_loop(),
};

const BehaviorScript bhvObjectWaterWave[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oFaceAnglePitch, 0),
	p_setd(oFaceAngleYaw, 0),
	p_setd(oFaceAngleRoll, 0),
	p_program(bhv_object_water_wave_init),
	p_wait(6),
	p_while(),
		p_program(bhv_object_water_wave_loop),
		p_addd(oAnimState, 1),
	p_do(6),
		p_program(bhv_object_water_wave_loop),
	p_next(),
	p_loop(),
};

const BehaviorScript bhvExplosion[] = {
	p_initialize(OBJ_LIST_DESTRUCTIVE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setobjname(INTERACT_DAMAGE),
	p_setd(oDamageOrCoinValue, 2),
	p_setd(oIntangibleTimer, 0),
	p_sethitbox2(/*Radius*/ 150, /*Height*/ 150, /*Downwards offset*/ 150),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_explosion_init),
	p_while(),
		p_program(bhv_explosion_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBobombBullyDeathSmoke[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_bobomb_bully_death_smoke_init),
	p_wait(1),
	p_while(),
		p_program(bhv_dust_smoke_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvSmoke[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_wait(1),
	p_while(),
		p_program(bhv_dust_smoke_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBobombExplosionBubble[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_bobomb_explosion_bubble_init),
	p_addf_random(oPosX, /*Minimum*/ -50, /*Range*/ 100),
	p_addf_random(oPosY, /*Minimum*/ -50, /*Range*/ 100),
	p_addf_random(oPosZ, /*Minimum*/ -50, /*Range*/ 100),
	p_jsr(bhvBobombExplosionBubble3600),
	p_wait(1),
	p_while(),
		p_jsr(bhvBobombExplosionBubble3600),
		p_program(bhv_bobomb_explosion_bubble_loop),
	p_loop(),
};

const BehaviorScript bhvBobombExplosionBubble3600[] = {
	p_addf_random(oPosX, /*Minimum*/ -2, /*Range*/ 4),
	p_addf_random(oPosZ, /*Minimum*/ -2, /*Range*/ 4),
	p_rts(),
};

const BehaviorScript bhvRespawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_respawner_loop),
	p_loop(),
};

const BehaviorScript bhvSmallBully[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, bully_seg5_anims_0500470C),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_program(bhv_small_bully_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_bully_loop),
	p_loop(),
};

const BehaviorScript bhvBigBully[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, bully_seg5_anims_0500470C),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_program(bhv_big_bully_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_bully_loop),
	p_loop(),
};

const BehaviorScript bhvBigBullyWithMinions[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, bully_seg5_anims_0500470C),
	p_save_nowpos(),
	p_program(bhv_big_bully_init),
	p_program(bhv_big_bully_with_minions_init),
	p_while(),
		p_program(bhv_big_bully_with_minions_loop),
	p_loop(),
};

const BehaviorScript bhvSmallChillBully[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, chilly_chief_seg6_anims_06003994),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_setd(oBullySubtype, 0x0010),
	p_program(bhv_small_bully_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_bully_loop),
	p_loop(),
};

const BehaviorScript bhvBigChillBully[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, chilly_chief_seg6_anims_06003994),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_setd(oBullySubtype, 0x0010),
	p_program(bhv_big_bully_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_bully_loop),
	p_loop(),
};

const BehaviorScript bhvJetStreamRingSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	P_shapeOFF(),
	p_while(),
		p_program(bhv_jet_stream_ring_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvJetStreamWaterRing[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, water_ring_seg6_anims_06013F7C),
	p_sethitbox2(/*Radius*/ 75, /*Height*/ 20, /*Downwards offset*/ 20),
	p_setobjname(INTERACT_WATER_RING),
	p_setd(oDamageOrCoinValue, 2),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_jet_stream_water_ring_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_jet_stream_water_ring_loop),
	p_loop(),
};

const BehaviorScript bhvMantaRayWaterRing[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, water_ring_seg6_anims_06013F7C),
	p_sethitbox2(/*Radius*/ 75, /*Height*/ 20, /*Downwards offset*/ 20),
	p_setobjname(INTERACT_WATER_RING),
	p_setd(oDamageOrCoinValue, 2),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_manta_ray_water_ring_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_manta_ray_water_ring_loop),
	p_loop(),
};

const BehaviorScript bhvMantaRayRingManager[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
	p_loop(),
};

const BehaviorScript bhvBowserBomb[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oIntangibleTimer, 0),
	p_sethitbox2(/*Radius*/ 40, /*Height*/ 40, /*Downwards offset*/ 40),
	p_wait(1),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_bowser_bomb_loop),
	p_loop(),
};

const BehaviorScript bhvBowserBombExplosion[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, -288),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_program(bhv_bowser_bomb_explosion_loop),
	p_loop(),
};

const BehaviorScript bhvBowserBombSmoke[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, -288),
	p_setd(oOpacity, 255),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_program(bhv_bowser_bomb_smoke_loop),
	p_loop(),
};

const BehaviorScript bhvCelebrationStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_celebration_star_init),
	p_while(),
		p_program(bhv_celebration_star_loop),
	p_loop(),
};

const BehaviorScript bhvCelebrationStarSparkle[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oGraphYOffset, 25),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_addd(oAnimState, 1),
		p_program(bhv_celebration_star_sparkle_loop),
	p_loop(),
};

const BehaviorScript bhvStarKeyCollectionPuffSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_softspritemodeON(),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_program(bhv_star_key_collection_puff_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvLllDrawbridgeSpawner[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	P_shapeOFF(),
	p_while(),
		p_program(bhv_lll_drawbridge_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvLllDrawbridge[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_drawbridge),
	p_while(),
		p_program(bhv_lll_drawbridge_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSmallBomp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_small_bomp),
	p_program(bhv_small_bomp_init),
	p_while(),
		p_program(bhv_small_bomp_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLargeBomp[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_large_bomp),
	p_program(bhv_large_bomp_init),
	p_while(),
		p_program(bhv_large_bomp_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWfSlidingPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wf_seg7_collision_sliding_brick_platform),
	p_program(bhv_wf_sliding_platform_init),
	p_while(),
		p_program(bhv_wf_sliding_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvMoneybag[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, moneybag_seg6_anims_06005E5C),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_setd(oIntangibleTimer, -1),
	p_program(bhv_moneybag_init),
	p_while(),
		p_program(bhv_moneybag_loop),
	p_loop(),
};

const BehaviorScript bhvMoneybagHidden[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oGraphYOffset, 27),
	p_softspritemodeON(),
	p_sethitbox(/*Radius*/ 110, /*Height*/ 100),
	p_setd(oIntangibleTimer, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_while(),
		p_addd(oAnimState, 1),
		p_program(bhv_moneybag_hidden_loop),
	p_loop(),
};

const BehaviorScript bhvPitBowlingBall[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, 130),
	p_program(bhv_bob_pit_bowling_ball_init),
	p_while(),
		p_program(bhv_bob_pit_bowling_ball_loop),
	p_loop(),
};

const BehaviorScript bhvFreeBowlingBall[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, 130),
	p_program(bhv_free_bowling_ball_init),
	p_while(),
		p_program(bhv_free_bowling_ball_loop),
	p_loop(),
};

const BehaviorScript bhvBowlingBall[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setf(oGraphYOffset, 130),
	p_program(bhv_bowling_ball_init),
	p_while(),
		p_program(bhv_bowling_ball_loop),
	p_loop(),
};

const BehaviorScript bhvTtmBowlingBallSpawner[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oBBallSpawnerPeriodMinus1, 63),
	p_program(bhv_generic_bowling_ball_spawner_init),
	p_while(),
		p_program(bhv_generic_bowling_ball_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvBobBowlingBallSpawner[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oBBallSpawnerPeriodMinus1, 127),
	p_program(bhv_generic_bowling_ball_spawner_init),
	p_while(),
		p_program(bhv_generic_bowling_ball_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvThiBowlingBallSpawner[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_thi_bowling_ball_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvRrCruiserWing[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_rr_cruiser_wing_init),
	p_while(),
		p_program(bhv_rr_cruiser_wing_loop),
	p_loop(),
};

const BehaviorScript bhvSpindel[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ssl_seg7_collision_spindel),
	p_program(bhv_spindel_init),
	p_while(),
		p_program(bhv_spindel_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSslMovingPyramidWall[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ssl_seg7_collision_0702808C),
	p_program(bhv_ssl_moving_pyramid_wall_init),
	p_while(),
		p_program(bhv_ssl_moving_pyramid_wall_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvPyramidElevator[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ssl_seg7_collision_pyramid_elevator),
	p_save_nowpos(),
	p_setf(oDrawingDistance, 20000),
	p_setf(oCollisionDistance, 20000),
	p_program(bhv_pyramid_elevator_init),
	p_while(),
		p_program(bhv_pyramid_elevator_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvPyramidElevatorTrajectoryMarkerBall[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_pyramid_elevator_trajectory_marker_ball_loop),
	p_loop(),
};

const BehaviorScript bhvPyramidTop[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ssl_seg7_collision_pyramid_top),
	p_save_nowpos(),
	p_setf(oDrawingDistance, 20000),
	p_setf(oCollisionDistance, 20000),
	p_program(bhv_pyramid_top_init),
	p_while(),
		p_program(bhv_pyramid_top_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvPyramidTopFragment[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_pyramid_top_fragment_init),
	p_while(),
		p_program(bhv_pyramid_top_fragment_loop),
	p_loop(),
};

const BehaviorScript bhvPyramidPillarTouchDetector[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 50, /*Height*/ 50),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_pyramid_pillar_touch_detector_loop),
	p_loop(),
};

const BehaviorScript bhvWaterfallSoundLoop[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
		p_program(bhv_waterfall_sound_loop),
	p_loop(),
};

const BehaviorScript bhvVolcanoSoundLoop[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
		p_program(bhv_volcano_sound_loop),
	p_loop(),
};

const BehaviorScript bhvCastleFlagWaving[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, castle_grounds_seg7_anims_flags),
	p_set_skelanime_number(CASTLE_FLAG_ANIM_WAVE),
	p_program(bhv_castle_flag_init),
	p_while(),
	p_loop(),
};

const BehaviorScript bhvBirdsSoundLoop[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
		p_program(bhv_birds_sound_loop),
	p_loop(),
};

const BehaviorScript bhvAmbientSounds[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_program(bhv_ambient_sounds_init),
	p_while(),
	p_loop(),
};

const BehaviorScript bhvSandSoundLoop[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
		p_program(bhv_sand_sound_loop),
	p_loop(),
};

const BehaviorScript bhvHiddenAt120Stars[] = {
	p_initialize(OBJ_LIST_SURFACE),
#ifdef UNLOCK_ALL
	p_killshape(),
#else
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(castle_grounds_seg7_collision_cannon_grill),
	p_setf(oCollisionDistance, 4000),
	p_program(bhv_castle_cannon_grate_init),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
#endif
};

const BehaviorScript bhvSnowmansBottom[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_snowmans_bottom_init),
	p_while(),
		p_program(bhv_snowmans_bottom_loop),
	p_loop(),
};

const BehaviorScript bhvSnowmansHead[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_setf(oGraphYOffset, 110),
	p_program(bhv_snowmans_head_init),
	p_while(),
		p_program(bhv_snowmans_head_loop),
	p_loop(),
};

const BehaviorScript bhvSnowmansBodyCheckpoint[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_snowmans_body_checkpoint_loop),
	p_loop(),
};

const BehaviorScript bhvBigSnowmanWhole[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oGraphYOffset, 180),
	p_setobjname(INTERACT_TEXT),
	p_sethitbox(/*Radius*/ 210, /*Height*/ 550),
	p_while(),
		p_setd(oIntangibleTimer, 0),
	p_loop(),
};

const BehaviorScript bhvBigBoulder[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oGraphYOffset, 180),
	p_program(bhv_big_boulder_init),
	p_setf(oDrawingDistance, 20000),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_big_boulder_loop),
	p_loop(),
};

const BehaviorScript bhvBigBoulderGenerator[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_big_boulder_generator_loop),
	p_loop(),
};

const BehaviorScript bhvWingCap[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
	p_program(bhv_wing_cap_init),
	p_while(),
		p_program(bhv_wing_vanish_cap_loop),
	p_loop(),
};

const BehaviorScript bhvMetalCap[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
	p_program(bhv_metal_cap_init),
	p_while(),
		p_program(bhv_metal_cap_loop),
	p_loop(),
};

const BehaviorScript bhvNormalCap[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
	p_program(bhv_normal_cap_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_normal_cap_loop),
	p_loop(),
};

const BehaviorScript bhvVanishCap[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
	p_program(bhv_vanish_cap_init),
	p_while(),
		p_program(bhv_wing_vanish_cap_loop),
	p_loop(),
};

const BehaviorScript bhvStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_init_room),
	p_program(bhv_collect_star_init),
	p_while(),
		p_program(bhv_collect_star_loop),
	p_loop(),
};

const BehaviorScript bhvStarSpawnCoordinates[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_collect_star_init),
	p_program(bhv_star_spawn_init),
	p_while(),
		p_program(bhv_star_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvHiddenRedCoinStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_hidden_red_coin_star_init),
	p_while(),
		p_program(bhv_hidden_red_coin_star_loop),
	p_loop(),
};

const BehaviorScript bhvRedCoin[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setd(oIntangibleTimer, 0),
	p_setd(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
	p_program(bhv_init_room),
	p_program(bhv_red_coin_init),
	p_while(),
		p_program(bhv_red_coin_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvBowserCourseRedCoinStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_bowser_course_red_coin_star_loop),
	p_loop(),
};

const BehaviorScript bhvHiddenStar[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_hidden_star_init),
	p_while(),
		p_program(bhv_hidden_star_loop),
	p_loop(),
};

const BehaviorScript bhvHiddenStarTrigger[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 100),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_hidden_star_trigger_loop),
	p_loop(),
};

const BehaviorScript bhvTtmRollingLog[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(ttm_seg7_collision_pitoune_2),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 2000),
	p_program(bhv_ttm_rolling_log_init),
	p_while(),
		p_program(bhv_rolling_log_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllVolcanoFallingTrap[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_falling_wall),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_volcano_trap_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvLllRollingLog[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(lll_seg7_collision_pitoune),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 2000),
	p_program(bhv_lll_rolling_log_init),
	p_while(),
		p_program(bhv_rolling_log_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhv1upWalking[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_1up_common_init),
	p_while(),
		p_program(bhv_1up_walking_loop),
	p_loop(),
};

const BehaviorScript bhv1upRunningAway[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_1up_common_init),
	p_while(),
		p_program(bhv_1up_running_away_loop),
	p_loop(),
};

const BehaviorScript bhv1upSliding[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_1up_common_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_1up_sliding_loop),
	p_loop(),
};

const BehaviorScript bhv1Up[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_1up_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_1up_loop),
	p_loop(),
};

const BehaviorScript bhv1upJumpOnApproach[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_1up_common_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_1up_jump_on_approach_loop),
	p_loop(),
};

const BehaviorScript bhvHidden1up[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_1up_common_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_1up_hidden_loop),
	p_loop(),
};

const BehaviorScript bhvHidden1upTrigger[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 100),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_1up_hidden_trigger_loop),
	p_loop(),
};

const BehaviorScript bhvHidden1upInPole[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_sethitbox2(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
	p_setf(oGraphYOffset, 30),
	p_program(bhv_1up_common_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_1up_hidden_in_pole_loop),
	p_loop(),
};

const BehaviorScript bhvHidden1upInPoleTrigger[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_sethitbox(/*Radius*/ 100, /*Height*/ 100),
	p_setd(oIntangibleTimer, 0),
	p_while(),
		p_program(bhv_1up_hidden_in_pole_trigger_loop),
	p_loop(),
};

const BehaviorScript bhvHidden1upInPoleSpawner[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_1up_hidden_in_pole_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvControllablePlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM | OBJ_FLAG_UPDATE_TRANSFORM_FOR_THROW_MATRIX | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(hmc_seg7_collision_controllable_platform),
	p_save_nowpos(),
	p_program(bhv_controllable_platform_init),
	p_while(),
		p_program(bhv_controllable_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvControllablePlatformSub[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(hmc_seg7_collision_controllable_platform_sub),
	p_while(),
		p_program(bhv_controllable_platform_sub_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvBreakableBoxSmall[] = {
	p_initialize(OBJ_LIST_DESTRUCTIVE),
	p_setbit(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_program(bhv_breakable_box_small_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_breakable_box_small_loop),
	p_loop(),
};

const BehaviorScript bhvSlidingSnowMound[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(sl_seg7_collision_sliding_snow_mound),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_sliding_snow_mound_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvSnowMoundSpawn[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_while(),
		p_program(bhv_snow_mound_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvWdwSquareFloatingPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wdw_seg7_collision_square_floating_platform),
	p_setf(oFloatingPlatformHeightOffset, 64),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_floating_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWdwRectangularFloatingPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(wdw_seg7_collision_rect_floating_platform),
	p_setf(oFloatingPlatformHeightOffset, 64),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_floating_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvJrbFloatingPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setshapeinfo(jrb_seg7_collision_floating_platform),
	p_setf(oFloatingPlatformHeightOffset, 64),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_floating_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvArrowLift[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(wdw_seg7_collision_arrow_lift),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_arrow_lift_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvOrangeNumber[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_save_nowpos(),
	p_program(bhv_orange_number_init),
	p_while(),
		p_program(bhv_orange_number_loop),
	p_loop(),
};

const BehaviorScript bhvMantaRay[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, manta_seg5_anims_05008EB4),
	p_set_skelanime_number(MANTA_ANIM_SWIM),
	p_program(bhv_manta_ray_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_manta_ray_loop),
	p_loop(),
};

const BehaviorScript bhvFallingPillar[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_program(bhv_falling_pillar_init),
	p_while(),
		p_program(bhv_falling_pillar_loop),
	p_loop(),
};

const BehaviorScript bhvFallingPillarHitbox[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_falling_pillar_hitbox_loop),
	p_loop(),
};

const BehaviorScript bhvPillarBase[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(jrb_seg7_collision_pillar_base),
	p_while(),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvJrbFloatingBox[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setshapeinfo(jrb_seg7_collision_floating_box),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_jrb_floating_box_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvDecorativePendulum[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_init_room),
	p_program(bhv_decorative_pendulum_init),
	p_while(),
		p_program(bhv_decorative_pendulum_loop),
	p_loop(),
};

const BehaviorScript bhvTreasureChestsShip[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_program(bhv_treasure_chest_ship_init),
	p_while(),
		p_program(bhv_treasure_chest_ship_loop),
	p_loop(),
};

const BehaviorScript bhvTreasureChestsJrb[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_program(bhv_treasure_chest_jrb_init),
	p_while(),
		p_program(bhv_treasure_chest_jrb_loop),
	p_loop(),
};

const BehaviorScript bhvTreasureChests[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_program(bhv_treasure_chest_init),
	p_while(),
		p_program(bhv_treasure_chest_loop),
	p_loop(),
};

const BehaviorScript bhvTreasureChestBottom[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_program(bhv_treasure_chest_bottom_init),
	p_setd(oIntangibleTimer, -1),
	p_while(),
		p_program(bhv_treasure_chest_bottom_loop),
	p_loop(),
};

const BehaviorScript bhvTreasureChestTop[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_treasure_chest_top_loop),
	p_loop(),
};

const BehaviorScript bhvMips[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, mips_seg6_anims_06015634),
	p_setd(oInteractType, INTERACT_GRABBABLE),
	p_BGcheckYset(),
	p_sethitbox(/*Radius*/ 50, /*Height*/ 75),
	p_setd(oIntangibleTimer, 0),
	p_program(bhv_mips_init),
	p_while(),
		p_program(bhv_mips_loop),
	p_loop(),
};

const BehaviorScript bhvYoshi[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, yoshi_seg5_anims_05024100),
	p_setobjname(INTERACT_TEXT),
	p_BGcheckYset(),
	p_sethitbox(/*Radius*/ 160, /*Height*/ 150),
	p_set_skelanime_number(YOSHI_ANIM_IDLE),
	p_save_nowpos(),
	p_program(bhv_yoshi_init),
	p_while(),
		p_setd(oIntangibleTimer, 0),
		p_program(bhv_yoshi_loop),
	p_loop(),
};

const BehaviorScript bhvKoopa[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, koopa_seg6_anims_06011364),
	p_set_skelanime_number(KOOPA_ANIM_WALK),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 50, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_set_scale(/*Unused*/ 0, /*Field*/ 150),
	p_setf(oKoopaAgility, 1),
	p_program(bhv_koopa_init),
	p_while(),
		p_program(bhv_koopa_update),
	p_loop(),
};

const BehaviorScript bhvKoopaRaceEndpoint[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_makeobj(/*Bhv param*/ 0, /*Model*/ MODEL_KOOPA_FLAG, /*Behavior*/ bhvKoopaFlag),
	p_while(),
		p_program(bhv_koopa_race_endpoint_update),
	p_loop(),
};

const BehaviorScript bhvKoopaFlag[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_setobjname(INTERACT_POLE),
	p_sethitbox(/*Radius*/ 80, /*Height*/ 700),
	p_setd(oIntangibleTimer, 0),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, koopa_flag_seg6_anims_06001028),
	p_set_skelanime_number(KOOPA_FLAG_ANIM_WAVE),
	p_while(),
	//	p_program(bhv_pole_base_loop),
	p_loop(),
};

const BehaviorScript bhvPokey[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_pokey_update),
	p_loop(),
};

const BehaviorScript bhvPokeyBodyPart[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setmovedata(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_softspritemodeON(),
	p_while(),
		p_program(bhv_pokey_body_part_update),
	p_loop(),
};

const BehaviorScript bhvSwoop[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, swoop_seg6_anims_060070D0),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 50, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_program(bhv_init_room),
	p_set_scale(/*Unused*/ 0, /*Field*/ 0),
	p_while(),
		p_program(bhv_swoop_update),
	p_loop(),
};

const BehaviorScript bhvFlyGuy[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, flyguy_seg8_anims_08011A64),
	p_set_skelanime_number(FLY_GUY_ANIM_FLYING),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 50, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
	p_program(bhv_init_room),
	p_setd(oInteractionSubtype, INT_SUBTYPE_TWIRL_BOUNCE),
	p_setf(oGraphYOffset, 30),
	p_set_scale(/*Unused*/ 0, /*Field*/ 150),
	p_while(),
		p_program(bhv_fly_guy_update),
	p_loop(),
};

const BehaviorScript bhvGoomba[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, goomba_seg8_anims_0801DA4C),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_program(bhv_goomba_init),
	p_while(),
		p_program(bhv_goomba_update),
	p_loop(),
};

const BehaviorScript bhvGoombaTripletSpawner[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_while(),
		p_program(bhv_goomba_triplet_spawner_update),
	p_loop(),
};

#ifdef FLOOMBAS
const BehaviorScript bhvFloomba[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setd(oIsFloomba, TRUE),
	p_jmp(bhvGoomba + 1),
};

#ifdef INTRO_FLOOMBAS
const BehaviorScript bhvFloombaStartup[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setd(oIsFloomba, TRUE),
	p_setd(oAction, FLOOMBA_ACT_STARTUP),
	p_setbit(oFlags, OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, goomba_seg8_anims_0801DA4C),
	p_save_nowpos(),
	p_program(bhv_goomba_init),
	p_setf(oDrawingDistance, 30000),
	p_setd(oIntangibleTimer, -1),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_goomba_update),
	p_loop(),
};
#endif

const BehaviorScript bhvFloombaTripletSpawner[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setd(oIsFloomba, TRUE),
	p_jmp(bhvGoombaTripletSpawner + 1),
};
#endif

const BehaviorScript bhvChainChomp[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, chain_chomp_seg6_anims_06025178),
	p_set_skelanime_number(CHAIN_CHOMP_ANIM_CHOMPING),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	P_shapeOFF(),
	p_save_nowpos(),
	p_setf(oGraphYOffset, 240),
	p_set_scale(/*Unused*/ 0, /*Field*/ 200),
	p_makeobj(/*Bhv param*/ 0, /*Model*/ MODEL_WOODEN_POST, /*Behavior*/ bhvWoodenPost),
	p_while(),
		p_program(bhv_chain_chomp_update),
	p_loop(),
};

const BehaviorScript bhvChainChompChainPart[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setf(oGraphYOffset, 40),
	p_set_scale(/*Unused*/ 0, /*Field*/ 200),
	p_while(),
		p_program(bhv_chain_chomp_chain_part_update),
	p_loop(),
};

const BehaviorScript bhvWoodenPost[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(poundable_pole_collision_wooden_post),
	p_set_pointer_long(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setd(oNumLootCoins, 5),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 50),
	p_while(),
		p_program(bhv_wooden_post_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvChainChompGate[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(bob_seg7_collision_chain_chomp_gate),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_chain_chomp_gate_init),
	p_while(),
		p_program(bhv_chain_chomp_gate_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWigglerHead[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, wiggler_seg5_anims_0500EC8C),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	P_shapeOFF(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 400),
	p_setf(oWigglerFallThroughFloorsHeight, 5000),
	p_while(),
		p_program(bhv_wiggler_update),
	p_loop(),
};

const BehaviorScript bhvWigglerBody[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, wiggler_seg5_anims_0500C874),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_set_scale(/*Unused*/ 0, /*Field*/ 400),
	p_while(),
		p_program(bhv_wiggler_body_part_update),
	p_loop(),
};

const BehaviorScript bhvEnemyLakitu[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, lakitu_enemy_seg5_anims_050144D4),
	p_set_skelanime_number(ENEMY_LAKITU_ANIM_SPAWN),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 40, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_enemy_lakitu_update),
	p_loop(),
};

const BehaviorScript bhvCameraLakitu[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, lakitu_seg6_anims_060058F8),
	p_set_skelanime_number(CAMERA_LAKITU_ANIM_DEFAULT),
	p_program(bhv_init_room),
	p_program(bhv_camera_lakitu_init),
	p_while(),
		p_program(bhv_camera_lakitu_update),
	p_loop(),
};

const BehaviorScript bhvCloud[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_save_nowpos(),
	p_setd(oOpacity, 240),
	p_while(),
		p_program(bhv_cloud_update),
	p_loop(),
};

const BehaviorScript bhvCloudPart[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setd(oOpacity, 240),
	p_while(),
		p_program(bhv_cloud_part_update),
	p_loop(),
};

const BehaviorScript bhvSpiny[] = {
	p_initialize(OBJ_LIST_PUSHABLE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, spiny_seg5_anims_05016EAC),
	p_set_skelanime_number(SPINY_ANIM_DEFAULT),
	p_setmovedata(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_spiny_update),
	p_loop(),
};

const BehaviorScript bhvMontyMole[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, monty_mole_seg5_anims_05007248),
	p_set_skelanime_number(MONTY_MOLE_ANIM_BEGIN_JUMP_INTO_HOLE),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	P_shapeOFF(),
	p_setd(oIntangibleTimer, -1),
	p_setf(oGraphYOffset, -60),
	p_set_scale(/*Unused*/ 0, /*Field*/ 150),
	p_wait(1),
	p_program(bhv_monty_mole_init),
	p_while(),
		p_program(bhv_monty_mole_update),
	p_loop(),
};

const BehaviorScript bhvMontyMoleHole[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 150),
	p_while(),
		p_program(bhv_monty_mole_hole_update),
	p_loop(),
};

const BehaviorScript bhvMontyMoleRock[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setf(oGraphYOffset, 10),
	p_set_scale(/*Unused*/ 0, /*Field*/ 200),
	p_while(),
		p_program(bhv_monty_mole_rock_update),
	p_loop(),
};

const BehaviorScript bhvPlatformOnTrack[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setmovedata(/*Wall hitbox radius*/ 50, /*Gravity*/ -100, /*Bounciness*/ -50, /*Drag strength*/ 100, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_init_room),
	p_program(bhv_platform_on_track_init),
	p_while(),
		p_program(bhv_platform_on_track_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTrackBall[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_program(bhv_init_room),
	p_set_scale(/*Unused*/ 0, /*Field*/ 15),
	p_while(),
		p_program(bhv_track_ball_update),
	p_loop(),
};

const BehaviorScript bhvSeesawPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_seesaw_platform_init),
	p_while(),
		p_program(bhv_seesaw_platform_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvFerrisWheelAxle[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_addd(oMoveAngleYaw, 0x4000),
	p_program(bhv_ferris_wheel_axle_init),
	p_while(),
		p_addd(oFaceAngleRoll, 400),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvFerrisWheelPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_ferris_wheel_platform_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvWaterBombSpawner[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_while(),
		p_program(bhv_water_bomb_spawner_update),
	p_loop(),
};

const BehaviorScript bhvWaterBomb[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setmovedata(/*Wall hitbox radius*/ 120, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_water_bomb_update),
	p_loop(),
};

const BehaviorScript bhvWaterBombShadow[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_scale(/*Unused*/ 0, /*Field*/ 150),
	p_while(),
		p_program(bhv_water_bomb_shadow_update),
	p_loop(),
};

const BehaviorScript bhvTTCRotatingSolid[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 450),
	p_program(bhv_ttc_rotating_solid_init),
	p_setd(oTTCRotatingSolidNumTurns, 1),
	p_while(),
		p_program(bhv_ttc_rotating_solid_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTTCPendulum[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(ttc_seg7_collision_clock_pendulum),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oCollisionDistance, 1500),
	p_program(bhv_ttc_pendulum_init),
	p_setf(oTTCPendulumAccelDir, 1),
	p_while(),
		p_program(bhv_ttc_pendulum_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTTCTreadmill[] = {
	p_initialize(OBJ_LIST_SURFACE),
#ifdef PLATFORM_DISPLACEMENT_2
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_VELOCITY_PLATFORM)),
#else
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
#endif
	p_setf(oCollisionDistance, 750),
	p_program(bhv_ttc_treadmill_init),
	p_wait(1),
	p_while(),
		p_program(bhv_ttc_treadmill_update),
		p_program(cur_obj_compute_vel_xz),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTTCMovingBar[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(ttc_seg7_collision_sliding_surface),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 550),
	p_program(bhv_ttc_moving_bar_init),
	p_while(),
		p_program(bhv_ttc_moving_bar_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTTCCog[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oCollisionDistance, 400),
	p_program(bhv_ttc_cog_init),
	p_while(),
		p_program(bhv_ttc_cog_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTTCPitBlock[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 350),
	p_program(bhv_ttc_pit_block_init),
	p_while(),
		p_program(bhv_ttc_pit_block_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTTCElevator[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(ttc_seg7_collision_clock_platform),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 400),
	p_program(bhv_ttc_elevator_init),
	p_setf(oTTCElevatorDir, 1),
	p_while(),
		p_program(bhv_ttc_elevator_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvTTC2DRotator[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(ttc_seg7_collision_clock_main_rotation),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oCollisionDistance, 1800),
	p_program(bhv_ttc_2d_rotator_init),
	p_while(),
		p_program(bhv_ttc_2d_rotator_update),
	p_loop(),
};

const BehaviorScript bhvTTCSpinner[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(ttc_seg7_collision_rotating_clock_platform2),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_setf(oCollisionDistance, 450),
	p_while(),
		p_program(bhv_ttc_spinner_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvMrBlizzard[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, snowman_seg5_anims_0500D118),
	p_set_skelanime_number(MR_BLIZZARD_ANIM_SPAWN_SNOWBALL),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_mr_blizzard_init),
	p_setf(oMrBlizzardScale, 1),
	p_while(),
		p_program(bhv_mr_blizzard_update),
	p_loop(),
};

const BehaviorScript bhvMrBlizzardSnowball[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ -300, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_set_scale(/*Unused*/ 0, /*Field*/ 200),
	p_addd(oMoveAngleYaw, -0x5B58),
	p_setf(oForwardVel, 5),
	p_setf(oVelY, -1),
	p_setf(oGraphYOffset, 10),
	p_while(),
		p_program(bhv_mr_blizzard_snowball),
	p_loop(),
};

const BehaviorScript bhvSlidingPlatform2[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_program(bhv_sliding_platform_init),
	p_while(),
		p_program(bhv_sliding_platform_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvOctagonalPlatformRotating[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_program(bhv_rotating_octagonal_plat_init),
	p_while(),
		p_program(bhv_rotating_octagonal_plat_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvAnimatesOnFloorSwitchPress[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oDrawingDistance, 8000),
	p_setf(oCollisionDistance, 8000),
	p_program(bhv_animates_on_floor_switch_press_init),
	p_while(),
		p_program(bhv_animates_on_floor_switch_press_loop),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvActivatedBackAndForthPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_program(bhv_activated_back_and_forth_platform_init),
	p_while(),
		p_program(bhv_activated_back_and_forth_platform_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvRecoveryHeart[] = {
	p_initialize(OBJ_LIST_LEVEL),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_recovery_heart_loop),
	p_loop(),
};

const BehaviorScript bhvWaterBombCannon[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_water_bomb_cannon_loop),
	p_loop(),
};

const BehaviorScript bhvCannonBarrelBubbles[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_bubble_cannon_barrel_loop),
	p_loop(),
};

const BehaviorScript bhvUnagi[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, unagi_seg5_anims_05012824),
	p_set_skelanime_number(UNAGI_ANIM_IDLE_2),
	p_save_nowpos(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 300),
	p_setf(oDrawingDistance, 6000),
	p_program(bhv_unagi_init),
	p_while(),
		p_program(bhv_unagi_loop),
	p_loop(),
};

const BehaviorScript bhvUnagiSubobject[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_unagi_subobject_loop),
	p_loop(),
};

const BehaviorScript bhvDorrie[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(dorrie_seg6_collision_0600F644),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, dorrie_seg6_anims_0600F638),
	p_save_nowpos(),
	p_setf(oCollisionDistance, 30000),
	p_addf(oPosX, 2000),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_dorrie_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvHauntedChair[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, chair_seg5_anims_05005784),
	p_set_skelanime_number(HAUNTED_CHAIR_ANIM_DEFAULT),
	p_setmovedata(/*Wall hitbox radius*/ 40, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_program(bhv_init_room),
	p_program(bhv_haunted_chair_init),
	p_while(),
		p_program(bhv_haunted_chair_loop),
	p_loop(),
};

const BehaviorScript bhvMadPiano[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, mad_piano_seg5_anims_05009B14),
	p_setmovedata(/*Wall hitbox radius*/ 40, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_addd(oMoveAngleYaw, 0x4000),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_mad_piano_update),
	p_loop(),
};

const BehaviorScript bhvFlyingBookend[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, bookend_seg5_anims_05002540),
	p_set_skelanime_number(FLYING_BOOKEND_ANIM_SPAWN),
	p_setmovedata(/*Wall hitbox radius*/ 60, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setd(oMoveFlags, OBJ_MOVE_NONE),
	p_set_scale(/*Unused*/ 0, /*Field*/ 70),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_flying_bookend_loop),
	p_loop(),
};

const BehaviorScript bhvBookendSpawn[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_bookend_spawn_loop),
	p_loop(),
};

const BehaviorScript bhvHauntedBookshelfManager[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_haunted_bookshelf_manager_loop),
	p_loop(),
};

const BehaviorScript bhvBookSwitch[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setf(oGraphYOffset, 30),
	p_addd(oMoveAngleYaw, 0x4000),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_book_switch_loop),
	p_loop(),
};

const BehaviorScript bhvMovingFlame[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_moving_flame_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvMovingFlameEmber[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ 200, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_moving_flame_particle_loop),
		p_addd(oAnimState, 1),
	p_loop(),
};

const BehaviorScript bhvFireSpitter[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 40),
	p_while(),
		p_program(bhv_fire_spitter_update),
	p_loop(),
};

const BehaviorScript bhvSnufit[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_program(bhv_init_room),
	p_while(),
		p_setd(oSnufitRecoil, 0),
		p_program(bhv_snufit_loop),
	p_loop(),
};

const BehaviorScript bhvSnufitBalls[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_softspritemodeON(),
	p_setmovedata(/*Wall hitbox radius*/ 10, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_program(bhv_init_room),
	p_setf(oGraphYOffset, 10),
	p_set_scale(/*Unused*/ 0, /*Field*/ 10),
	p_while(),
		p_program(bhv_snufit_balls_loop),
	p_loop(),
};

const BehaviorScript bhvHorizontalGrindel[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(ssl_seg7_collision_grindel),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_set_scale(/*Unused*/ 0, /*Field*/ 90),
	p_program(bhv_horizontal_grindel_init),
	p_while(),
		p_program(cur_obj_update_floor_and_walls),
		p_program(bhv_horizontal_grindel_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvEyerokBoss[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_eyerok_boss_loop),
	p_loop(),
};

const BehaviorScript bhvEyerokHand[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, eyerok_seg5_anims_050116E4),
	p_set_skelanime_number(EYEROK_HAND_ANIM_SLEEPING),
	p_setmovedata(/*Wall hitbox radius*/ 150, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_setd(oAnimState, EYEROK_HAND_ANIM_STATE_EYE_CLOSED),
	p_while(),
		p_program(bhv_eyerok_hand_loop),
	p_loop(),
};

const BehaviorScript bhvKlepto[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, klepto_seg5_anims_05008CFC),
	p_set_skelanime_number(KLEPTO_ANIM_DIVE_0),
	p_setmovedata(/*Wall hitbox radius*/ 100, /*Gravity*/ 0, /*Bounciness*/ -20, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_save_nowpos(),
	p_program(bhv_klepto_init),
	p_while(),
		p_program(bhv_klepto_update),
	p_loop(),
};

const BehaviorScript bhvBird[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, birds_seg5_anims_050009E8),
	p_set_skelanime_number(BIRD_ANIM_FLY),
	P_shapeOFF(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 70),
	p_while(),
		p_program(bhv_bird_update),
	p_loop(),
};

const BehaviorScript bhvRacingPenguin[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, penguin_seg5_anims_05008B74),
	p_set_skelanime_number(PENGUIN_ANIM_IDLE),
	p_setmovedata(/*Wall hitbox radius*/ 300, /*Gravity*/ -800, /*Bounciness*/ -5, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_set_scale(/*Unused*/ 0, /*Field*/ 400),
	p_program(bhv_racing_penguin_init),
	p_while(),
		p_program(bhv_racing_penguin_update),
	p_loop(),
};

const BehaviorScript bhvPenguinRaceFinishLine[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_penguin_race_finish_line_update),
	p_loop(),
};

const BehaviorScript bhvPenguinRaceShortcutCheck[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_while(),
		p_program(bhv_penguin_race_shortcut_check_update),
	p_loop(),
};

const BehaviorScript bhvCoffinSpawner[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_coffin_spawner_loop),
	p_loop(),
};

const BehaviorScript bhvCoffin[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(bbh_seg7_collision_coffin),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_program(bhv_init_room),
	p_while(),
		p_program(bhv_coffin_loop),
	p_loop(),
};

const BehaviorScript bhvClamShell[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_BGcheckYset(),
	p_set_pointer(oAnimations, clam_shell_seg5_anims_05001744),
	p_setf(oGraphYOffset, 10),
	p_while(),
		p_program(bhv_clam_loop),
	p_loop(),
};

const BehaviorScript bhvSkeeter[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, skeeter_seg6_anims_06007DE0),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 180, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 1200, /*Unused*/ 0, 0),
	p_while(),
		p_program(bhv_skeeter_update),
	p_loop(),
};

const BehaviorScript bhvSkeeterWave[] = {
	p_initialize(OBJ_LIST_UNIMPORTANT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_skeeter_wave_update),
	p_loop(),
};

const BehaviorScript bhvSwingPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(rr_seg7_collision_pendulum),
	p_setbit(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_setf(oCollisionDistance, 2000),
	p_program(bhv_swing_platform_init),
	p_while(),
		p_program(bhv_swing_platform_update),
		p_program(load_object_collision_model),
	p_loop(),
};

const BehaviorScript bhvDonutPlatformSpawner[] = {
	p_initialize(OBJ_LIST_SPAWNER),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_donut_platform_spawner_update),
	p_loop(),
};

const BehaviorScript bhvDonutPlatform[] = {
	p_initialize(OBJ_LIST_SURFACE),
	p_setshapeinfo(rr_seg7_collision_donut_platform),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_while(),
		p_program(bhv_donut_platform_update),
	p_loop(),
};

const BehaviorScript bhvDDDPole[] = {
	p_initialize(OBJ_LIST_POLELIKE),
	p_setobjname(INTERACT_POLE),
	p_sethitbox(/*Radius*/ 80, /*Height*/ 800),
	p_setd(oIntangibleTimer, 0),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_save_nowpos(),
	p_program(bhv_ddd_pole_init),
	p_setf(oDDDPoleVel, 10),
	p_while(),
		p_program(bhv_ddd_pole_update),
	//	p_program(bhv_pole_base_loop),
	p_loop(),
};

const BehaviorScript bhvRedCoinStarMarker[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_BGcheckYset(),
	p_set_scale(/*Unused*/ 0, /*Field*/ 150),
	p_setd(oFaceAnglePitch, 0x4000),
	p_addf(oPosY, 60),
	p_program(bhv_red_coin_star_marker_init),
	p_while(),
		p_addd(oFaceAngleYaw, 0x100),
	p_loop(),
};

const BehaviorScript bhvTripletButterfly[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, butterfly_seg3_anims_030056B0),
	p_set_skelanime_number(BUTTERFLY_ANIM_FLYING),
	P_shapeOFF(),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 0, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
	p_setf(oTripletButterflyScale, 1),
	p_while(),
		p_program(bhv_triplet_butterfly_update),
	p_loop(),
};

const BehaviorScript bhvBubba[] = {
	p_initialize(OBJ_LIST_GENACTOR),
	p_setbit(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_save_nowpos(),
	p_setmovedata(/*Wall hitbox radius*/ 200, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
	p_set_scale(/*Unused*/ 0, /*Field*/ 50),
	p_while(),
		p_program(bhv_bubba_loop),
	p_loop(),
};

const BehaviorScript bhvBeginningLakitu[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, lakitu_seg6_anims_060058F8),
	p_set_skelanime_number(INTRO_LAKITU_ANIM_DEFAULT),
	p_setd(oOpacity, 0),
	p_while(),
		p_program(bhv_intro_lakitu_loop),
	p_loop(),
};

const BehaviorScript bhvBeginningPeach[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_set_pointer(oAnimations, peach_seg5_anims_0501C41C),
	p_set_skelanime_number(PEACH_ANIM_0),
	p_while(),
		p_program(bhv_intro_peach_loop),
	p_loop(),
};

const BehaviorScript bhvEndBirds1[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, birds_seg5_anims_050009E8),
	p_set_skelanime_number(END_BIRDS_ANIM_FLY),
	p_while(),
		p_program(bhv_end_birds_1_loop),
	p_loop(),
};

const BehaviorScript bhvEndBirds2[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
	p_set_pointer(oAnimations, birds_seg5_anims_050009E8),
	p_set_skelanime_number(END_BIRDS_ANIM_FLY),
	p_while(),
		p_program(bhv_end_birds_2_loop),
	p_loop(),
};

const BehaviorScript bhvIntroScene[] = {
	p_initialize(OBJ_LIST_DEFAULT),
	p_setbit(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	p_while(),
		p_program(bhv_intro_scene_loop),
	p_loop(),
};


