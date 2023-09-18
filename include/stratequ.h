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

int Xspacebarlen = 500;
int Xspacebarsize = 50;
int Yspacebarlen = 500;
int Yspacebarsize = 50;
int Zspacebarlen = 500;
int Zspacebarsize = 50;


int SXspacebarlen = 250;
int SXspacebarsize = 50;
int SYspacebarlen = 250;
int SYspacebarsize = 50;
int SZspacebarlen = 250;
int SZspacebarsize = 50;




 //-----------------------------------------------------------------------------
 // STATIC NEUTRAL.

int tunnelHP = 20;
int hardAP = 8;
int rockhardAP = 20;
int hardHP = -1;
int core1HP = 6;


 //-----------------------------------------------------------------------------
 // WEAPON HP/AP

int missile1AP = 8;
int kamihmissile1HP = 2;
int kamihmissile1AP = 8;
int hmissile1HP = 2;
int hmissile1AP = 8;
int hmissile2HP = 8;
int hmissile2AP = 4;		
int missile2HP = 2;		
int missile2AP = 4;		
int phazerAP = 1;		
int enemylaserAP = 2;		
int plasmaAP = 10;		
int HplasmaAP = 10;		
 // // Nova Bomb (Nuke) Parameters
int nukeAP = 8;		 // on each object.
int nukeRATE = 200;		 //
int nukeMAXRADIUS = 7000;		 //
int defaultNukeCount = 3;
 // //

 // // ELASER

int elaserAP = 4;
int playerbeamAP = 5;

 //-----------------------------------------------------------------------------
 // MOVING ENEMY.

int windmillHP = 6;
int windmillAP = 4;
int bee1HP = 4;
int bee1AP = 6;
int domaHP = 2;
int starbullHP = 16;		 // G
int starbullAP = 1;		 // G
int textbullHP = 30;		 // G
int textbullNS = 20;		 // G
int walkerHP = 5;		 // G
int misspodHP = 2;
int misspodAP = 16;
int fighterHP = 4;
int fighterAP = 4;
int flypillarHP = 12;
int flypillarAP = 16;
int sokutenHP = 16;
int sokutenAP = 16;
int wormHP = 2;
int wormAP = 4;
int sharkHP = 4;
int sharkAP = 6;
int ship1HP = 20;
int ship1AP = 16;
int ship2HP = 40;
int ship2AP = 16;
int ship3HP = -1;
int ship3AP = 16;
int ship4HP = -1;
int ship4AP = 16;
int torpedoHP = 4;
int torpedoAP = 4;
int crabHP = 4;
int crabAP = 4;
int kamiHP = 4;
int kamiAP = 8;
int jump0HP = 2;
int jump0AP = 4;
int jump1HP = -1;
int jump1AP = 8;
int truckHP = 4;
int truckAP = 8;
int patrolHP = 4;
int patrolAP = 4;
int evaderHP = 8;
int evaderAP = 4;
int woodsHP = 2;
int woodsAP = 8;
int misstankHP = 4;
int misstankAP = 8;
int houdaiHP = 8;
int houdaiAP = 8;
int zaco1HP = 2;
int zaco1AP = 4;
int zaco2HP = 4;
int zaco2AP = 4;
int Szaco0HP = 4;
int Szaco0AP = 8;
int Szaco2HP = 2;
int Szaco2AP = 8;
int Szaco5HP = 2;
int Szaco5AP = 8;
int FzacoHP = 4;
int FzacoAP = 8;
int door1AP = 8;
int zacosHP = 2;
int zacosAP = 4;
int raderHP = 8;
int raderAP = 4;
int friendHP = 8;
int friendAP = 4;
int wlHP = 8;
int wlAP = 16;
int ripmanHP = 4;
int ripmanAP = 16;
int winglazermanHP = 8;
int winglazermanAP = 16;
int up1manAP = 8;
int bomwingHP = 4;
int bomwingAP = 8;
int wiremanHP = 4;
int wiremanAP = 16;

int MOTHERDIST = 1600;
int TURRETDIST = 1300;
int flyHP = 2;
int flyAP = 4;
int flyDIST = 700;
int flyFC = 4;	 // amount of times the fly fires
int cubeHP = 100;
int cubeAP = 16;
int saucer1HP = 12;
int saucer1AP = 1;
int saucer1FC = 2;
int saucer1DIST = 400;
int paraHP = 2;
int paraAP = 4;
int paraSWINGSPD = 5;
int paraSWINGMAX = 15;
int pillar3HP = 8;
int pillar3fallHP  = 4;
int pillar3AP = 8;
int pillar3DIST = 500;
int floor1HP = 5;
int floor1AP = 2;
int floor1DIST = 600;
int walkingHP = 8;
int walkingAP = 16;
int wall1AP = 16;
int wall1DIST = 600;
int meteorHP = 2;
int meteorAP = 12;
int beamboxHP = 10;
int beamboxAP = 8;
int swingwalHP = 20;
int swingwalAP = 8;
int irisHP = 2;
int irisAP = 8;
int swingHP = 12;
int swingAP = 6;
int cameleonHP = 2;
int cameleonAP = 8;
int hiderHP = 2;
int hiderAP = 6;
int mine0HP = 2;
int mine0AP = 10;
int dbossHP = 10;
int dbossAP = 10;
int crown3HP = 8;
int crown3AP = 8;
int saucerHP = 10;
int saucerAP = 4;
int ejectHP = 8;
int ejectAP = 8;
int ruiser2launcherHP = 4;
int bazookaHP = 8;
int bazookaAP = 16;
int upermHP = 2;
int upermAP = 8;
int warpHP = 4;
int warpAP = 8;
int tank2HP = 40;
int tank2AP = 32;
int dragonflyHP = 2;
int dragonflyAP = 8;
int SdragonflyHP = 2;
int SdragonflyAP = 4;
int shou0HP = 2;
int shou0AP = 12;
int walker2HP = 10;
int walker2AP = 8;

 //-----------------------------------------------------------------------------
 // BOSS ENEMY

int boss1turretHP = 8;		 // barricader
int boss1turretAP = 16;
int boss1HP = 70;
int boss2covAP = 16;

int boss2turretHP = 16;		 // spin top
int boss2turretAP = 16;
int boss2petalAP = 1;
int boss2topHP = 64;
int boss2topAP = 1;
			  	 // bar launcher
int boss5launchHP = 4;
int boss5barAP = 8;

int boss7HP	 = 40;	 // planet launcher
int boss7hatchHP	 = 16;
int boss7launcherHP = 8;

int boss8HP	 = 32;	 // washing machine 
int nucleusLaunchAP = 8;
int nucleusBeamLAP	 = 8;


int bossAturrHP = 12;		 
int bossAcupHP = 24;
int bossAAP = 16;

/*
int bossBairHP = 40	64;
int bossBspinHP = 30	50;
int bossBrobHP = 32	64;
int bossBAP = 16;
*/

int bossFlauncherAP = 10;
int bossFlauncherHP = 4;
int bossFlauncher2HP = 8;



int boss2_scale = 3;
int boss5_scale = 3;
int boss7_scale = 3;
int boss8_scale = 3;
int boss8_rotspeed = 1;
int boss8_circ = 1200;
int bossA_scale = 2;
int bossB_scale = 2;
int bossF_scale = 3;
int bossH_scale = 2;
int mybase_scale = 3;

 //-----------------------------------------------------------------------------
 // STATIC ENEMY.

int bu_scale = 2;
int bu_scale2 = 3;
int turretHP = 4;		 // D
int turretAP = 1;		 // D
int flowerHP = 4;		 // D
int flowerAP = 1;		 // D
int recItemHP = 1;
int coreHP = 8;
int coreAP = 4;


 //-----------------------------------------------------------------------------
 // PLAYER.

int playerW_HP = 5;	 // Wings HP/health/shield (Stock = 5)
//int playerB_HP = 40;	 // Player Body HP/health/shield (Stock = 40) (redef'd in sm64.h)
int playerW_AP = 3;
int playerB_AP = 3;	       
int playerB_boxsize = 10;

int playerW_boxsize = 5;
int TplayerW_x = 20;
int playerW_x = 33;
int playerW_y = 13;
int playerW_z = 0;
int playerB_z = 0;


int playerB_Ystop = -20;

int pBhardAP = 4;
int pBsoftAP = 2;
int pWhardAP = 1;
int pWsoftAP = 1;

int maxPspeed = 85;
int medPspeed = 65;
int minPspeed = 20;

int pexitbasespeed = 50;

int nullpship = 2;

// Player's ship flags.

// pshipflags
int psf_bodycoll = 1;
int psf_LWingcoll = 2;
int psf_Rwingcoll = 4;	
int psf_brkLWing = 8;
int psf_brkRwing = 16;	
int psf_noctrl = 32;
int psf_nofire = 64;
int psf_noYctrl = 128;

// pshipflags2
int psf2_doublaser = 1;
int psf2_wireship = 2;
int psf2_nospark = 4;
int psf2_turn180 = 8;
int psf2_forceboost = 0;
int psf2_boosting = 32;
int psf2_braking = 64;
int psf2_playerHP0 = 128;

//pshipflags3
int psf3_intunnel = 1;
int psf3_enginesnd = 2;	// 0/1 , off/on
int psf3_forcebrake = 0;
int psf3_nocollisions = 8;
int psf3_beamball = 16;

// zremove
int zremove = 0;

