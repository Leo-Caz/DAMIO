#include "posologie_ete.h"
/* #include "posologie_hiver.h" */

// capteur i2c
#include <Wire.h>

// ecran LCD: LiquideCrystal ou Grove RGB LCD
#if 0
#define LiquidCristal
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);  // sets the pins used by the lcd screen
#else
#include "rgb_lcd.h"
rgb_lcd lcd;
#endif

int couleur_p = 220;
int couleur_v = 220;
int couleur_b = 220;

#define bouton_confirmer 2
#define bouton_trait_suivant 4
/* #define ctrl_choix_jour "suivant  choisir" */
/* #define ctrl_confirmer   "changer   lancer" */
#define affichage_controles "suivant | lancer"
#define largeur_ecran 16

int traitement_selectionne = 0;
int jour_choisi = 0;
/* const int taille_posologie = 56; */
int etat_bouton_g = 0;
int etat_bouton_d = 0;
int dernier_etat_bouton_g = LOW;
int dernier_etat_bouton_d = LOW;
/* bool choix_jour = false;  // true = choisir traitement, false = lancer traitement. */

void Affichage() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(nom_jours[jour_choisi]);
	lcd.setCursor(largeur_ecran - TAILLE_NOM_POSOLOGIE, 0);
	lcd.print(POSOLOGIE);
	lcd.setCursor(0, 1);
	lcd.print(affichage_controles);
}

void setup() {
	pinMode(bouton_trait_suivant, INPUT);
	pinMode(bouton_confirmer, INPUT);
	lcd.begin(16, 2);
#ifdef LcdRgb
	lcd.setRGB(couleur_p, couleur_v, couleur_b);
#endif

	Affichage();
	/* lcd.setCursor(0, 0); */
	/* lcd.print(POSOLOGIE); */
	/* lcd.setCursor(0, 1); */
	/* lcd.print(affichage_controles); */

	// debug
	/* Serial.begin(9600); */
	/* Serial.println("damio"); */
	/* for (int i = 0; i < NB_MEDICAMENTS; i++) { */
	/* 	Serial.print(id_medicaments[i]); */
	/* 	Serial.print(": "); */
	/* 	Serial.println((int)traitement[j_lundi][p_midi][i]); */
	/* } */
}

void loop() {
	etat_bouton_g = digitalRead(bouton_trait_suivant);
	etat_bouton_d = digitalRead(bouton_confirmer);

	// On sélectionne le cours suivant
	if (etat_bouton_g != dernier_etat_bouton_g && etat_bouton_g == HIGH) {
		jour_choisi = (jour_choisi +1) % NB_JOURS;
		Affichage();
		/* lcd.clear(); */
		/* lcd.setCursor(0, 0); */
		/* lcd.print(nom_jours[jour_choisi]); */
		/* lcd.setCursor(0, 1); */
		/* lcd.print(affichage_controles); */
	}

	// On lance le traitement
	if (etat_bouton_d != dernier_etat_bouton_d && etat_bouton_d == HIGH) {
		Serial.begin(9600);
		Serial.println("damio");
		for (int repas = 0; repas < NB_PRISES; repas++) {
			Serial.print("repas numéro : ");
			Serial.println(repas);
			for (int medoc = 0; medoc < NB_MEDICAMENTS; medoc++) {
				Serial.print(id_medicaments[medoc]);
				Serial.print(": ");
				Serial.println((int)traitement[jour_choisi][repas][medoc]);
			}
		}
	}

	/* if (choix_jour) {  // On choisi le jour. */
	/* 	if (etat_bouton_g != dernier_etat_bouton_g && etat_bouton_g == HIGH) { */
	/* 		jour_choisi = (jour_choisi +1) % NB_JOURS; */
	/* 		lcd.clear(); */
	/* 		lcd.setCursor(0, 0); */
	/* 		lcd.print(nom_jours[jour_choisi]); */
	/* 		lcd.setCursor(0, 1); */
	/* 		lcd.print(ctrl_choix_jour); */
	/* 	} */

	/* 	// on confirme le jour */
	/* 	if (etat_bouton_d != dernier_etat_bouton_d && etat_bouton_d == HIGH) { */
	/* 		choix_jour = false; */
	/* 		lcd.clear(); */
	/* 		lcd.setCursor (0, 0); */
	/* 		lcd.print(POSOLOGIE); */
	/* 		lcd.setCursor(0, 1); */
	/* 		lcd.print(ctrl_confirmer); */
	/* 	} */
	/* } */

	/* else {  // Le jour à été sélectionné */
	/* 	// On confirme le traitement */
	/* 	if (etat_bouton_d != dernier_etat_bouton_d && etat_bouton_d == HIGH) { */
	/* 		Serial.begin(9600); */
	/* 		Serial.println("damio"); */
	/* 		for (int repas = 0; repas < NB_PRISES; repas++) { */
	/* 			Serial.print("repas numéro : "); */
	/* 			Serial.println(repas); */
	/* 			for (int medoc = 0; medoc < NB_MEDICAMENTS; medoc++) { */
	/* 				Serial.print(id_medicaments[medoc]); */
	/* 				Serial.print(": "); */
	/* 				Serial.println((int)traitement[jour_choisi][repas][medoc]); */
	/* 			} */
	/* 		} */
	/* 	} */

	/* 	// On change de jour */
	/* 	if (etat_bouton_g != dernier_etat_bouton_g && etat_bouton_g == HIGH) { */
	/* 		choix_jour = true; */
	/* 		lcd.clear(); */
	/* 		lcd.setCursor(0, 0); */
	/* 		lcd.print(nom_jours[jour_choisi]); */
	/* 		lcd.setCursor(0, 1); */
	/* 		lcd.print(ctrl_choix_jour); */
	/* 	} */
	/* } */

	dernier_etat_bouton_g = etat_bouton_g;
	dernier_etat_bouton_d = etat_bouton_d;
}
