// player's single laser strategy.

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