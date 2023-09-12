```
-- PATH64 language to Decomp BhvScript to PATH1 (SF1) --

PATH64 - DECOMP - Closest PATH1 equ.

p_initialize(type) - BEGIN(objList) - START_PATH

p_wait(var) - DELAY(num) - P_WAIT frames

p_jsr(addr) - CALL(addr) - P_GOSUB addr

p_rts - RETURN() - P_RETURN

p_jmp(addr) - GOTO(addr) - P_GOTO

p_do(var) - BEGIN_REPEAT(count) - P_DO number|alvar

p_next - END_REPEAT() - P_NEXT

p_next_imm - END_REPEAT_CONTINUE() - P_INEXT

p_while - BEGIN_LOOP() - P_LOOP number,address

p_loop - END_LOOP() - NONE (maybe P_BREAK?)

p_end - BREAK() - NONE (P_END? maybe P_BREAK)

p_exit - BREAK_UNUSED() - NONE (P_END?)

p_program(addr) - CALL_NATIVE(func) - UNKNOWN

p_addf(index,work) - ADD_FLOAT(field, value) - P_ADD var,value

p_setf(index,work) - SET_FLOAT(field, value) - P_SET var,value

p_addd(index,work) - ADD_INT(field, value) - P_ADD var,value

p_setd(index,work) - SET_INT(field, value) - P_SET var,value

p_setbit(index,flag) - OR_INT(field, value) - NONE

p_clrbit(index,flag) - BIT_CLEAR(field, value) - NONE

p_setangle_random(index,base,offset) - SET_INT_RAND_RSHIFT(field, min, rshift) - NONE

p_setf_random(index,base,offset) - SET_RANDOM_FLOAT(field, min, range) - NONE

p_setd_random(index,base,offset) - SET_RANDOM_INT(field, min, range) - NONE

p_addf_random(index,base,offset) - ADD_RANDOM_FLOAT(field, min, range) - NONE

p_addd_random(index,base,offset) - ADD_INT_RAND_RSHIFT(field, min, rshift) - NONE

p_dprintf(index) - CMD_NOP_1(field) - NONE

p_dprintx(index) - CMD_NOP_2(field) - NONE

p_dprintd(index) - CMD_NOP_3(field) - NONE

p_changeshape(index,shape) - SET_MODEL(modelID) - P_BECOMESHAPE?

p_makeshape(shape,strat) - SPAWN_CHILD(modelID, behavior) NONE

p_killshape - DEACTIVATE() - P_REMOVE?

p_BGcheckYset - DROP_TO_FLOOR() - NONE

p_WADDf(s1,s2,s3) - SUM_FLOAT(fieldDst, fieldSrc1, fieldSrc2) - NONE

p_WADDd(s1,s2,s3) - SUM_INT(fieldDst, fieldSrc1, fieldSrc2) - NONE

p_softspritemodeON - BILLBOARD() - P_SPRITE

P_shapeOFF - HIDE() - P_INVISIBLE

p_sethitbox(Rdata,Hdata) - SET_HITBOX(radius, height) - NONE? I think there is one, in strats at least

p_softspriteanime(animeNo) - CMD_NOP_4(field, value) - NONE

p_wait_work(work) - DELAY_VAR(field) - P_WAIT

p_do_work(work) - BEGIN_REPEAT_UNUSED(count) - P_DO

p_set_pointer(work,addr) - LOAD_ANIMATIONS(field, anims) - NONE

p_set_skelanime_number(n) - ANIMATE(animIndex) - 

p_makeobj(shape,strat,number) - SPAWN_CHILD_WITH_PARAM(bhvParam, modelID, behavior) - NONE?

p_setshapeinfo(addr) - LOAD_COLLISION_DATA(collisionData) - NONE?

p_sethitbox2(Rdata,Hdata,Ldata) - SET_HITBOX_WITH_OFFSET(radius, height, downOffset) - see p_sethitbox

p_makeobj_child(shape,strat) - SPAWN_OBJ(modelID, behavior) - P_SPAWN

p_save_nowpos - SET_HOME() - NONE?

p_setdamagebox(Rdata,Hdata) - SET_HURTBOX(radius, height) - NONE? (See p_sethitbox)

p_setobjname(name) - SET_INTERACT_TYPE(type) - NONE

p_setmovedata(d0,d1,d2,d3,d4,d5,d6,d7) - SET_OBJ_PHYSICS(wallHitboxRadius, gravity, bounciness, dragStrength, friction, buoyancy, unused1, unused2) - NONE

p_setobjinfo(name) - SET_INTERACT_SUBTYPE(subtype) - NONE

p_set_scale(scale) - SCALE(unusedField, percent) - NONE

p_mother_clrbit(index,flag) - PARENT_BIT_CLEAR(field, flags) - NONE

p_inc_frame(index,frame) - ANIMATE_TEXTURE(field, rate) - NONE?

p_shapeDISABLE - DISABLE_RENDERING() - NONE?

p_setlong(index,data) - SET_INT_UNUSED(field, value) - NONE?

p_makeobj_initdata(addr) SPAWN_WATER_DROPLET(dropletParams) - NONE
```

```
-- STRAT64 macros to Decomp ObjHlpr to SF1 strat macros --

STRAT64 - DECOMP - Closest SF1 equ.

s_remove_obj(StrategyRecord *stratp) - obj_mark_for_deletion(struct Object *obj) - s_remove_obj obj1

s_allOFF(void) - ??? - cur_obj_disable(void)

s_hitOFF(void) - cur_obj_become_intangible(void); - s_clr_hitflags obj1,mask

s_hitON(void) - cur_obj_become_tangible(void) - 

s_hitON_obj(StrategyRecord *stp) - obj_become_tangible(struct Object *obj) - 

s_groundcheck(void) - cur_obj_update_floor_height(void) - 

```