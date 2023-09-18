// Player's special weapon (nuke/bomb)

#include "stratequ.h"

void nuke_Istrat(void) {
    int nukelimit;
    cur_obj_scale(1.0f); // scale object
        o->oVelZ = 66 * 2; // Set Z velocity
        o->oForwardVel = 66 * 2; // Set Forward velocity
        o->oTimer++; // increment the object timer
        nukelimit += 1;

    if (o->oTimer > 100) { // despawn if object timer is 100
        nukelimit -= 1;
        s_remove_obj(o); // would be detonate but we can't do that just yet
    }

    if ((gPlayer1Controller->buttonPressed & B_BUTTON) && (o->oTimer > 50)) {
        nukelimit -= 1;
        s_remove_obj(o); // would be detonate but we can't do that just yet
    }
    cur_obj_move_using_fvel_and_gravity(); // actually tell the thing to move
}


/* Original strategy for reference
nuke_Istrat 			; relative to player speed.
	s_start_strat
	s_set_alptrs		x,nuke_strat,weapcollide_Istrat,nukeexp_Istrat
	s_gen_3dvecs		x,al_roty,al_rotx,al_vel,1   ; nuke spd.
	s_addgen_3dvecs		x,al_roty,al_rotx,al_sbyte3  ; mother obj speed

	s_set_alvar		B,x,al_rotx,#0
	s_set_alvar		B,x,al_roty,#deg180
	set_sound2		x,#6
	s_end_strat
nuke_strat
	s_start_strat
	s_remove_ifplayerdead	x
	s_jmp_varAND		B,pshipflags,#psf_nofire,removenuke_Istrat


	s_add_vecs2pos		x
	s_dec_lifecnt		x,1


	s_jmpNOT_varAND		B,playerflymode,#pfm_diefall,.notdead
	s_add_alvar		W,x,al_vy,#2
.notdead


	IFNE	mouseon
	lda	mouse_swt1
	cmp	#2
	beq	.blowupthenuke
	ENDC
	
	s_jmp_keyup		a,.nexp
	s_jmp_lastkeydown	a,.nexp
.blowupthenuke
	s_kill_obj		x
.nexp

	s_jmp_NOTalsflag	x,sflag1,missboundchkexp
	s_end_strat

removenuke_Istrat
	s_start_strat
	IFEQ	INFBOMBS
	s_inc_var	W,specwepcnt
	ENDC
	s_set_var	B,specialdelay,#1
	s_jmp		remove_Istrat


nukeexp_Istrat
	s_start_strat
	s_set_alvar		W,x,al_sword1,#nukeRATE
	s_set_expstrat		x,nukeexp_strat
	s_set_alvar		W,x,al_shape,#nullshape
	s_jsl			makeMEDexpobj_srou
	s_set_vartobeobj	circleobj,x
	big_circle_exp
	trigse			$30
	set_sound2		x,#0
	s_end_strat
nukeexp_strat
	s_start_strat

	a16
	lda	al_sword1,x
	cmp	#nukeMAXRADIUS
	a8
	bmi	.donuke	
	s_remove_obj	x
	s_end_strat
.donuke
	s_add_playerZ		x


	s_jmp_varAND	B,pshipflags2,#psf2_playerHP0,.nonuke

	s_set_find		0
	a16
	lda			al_sword1,x
	sta			svar_word2
	sec
	sbc			#nukeRATE
	sta			svar_word1
	a8
	
.here	
	s_find_radiusobj	y,x,#0,svar_word1,svar_word2,.donefind

	s_jmp_alsflag		y,nohitaffect,.here
	s_jmp_alsflag		y,colldisable,.here
	s_jmpNOT_alflag		y,frontpl,.here

	lda.w			al_hp,y
	bmi			.here
	sec
	sbc			#nukeAP
	bpl			.nneg
	lda			#0
.nneg
	sta.w			al_hp,y
	s_set_alsflag	y,hitflash
	s_set_altype		y,nuked
	brl			.here
.donefind
	s_add_alvar		W,x,al_sword1,#nukeRATE

.nonuke
	s_end_strat

*/