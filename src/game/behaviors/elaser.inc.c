// player's single laser strategy.

// original PATH from SF1 (reference):
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