// Master object spawner for test level.

#include "game/game_init.h"

struct ObjectHitbox mspawnertestlev_Hitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 50,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 50,
    /* hurtboxHeight:     */ 50,
};


void lvltest_scr(void) {

    MAPOBJ(200, 100, 100, 5000, MODEL_MARIO, P_Elaser);
    MAPOBJ(200, -100, 100, 5000, MODEL_MARIO, P_Elaser);


    o->oInteractStatus = INT_STATUS_NONE;
}