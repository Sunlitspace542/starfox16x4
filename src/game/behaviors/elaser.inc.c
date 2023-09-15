// player's single laser strategy.

#include "types.h"

struct ObjectHitbox sElaserHitbox = {
    /* interactType:      */ INTERACT_KOOPA_SHELL,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 4,
    /* health:            */ 1,
    /* numLootCoins:      */ 1,
    /* radius:            */ 50,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 50,
    /* hurtboxHeight:     */ 50,
};


void elaser_Istrat(void) {

s16 position = o->oPosX;

    position += 24;

    if (position > 4096) { // despawn.
        s_remove_obj(o);
    }

    o->oInteractStatus = INT_STATUS_NONE;
}