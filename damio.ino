#include "posologie_ete.h"

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
#define controles_choix_trai  "defiler  choisir"
#define controles_lancer_trai "changer   lancer"
#define controles_annuler     "annuler  annuler"

int traitement_selectionne = 0;
const int taille_posologie = 56;
int etat_bouton_g = 0;
int etat_bouton_d = 0;
int dernier_etat_bouton_g = LOW;
int dernier_etat_bouton_d = LOW;
bool choix_traitement = false;  // true = choisir traitement, false = lancer traitement.

void setup() {
	pinMode(bouton_trait_suivant, INPUT);
	pinMode(bouton_confirmer, INPUT);
	lcd.begin(16, 2);
#ifdef LcdRgb
	lcd.setRGB(couleur_p, couleur_v, couleur_b);
#endif
	lcd.print(POSOLOGIE);
	lcd.setCursor(0, 1);
	lcd.print(controles_lancer_trai);
	// debug
	Serial.begin(9600);
	Serial.println("damio");
	for (int i = 0; i < NB_MEDICAMENTS; i++) {
		Serial.print(id_medicaments[i]);
		Serial.print(": ");
		Serial.println((int)traitement[j_lundi][p_midi][i]);
	}
}

void loop() {

	etat_bouton_g = digitalRead(bouton_trait_suivant);
	etat_bouton_d = digitalRead(bouton_confirmer);

	if (choix_traitement) {  // On choisi le traitement.
		if (etat_bouton_d != dernier_etat_bouton_d && etat_bouton_d == HIGH) {
			choix_traitement = false;
			lcd.clear();
			lcd.setCursor (0, 0);
			lcd.print(POSOLOGIE);
			lcd.setCursor(0, 1);
			lcd.print(controles_lancer_trai);
		}
	}

	else {  // On confirme le lancement du traitement.
		if (etat_bouton_g != dernier_etat_bouton_g && etat_bouton_g == HIGH) {
			choix_traitement = true;
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print(POSOLOGIE);
			lcd.setCursor(0, 1);
			lcd.print(controles_choix_trai);
		}
	}

	dernier_etat_bouton_g = etat_bouton_g;
	dernier_etat_bouton_d = etat_bouton_d;
}
