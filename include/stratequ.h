/*************************************************************************\
*                                                                         *
*                               Star Fox                                  *
*                              -----------                                *
*                                                                         *
*                          Nintendo 64 version.                           *
*                                                                         *
*                                                                         *
*                              16x4 Team.      		                      *
*                                                                         *
*_________________________________________________________________________*
*                                                                         *
*  File: STRATEQU.H                                                       *
*_________________________________________________________________________*
*                                                                         *
*  Descr: STRATEGY EQUATES FOR OBJECTS.                                   *
*                                                                         *
\*************************************************************************/
 //***************************************************************************
 //*
 //*
 //* nameHP   = hit count.
 //* nameAP 	= hit count affect on other objects.
 //* nameNS	= number of shots fired.
 //*
 //*
 //*

 //-----------------------------------------------------------------------------
 // Things.

// pshipflags3 (done)
// 0/1 , off/on
extern int psf3_enginesnd;
extern int psf2_boosting;
extern int psf2_braking;

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
extern int pshipflags2;
extern int pshipflags3;
extern int numNukes;
extern int nukelimit;

