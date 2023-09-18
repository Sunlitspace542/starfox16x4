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

//TODO: properly initialize all these where they should be 

// pshipflags3 (done)
extern int psf3_enginesnd;	// 0/1 , off/on
extern int psf2_boosting;
extern int psf2_braking;

// player speeds.
extern int maxPspeed;
extern int medPspeed;
extern int minPspeed;

// hud.c
extern int playerB_HP;
extern int playerB_MaxHP;
extern f32 hp_ratio;
extern f32 shieldMeterMax;
extern f32 shieldMeterScale;
extern f32 boostMeterScale;
extern int numNukes;

