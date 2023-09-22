/*************************************************************************\
*                                                                         *
*                               Star Fox                                  *
*                              -----------                                *
*                                                                         *
*                          Nintendo 64 version.                           *
*                                                                         *
*_________________________________________________________________________*
*                                                                         *
*  File: stratequ.h                                                       *
*_________________________________________________________________________*
*                                                                         *
*  Descr: STRATEGY EQUATES FOR OBJECTS.                                   *
*                                                                         *
\*************************************************************************/

/* player's ship flags.
   there are 3 ship flag bytes.
   each bit corresponds to a different player status flag.
   only 5 bytes are used in flags3. */

extern int pshipflags;
#define psf_bodycoll (1 << 0) // 00000001 (1)
#define psf_LWingcoll (1 << 1) // 00000010 (2)
#define psf_Rwingcoll (1 << 2) // 00000100 (4)
#define psf_brkLWing (1 << 3) // 00001000 (8)
#define psf_brkRwing (1 << 4) // 00010000 (16)
#define psf_noctrl (1 << 5) // 00100000 (32)
#define psf_nofire (1 << 6) // 01000000 (64)
#define psf_noYctrl (1 << 7) // 10000000 (128)

extern int pshipflags2;
#define psf2_doublaser (1 << 0) // 00000001 (1)
#define psf2_wireship (1 << 1) // 00000010 (2)
#define psf2_nospark (1 << 2) // 00000100 (4)
#define psf2_turn180 (1 << 3) // 00001000 (8)
#define psf2_forceboost (1 << 4) // 00010000 (16)
#define psf2_boosting (1 << 5) // 00100000 (32)
#define psf2_braking (1 << 6) // 01000000 (64)
#define psf2_playerHP0 (1 << 7) // 10000000 (128)

extern int pshipflags3;
#define psf3_intunnel  (1 << 0) // 00000001 (1)
#define psf3_enginesnd (1 << 1) // 00000010 (2)
#define psf3_forcebrake (1 << 2) // 00000100 (4)
#define psf3_nocollisions (1 << 3) // 00001000 (8)
#define psf3_beamball (1 << 4) // 00010000 (16)


// player speeds.
extern int maxPspeed;
extern int medPspeed;
extern int minPspeed;

// hud.c
extern int playerB_HP;
extern int playerB_MaxHP;
extern f32 bp_ratio;
extern int player_BP; // boost points
extern int player_MaxBP;
extern f32 boostMeterScale;
extern f32 hp_ratio;
extern f32 shieldMeterMax;
extern f32 shieldMeterScale;
extern f32 boostMeterMax;
extern int numNukes;
extern int nukelimit;

