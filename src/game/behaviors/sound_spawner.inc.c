// sound_spawner.inc.c

void bhv_sound_spawner_init(void) {
    s32 sp1C = o->oSoundEffectBits;
    play_sound(sp1C, o->header.gfx.cameraToObject);
}