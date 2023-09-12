/*;use set pos 
; z>= 1500, y=anywhere but above ground
;use shape "r_bu_1"

	START_PATH	e_dosun

	P_INVINCIBLE	ON
	P_SET		roty,128

.e_do_0
	P_DISTLESS		1300,.e_do_1
	P_GOTO		.e_do_0

.e_do_1
	P_ADD		worldx,-10
	P_WAIT		2
	P_ADD		worldx,20
	P_WAIT		2
	P_ADD		worldx,-10
	P_LOOP		2,.e_do_1

.e_do_2
	P_IFBETWEEN		-41,worldy,0,.e_do_3
	P_ADD		worldy,40
	P_GOTO		.e_do_2

.e_do_3
	P_SOUNDEFFECT	$49
	P_SET		worldy,-50

	P_END
*/
const BehaviorScript bhvDosunMain[] = {
	BEGIN(OBJ_LIST_GENACTOR), // START_PATH e_dosun
	SET_HITBOX(/*Radius*/ 24, /*Height*/ 16), // P_INVINCIBLE // set hitbox?
	obj_set_angle(o, 0, 128, 0); // P_SET roty,128
    CALL_NATIVE(bhvDosunDo0), // goto do0
}

const BehaviorScript bhvDosunDo0[] = { //.e_do_0
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO)), // not sure how distance from player is actually calculated
	if (gCurrentObject->oDistanceToMario < 1300) { //P_DISTLESS 1300,.e_do_1
		CALL_NATIVE(bhvDosunDo1),
	}else{
		CALL_NATIVE(bhvDosunDo0), //P_GOTO .e_do_0
	}
}

const BehaviorScript bhvDosunDo1[] = { //.e_do_1
	ADD_INT(oPosX, -10) // P_ADD worldx,-10
	DELAY(2), // P_WAIT 2
	ADD_INT(oPosX,  20) // P_ADD worldx,20
	DELAY(2), // P_WAIT 2
	ADD_INT(oPosX, -10) // P_ADD worldx,-10
    BEGIN_LOOP(), //P_LOOP 2,.e_do_1
        CALL_NATIVE(bhvDosunDo1),
		CALL_NATIVE(bhvDosunDo1),
    END_LOOP(),
	CALL_NATIVE(bhvDosunDo2), // to go to do2
}

const BehaviorScript bhvDosunDo2[] = { //.e_do_2

	if (0 < oPosY < -41) { //P_IFBETWEEN -41,worldy,0,.e_do_3
		CALL_NATIVE(bhvDosunDo3),
	}else{
		ADD_INT(oPosY, 40) //P_ADD worldy,40
		CALL_NATIVE(bhvDosunDo2), //P_GOTO .e_do_2
	}
	
}

const BehaviorScript bhvDosunDo3[] = { //.e_do_3
    cur_obj_play_sound_2(SOUND_OBJ_THWOMP); //P_SOUNDEFFECT	$49
	SET_INT(oPosY, -50) //P_SET worldy,-50
	END_LOOP(),
}
