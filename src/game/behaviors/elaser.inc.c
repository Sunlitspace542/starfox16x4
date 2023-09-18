// player's single laser strategy.

// original PATH and strat from SF1 (reference):
/*
fire_Elaser	; player's laser.
	s_make_obj		#elaser2,.badobj
	s_set_aldata		y,#1,#elaserAP
	s_set_alptrs		y,Pelaser_Istrat,pelasercollide_Istrat,pelaser2die_Istrat
	s_set_speed		y,#66
	s_set_lifecnt		y,#10
	s_set_colltype		y,laser
	s_set_colltype		y,friend
	jsr			gen_weapon
.badobj	rtl
*/

/*
elaser_Istrat 			
	s_start_strat
	s_set_strat		x,elaser_strat
	s_copy_alvar2alvar	B,x,al_rotx,x,al_sbyte1
	s_copy_alvar2alvar	B,x,al_roty,x,al_sbyte2

	s_gen_3dvecs		x,al_roty,al_rotx,al_vel,1   ; laser spd.

	s_init_anim		x,#0
	s_end_strat
elaser_strat
	s_start_strat
 
	s_cmp_anim		x,#4
	s_beq			.nai
	s_add_anim		x,#2,#8
.nai
	s_add_vecs2pos		x

	s_decbne_lifecnt	x,.lnd
	s_remove_obj		x
	s_end_strat
.lnd
	s_brl			miss_end

*/


void elaser_Istrat(void) {
    cur_obj_scale(1.0f);
        o->oVelZ = 66 * 4;
        o->oForwardVel = 66 * 4;
        o->oTimer++;

    // TODO: add collisions with objects

    if (o->oTimer > 100) { // despawn.
        s_remove_obj(o);
    }
    cur_obj_move_using_fvel_and_gravity();
}