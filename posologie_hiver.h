#include "posologie.h"
#define POSOLOGIE "traitement hiver"

enum {
	m_A313,
	m_Alvityl,
	m_Ergyphillus,
	m_Eurobiol,
	m_Gelule_Vide,
	m_NaCl,
	m_Omeprazole,
	m_Orkambi,
	m_Toco,
	m_Ursolvan,
	m_Zinc,
	m_Zithromax,
	NB_MEDICAMENTS
};

const String id_medicaments[NB_MEDICAMENTS] = {
	[m_A313]        = "Vitamine A 313",
	[m_Alvityl]     = "Alvityl",
	[m_Ergyphillus] = "Ergyphillus",
	[m_Eurobiol]    = "Eurobiol",
	[m_Gelule_Vide] = "Gelule Vide",
	[m_NaCl]        = "NaCl",
	[m_Omeprazole]  = "Omeprazole",
	[m_Orkambi]     = "Orkambi",
	[m_Toco]        = "Toco",
	[m_Ursolvan]    = "Ursolvan",
	[m_Zinc]        = "Zinc",
	[m_Zithromax]   = "Zithromax",
};

/* pour modele
const char zero[NB_MEDICAMENTS] = {
	[m_A313]        = 0,
	[m_Alvityl]     = 0,
	[m_Ergyphillus] = 0,
	[m_Eurobiol]    = 0,
	[m_Gelule_Vide] = 0,
	[m_NaCl]        = 0,
	[m_Omeprazole]  = 0,
	[m_Orkambi]     = 0,
	[m_Toco]        = 0,
	[m_Ursolvan]    = 0,
	[m_Zinc]        = 0,
	[m_Zithromax]   = 0,
};
*/

const char matin1[NB_MEDICAMENTS] = {
	[m_A313]        = 1,
	[m_Alvityl]     = 0,
	[m_Ergyphillus] = 2,
	[m_Eurobiol]    = 3,
	[m_Gelule_Vide] = 0,
	[m_NaCl]        = 2,
	[m_Omeprazole]  = 0,
	[m_Orkambi]     = 2,
	[m_Toco]        = 0,
	[m_Ursolvan]    = 2,
	[m_Zinc]        = 2,
	[m_Zithromax]   = 0,
};

const char matin2[NB_MEDICAMENTS] = { // idem matin1 sans A313
	[m_A313]        = 0,
	[m_Alvityl]     = 0,
	[m_Ergyphillus] = 2,
	[m_Eurobiol]    = 3,
	[m_Gelule_Vide] = 0,
	[m_NaCl]        = 2,
	[m_Omeprazole]  = 0,
	[m_Orkambi]     = 2,
	[m_Toco]        = 0,
	[m_Ursolvan]    = 2,
	[m_Zinc]        = 2,
	[m_Zithromax]   = 0,
};

const char midi1[NB_MEDICAMENTS] = {
	[m_A313]        = 0,
	[m_Alvityl]     = 1,
	[m_Ergyphillus] = 0,
	[m_Eurobiol]    = 3,
	[m_Gelule_Vide] = 0,
	[m_NaCl]        = 2,
	[m_Omeprazole]  = 2,
	[m_Orkambi]     = 0,
	[m_Toco]        = 1,
	[m_Ursolvan]    = 0,
	[m_Zinc]        = 0,
	[m_Zithromax]   = 1,
};

const char midi2[NB_MEDICAMENTS] = { // idem midi1 sans Zithromax
	[m_A313]        = 0,
	[m_Alvityl]     = 1,
	[m_Ergyphillus] = 0,
	[m_Eurobiol]    = 3,
	[m_Gelule_Vide] = 0,
	[m_NaCl]        = 2,
	[m_Omeprazole]  = 2,
	[m_Orkambi]     = 0,
	[m_Toco]        = 1,
	[m_Ursolvan]    = 0,
	[m_Zinc]        = 0,
	[m_Zithromax]   = 0,
};

const char midi3[NB_MEDICAMENTS] = { // idem midi2 avec 2 gélules vides
	[m_A313]        = 0,
	[m_Alvityl]     = 1,
	[m_Ergyphillus] = 0,
	[m_Eurobiol]    = 3,
	[m_Gelule_Vide] = 2,
	[m_NaCl]        = 2,
	[m_Omeprazole]  = 2,
	[m_Orkambi]     = 0,
	[m_Toco]        = 1,
	[m_Ursolvan]    = 0,
	[m_Zinc]        = 0,
	[m_Zithromax]   = 0,
};

const char soir1[NB_MEDICAMENTS] = {
	[m_A313]        = 0,
	[m_Alvityl]     = 0,
	[m_Ergyphillus] = 0,
	[m_Eurobiol]    = 3,
	[m_Gelule_Vide] = 0,
	[m_NaCl]        = 2,
	[m_Omeprazole]  = 0,
	[m_Orkambi]     = 2,
	[m_Toco]        = 0,
	[m_Ursolvan]    = 2,
	[m_Zinc]        = 0,
	[m_Zithromax]   = 0,
};

const char * traitement[NB_JOURS][NB_PRISES] = {
	[j_lundi] = {
		[p_matin] = matin1,
		[p_midi]  = midi1,
		[p_soir]  = soir1,
	},
	[j_mardi] = {
		[p_matin] = matin2,
		[p_midi]  = midi2,
		[p_soir]  = soir1,
	},
	[j_mercredi] = {
		[p_matin] = matin1,
		[p_midi]  = midi1,
		[p_soir]  = soir1,
	},
	[j_jeudi] = {
		[p_matin] = matin2,
		[p_midi]  = midi2,
		[p_soir]  = soir1,
	},
	[j_vendredi] = {
		[p_matin] = matin1,
		[p_midi]  = midi1,
		[p_soir]  = soir1,
	},
	[j_samedi] = {
		[p_matin] = matin2,
		[p_midi]  = midi2,
		[p_soir]  = soir1,
	},
	[j_dimanche] = {
		[p_matin] = matin2,
		[p_midi]  = midi3,
		[p_soir]  = soir1,
	},
};
