// player's single laser strategy.

void elaser_Istrat(void) {
    if (o->oTimer == 0) {
        o->oVelZ = 66 * 2;
        o->oForwardVel = 66 * 2;
    }

    if (o->oPosZ > 4096) { // despawn.
        s_remove_obj(o);
    }
    cur_obj_move_using_fvel_and_gravity();
}