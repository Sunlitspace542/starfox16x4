/*************************************************************************\
*                                                                         *
*                               Star Fox                                  *
*                              -----------                                *
*                                                                         *
*                          Nintendo 64 version.                           *
*                                                                         *
*                                                                         *
*                           Emerald Softworks.      		              *
*                                                                         *
*_________________________________________________________________________*
*                                                                         *
*  File: pstrats.inc.c                                                    *
*_________________________________________________________________________*
*                                                                         *
*  Descr: PLAYER'S STRATEGIES.                                            *
*                                                                         *
\*************************************************************************/

// Initial Strategy.
void s_player_Istrat(void) {

}

/*
player_Istrat
	s_start_strat
	s_jsr		playermove_init
	s_jsl		playercred_Istrat
	s_clr_alsflag	x,invisible
	s_clr_alsflag	x,colldisable
	stz	slowstars
	s_end_strat
*/

/*
playermove_init
	a8
	lda	#1
	sta.l	m_particlesON
	sta.l	m_particlesON+1
	lda	#viewtype_norm
	sta	viewtype
	stx	viewpt
	stx	playpt
	stx	viewtoobj
	stx	internalPLAYPT

	s_set_var		W,viewdist,#outviewdist
	s_set_var		W,outdist,#outviewdist

	s_setnoremove_behind	x

	s_set_aldata	x,#-1,#8
	s_set_alsflag	x,shadow
	s_set_var	W,plrotx,#0
	s_set_var	W,plroty,#0
	s_set_var	W,plrotz,#0
	s_set_var	B,slimecount,#0
	
	s_set_var	B,pstratflags,#0

	s_set_var		W,player_turnrot,#0
	s_set_var		B,player_ztilt,#0
	s_set_var		W,player_zshake,#0
	s_set_var		B,player_zstratadd,#0
	s_set_var		B,player_rollZvel,#0
	s_set_var		B,player_rollZoff,#0

	s_set_var		B,pnumhits,#0
	s_set_var		B,numplasers,#0

	s_set_var		B,specialdelay,#1

	s_set_var		W,pviewposz,#0
	s_set_var		B,playerdieYrotspeed,#128

	s_set_var		W,pviewvelz,#medpspeed
	s_set_var		B,player_tospeed,#medpspeed
	s_set_var		B,player_medspeed,#medpspeed
	s_set_var		W,playervelZ,#medpspeed

	s_set_var		B,boostZoff,#-30

	s_set_var		B,nomaxbg2Yscroll,#0

	stz	fadetored

	jsr	setcurrpshape
	
	s_and_var		B,pshipflags3,#~(psf3_intunnel!psf3_forcebrake!psf3_nocollisions)
	s_or_var		B,pshipflags3,#psf3_enginesnd

	rts
*/
