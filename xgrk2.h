/*
 {* xgrk - Greek keyboard support for X
 {*
 {* (c) Spiros Ioannou 1999
 {*
 {* sivann@softlab.ece.ntua.gr
 {*/


/*
 {* keycodes in here don't matter, they are recalculated 
 {*
 {* Nothing needs to be changed in this file 
 {*/

#define XK_MISCELLANY
#define XK_GREEK
#include <X11/keysymdef.h>

#define DUMMY1 XK_F30
#define DUMMY2 XK_F31

/*
#define DUMMY1 XK_VoidSymbol
#define DUMMY2 XK_VoidSymbol
*/

/*keycode,l_case,u_case (greek) */
KeySym greek_plain[27][3] =
{
 { 0, XK_Greek_alpha, XK_Greek_ALPHA}, //Alpha Alpha_Kefalaio
 { 0, XK_Greek_beta, XK_Greek_BETA}, //Beta
 { 0, XK_Greek_gamma, XK_Greek_GAMMA}, //Gamma
 { 0, XK_Greek_delta, XK_Greek_DELTA}, //Delta
 { 0, XK_Greek_epsilon, XK_Greek_EPSILON}, //Epsilon
 { 0, XK_Greek_zeta, XK_Greek_ZETA}, //Zita
 { 0, XK_Greek_eta, XK_Greek_ETA}, //Ita
 { 0, XK_Greek_theta, XK_Greek_THETA}, //Theta
 { 0, XK_Greek_iota, XK_Greek_IOTA}, //Iota
 { 0, XK_Greek_kappa, XK_Greek_KAPPA}, //Kappa

 { 0, XK_Greek_lamda, XK_Greek_LAMDA}, //Lambda
 { 0, XK_Greek_mu, XK_Greek_MU}, //Mi
 { 0, XK_Greek_nu, XK_Greek_NU}, //Ni
 { 0, XK_Greek_xi, XK_Greek_XI}, //Ksi
 { 0, XK_Greek_omicron, XK_Greek_OMICRON}, //Omicron
 { 0, XK_Greek_pi, XK_Greek_PI}, //Pi
 { 0, XK_Greek_rho, XK_Greek_RHO}, //Rho
 { 0, XK_Greek_finalsmallsigma, XK_Greek_SIGMA}, //Sigma_teliko Ano Teleia
 { 0, XK_Greek_sigma, XK_Greek_SIGMA}, //Sigma
 { 0, XK_Greek_tau, XK_Greek_TAU}, //Taf

 { 0, XK_Greek_upsilon, XK_Greek_UPSILON}, //Ypsilon
 { 0, XK_Greek_phi, XK_Greek_PHI}, //Phi
 { 0, XK_Greek_chi, XK_Greek_CHI}, //Hi
 { 0, XK_Greek_psi, XK_Greek_PSI}, //Psi
 { 0, XK_Greek_omega, XK_Greek_OMEGA}, //Omega
 { 0, 59, 58},   //; :
 { 0, DUMMY1, DUMMY2},
};

/*keycode,l_case,u_case (greek accented) */
KeySym greek_accent[27][3] =
{
 { 0, XK_Greek_alphaaccent, XK_Greek_ALPHAaccent}, //Alpha Alpha_Kefalaio
 { 0, XK_Greek_beta, XK_Greek_BETA}, //Beta
 { 0, XK_Greek_gamma, XK_Greek_GAMMA}, //Gamma
 { 0, XK_Greek_delta, XK_Greek_DELTA}, //Delta
 { 0, XK_Greek_epsilonaccent, XK_Greek_EPSILONaccent}, //Epsilon
 { 0, XK_Greek_zeta, XK_Greek_ZETA}, //Zita
 { 0, XK_Greek_etaaccent, XK_Greek_ETAaccent}, //Ita
 { 0, XK_Greek_theta, XK_Greek_THETA}, //Theta
 { 0, XK_Greek_iotaaccent, XK_Greek_IOTAaccent}, //Iota
 { 0, XK_Greek_kappa, XK_Greek_KAPPA}, //Kappa

 { 0, XK_Greek_lamda, XK_Greek_LAMDA}, //Lambda
 { 0, XK_Greek_mu, XK_Greek_MU}, //Mi
 { 0, XK_Greek_nu, XK_Greek_NU}, //Ni
 { 0, XK_Greek_xi, XK_Greek_XI}, //Ksi
 { 0, XK_Greek_omicronaccent, XK_Greek_OMICRONaccent},
 { 0, XK_Greek_pi, XK_Greek_PI}, //Pi
 { 0, XK_Greek_rho, XK_Greek_RHO}, //Rho
 { 0, XK_Greek_finalsmallsigma, XK_Greek_SIGMA}, //Sigma_teliko Ano Teleia
 { 0, XK_Greek_sigma, XK_Greek_SIGMA}, //Sigma
 { 0, XK_Greek_tau, XK_Greek_TAU}, //Taf

 { 0, XK_Greek_upsilonaccent, XK_Greek_UPSILONaccent}, //Ypsilon
 { 0, XK_Greek_phi, XK_Greek_PHI}, //Phi
 { 0, XK_Greek_chi, XK_Greek_CHI}, //Hi
 { 0, XK_Greek_psi, XK_Greek_PSI}, //Psi
 { 0, XK_Greek_omegaaccent, XK_Greek_OMEGAaccent}, //Omega
 { 0, 59, 58},
 { 0, DUMMY1, DUMMY2},
};

KeySym greek_diaeresis[27][3] =
{
/*keycode,l_case,u_case (greek diaeresis) */
 { 0, XK_Greek_alpha, XK_Greek_ALPHA}, //Alpha Alpha_Kefalaio
 { 0, XK_Greek_beta, XK_Greek_BETA}, //Beta
 { 0, XK_Greek_gamma, XK_Greek_GAMMA}, //Gamma
 { 0, XK_Greek_delta, XK_Greek_DELTA}, //Delta
 { 0, XK_Greek_epsilon, XK_Greek_EPSILON}, //Epsilon
 { 0, XK_Greek_zeta, XK_Greek_ZETA}, //Zita
 { 0, XK_Greek_eta, XK_Greek_ETA}, //Ita
 { 0, XK_Greek_theta, XK_Greek_THETA}, //Theta
 { 0, XK_Greek_iotadieresis, XK_Greek_IOTAdiaeresis}, //Iota
 { 0, XK_Greek_kappa, XK_Greek_KAPPA}, //Kappa

 { 0, XK_Greek_lamda, XK_Greek_LAMDA}, //Lambda
 { 0, XK_Greek_mu, XK_Greek_MU}, //Mi
 { 0, XK_Greek_nu, XK_Greek_NU}, //Ni
 { 0, XK_Greek_xi, XK_Greek_XI}, //Ksi
 { 0, XK_Greek_omicron, XK_Greek_OMICRON}, //Omicron
 { 0, XK_Greek_pi, XK_Greek_PI}, //Pi
 { 0, XK_Greek_rho, XK_Greek_RHO}, //Rho
 { 0, XK_Greek_finalsmallsigma, XK_Greek_SIGMA}, //Sigma_teliko Ano Teleia
 { 0, XK_Greek_sigma, XK_Greek_SIGMA}, //Sigma
 { 0, XK_Greek_tau, XK_Greek_TAU}, //Taf

 { 0, XK_Greek_upsilondieresis, XK_Greek_UPSILONdieresis}, //Ypsilon
 { 0, XK_Greek_phi, XK_Greek_PHI}, //Phi
 { 0, XK_Greek_chi, XK_Greek_CHI}, //Hi
 { 0, XK_Greek_psi, XK_Greek_PSI}, //Psi
 { 0, XK_Greek_omega, XK_Greek_OMEGA}, //Omega
 { 0, 59, 58},
 { 0, DUMMY1, DUMMY2},
};

KeySym greek_diaeresis_accent[27][3] =
{
/*keycode,l_case,u_case (greek diaeresis+accent) */
 { 0, XK_Greek_alpha, XK_Greek_ALPHA}, //Alpha Alpha_Kefalaio
 { 0, XK_Greek_beta, XK_Greek_BETA}, //Beta
 { 0, XK_Greek_gamma, XK_Greek_GAMMA}, //Gamma
 { 0, XK_Greek_delta, XK_Greek_DELTA}, //Delta
 { 0, XK_Greek_epsilon, XK_Greek_EPSILON}, //Epsilon
 { 0, XK_Greek_zeta, XK_Greek_ZETA}, //Zita
 { 0, XK_Greek_eta, XK_Greek_ETA}, //Ita
 { 0, XK_Greek_theta, XK_Greek_THETA}, //Theta
 { 0, XK_Greek_iotaaccentdieresis, XK_Greek_IOTAaccent}, //Iota
 { 0, XK_Greek_kappa, XK_Greek_KAPPA}, //Kappa

 { 0, XK_Greek_lamda, XK_Greek_LAMDA}, //Lambda
 { 0, XK_Greek_mu, XK_Greek_MU}, //Mi
 { 0, XK_Greek_nu, XK_Greek_NU}, //Ni
 { 0, XK_Greek_xi, XK_Greek_XI}, //Ksi
 { 0, XK_Greek_omicron, XK_Greek_OMICRON}, //Omicron
 { 0, XK_Greek_pi, XK_Greek_PI}, //Pi
 { 0, XK_Greek_rho, XK_Greek_RHO}, //Rho
 { 0, XK_Greek_finalsmallsigma, XK_Greek_SIGMA}, //Sigma_teliko Ano Teleia
 { 0, XK_Greek_sigma, XK_Greek_SIGMA}, //Sigma
 { 0, XK_Greek_tau, XK_Greek_TAU}, //Taf

 { 0, XK_Greek_upsilonaccentdieresis, XK_Greek_UPSILONaccent}, //Ypsilon
 { 0, XK_Greek_phi, XK_Greek_PHI}, //Phi
 { 0, XK_Greek_chi, XK_Greek_CHI}, //Hi
 { 0, XK_Greek_psi, XK_Greek_PSI}, //Psi
 { 0, XK_Greek_omega, XK_Greek_OMEGA}, //Omega
 { 0, 59, 58},
 { 0, DUMMY1, DUMMY2},
};

