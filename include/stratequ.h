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


/******************************
--HOW TO SET AND CLEAR FLAGS--

set:
flags |= FLAG_A; // Set FLAG_A

clear:
flags &= ~FLAG_B; // Clear FLAG_B

********************************/

/*
player's ship flags.
   there are 3 ship flag bytes.
   each bit corresponds to a different player status flag.
   only 5 bytes are used in flags3.
*/
// carried over from the original SNES source (converted to C syntax of course)
// as a bonus, this saves on RAM! (only uses 3 bytes)

extern int pshipflags; // was an 8-bit alc
#define psf_bodycoll (1 << 0)       // 00000001 (1)
#define psf_LWingcoll (1 << 1)      // 00000010 (2)
#define psf_Rwingcoll (1 << 2)      // 00000100 (4)
#define psf_brkLWing (1 << 3)       // 00001000 (8)
#define psf_brkRwing (1 << 4)       // 00010000 (16)
#define psf_noctrl (1 << 5)         // 00100000 (32)
#define psf_nofire (1 << 6)         // 01000000 (64)
#define psf_noYctrl (1 << 7)        // 10000000 (128)

extern int pshipflags2; // was an 8-bit alc
#define psf2_doublaser (1 << 0)     // 00000001 (1)
#define psf2_wireship (1 << 1)      // 00000010 (2)
#define psf2_nospark (1 << 2)       // 00000100 (4)
#define psf2_turn180 (1 << 3)       // 00001000 (8)
#define psf2_forceboost (1 << 4)    // 00010000 (16)
#define psf2_boosting (1 << 5)      // 00100000 (32)
#define psf2_braking (1 << 6)       // 01000000 (64)
#define psf2_playerHP0 (1 << 7)     // 10000000 (128)

extern int pshipflags3; // was an 8-bit alc
#define psf3_intunnel  (1 << 0)     // 00000001 (1)
#define psf3_enginesnd (1 << 1)     // 00000010 (2)
#define psf3_forcebrake (1 << 2)    // 00000100 (4)
#define psf3_nocollisions (1 << 3)  // 00001000 (8)
#define psf3_beamball (1 << 4)      // 00010000 (16)
// last 3 bits unused... (space for more flags someday?)

// Player's flying mode flags.
extern int playerflymode; // was an 8-bit alc
#define pfm_diefall (1 << 0)    // 00000001 (1)
#define pfm_dieYrot (1 << 1)    // 00000010 (2)
#define pfm_water (1 << 2)      // 00000100 (4)
#define pfm_shadows (1 << 3)    // 00001000 (6)      
#define pfm_wobble (1 << 4)     // 00010000 (8)

extern int splayerflymode; // was an 8-bit alc
#define spfm_norm 0
#define spfm_close 1
#define spfm_toinside 2
#define spfm_inside 3
#define spfm_tonorm 4
#define spfm_maxmode 5

extern int splayerflymodeopt; // was an 8-bit alc
#define spfmo_AB spfm_inside
#define spfmo_ABC spfm_maxmode

// Player's strategy flags.
// TODO: figure out if bit 3 of pstratflags is used anywhere in original game
extern int pstratflags;
#define pstf_novdistC (1 << 0)          // 00000001 (1)
#define pstf_flag1 (1 << 1)             // 00000010 (2)
#define pstf_noviewmove (1 << 2)        // 00000100 (4)
/*bit 3 skipped...           */         // 00001000 (6)
#define pstf_inseq (1 << 4)             // 00010000 (8)  
#define pstf_firstframeLcol (1 << 5)    // 00100000 (16) // first frame player laser collision ON.
#define pstf_notdie (1 << 6)            // 00010000 (32)  

// movement limitations (yet to be converted to C + SM64 units)
/*
pml_Lwleft	equ	1
pml_Rwright	equ	2
pml_Lwtop	equ	4
pml_Lwbottom	equ	8
pml_Rwtop	equ	16
pml_Rwbottom	equ	32
pml_Btop	equ	64
pml_Bbottom	equ	128

pml_all	equ	pml_lwtop!pml_rwtop!pml_lwbottom!pml_rwbottom!pml_lwleft!pml_rwright!pml_Btop!pml_Bbottom

	alc	pmovelimit,1
	alc	pmovelimitAND,1
*/

// player speeds.
extern int maxPspeed;
extern int medPspeed;
extern int minPspeed;

// HUD stuffs
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

