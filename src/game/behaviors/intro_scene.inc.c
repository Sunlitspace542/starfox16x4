// intro_scene.inc.c

void spawn_child_obj_relative(struct Object *parent, s16 xOffset, s16 yOffset, s16 zOffset,
                              s16 pitchOffset, s16 yawOffset, s16 rollOffset,
                              s16 forwardVel, ModelID32 model, const BehaviorScript *behavior) {
    struct Object *obj = spawn_object(parent, model, behavior);

    obj->header.gfx.animInfo.animFrame = random_float() * 6.0f;
    obj->oEndBirdCutsceneVars9PointX = sCutsceneVars[9].point[0];

    sCutsceneVars[9].point[0] += 1.0f;

    obj->oPosX += xOffset;
    obj->oPosY += yOffset;

    if (gCutsceneTimer > 700) {
        obj->oPosY += -150.0f;
    }

    obj->oPosZ += zOffset;
    obj->oMoveAnglePitch += pitchOffset;
    obj->oMoveAngleYaw += yawOffset;
    obj->oMoveAngleRoll += rollOffset;
    obj->oForwardVel = forwardVel;
}

void bhv_intro_scene_loop(void) {
    if (gCutsceneObjSpawn != CUTSCENE_OBJ_NONE) {
        o->oPosX = gCamera->pos[0];
        o->oPosY = gCamera->pos[1];
        o->oPosZ = gCamera->pos[2];

        o->oMoveAnglePitch = 0;
        o->oMoveAngleYaw = 0;

        switch (gCutsceneObjSpawn) {

        }

        gCutsceneObjSpawn = CUTSCENE_OBJ_NONE;
    }
}
