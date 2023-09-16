// Master object spawner for test level.

#include "game/game_init.h"

struct ObjectHitbox hard180yr_Hitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 50,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 50,
    /* hurtboxHeight:     */ 50,
};


void hard180yr_main(void) {

s16 position = o->oPosX;

    position += 24;

    if (position > 4096) { // despawn.
        s_remove_obj(o);
    }

    o->oInteractStatus = INT_STATUS_NONE;
}