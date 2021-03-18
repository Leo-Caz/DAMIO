#include "posologie_ete.h"
// #include "posologie_hiver.h"

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

#define bouton_distrib 2
#define bouton_suivant 4
#define affichage_controles "suivant | lancer"
#define largeur_ecran 16

int jour_choisi = 0;
int e_suivant = 0;
int e_distrib = 0;
int der_e_suivant = LOW;
int der_e_distrib = LOW;
bool distribution = false;


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
	pinMode(bouton_suivant, INPUT);
	pinMode(bouton_distrib, INPUT);
	lcd.begin(16, 2);
#ifdef LcdRgb
	lcd.setRGB(couleur_p, couleur_v, couleur_b);
#endif
	Affichage();
	Serial.begin(9600);
	Serial.println("damio");
}


void loop() {
	e_suivant = digitalRead(bouton_suivant);
	e_distrib = digitalRead(bouton_distrib);

	// On sélectionne le jours suivant
	if (e_suivant != der_e_suivant && e_suivant == HIGH) {
		jour_choisi = (jour_choisi +1) % NB_JOURS;
		Affichage();
	}

	// On lance le traitement
	else if (e_distrib != der_e_distrib && e_distrib == HIGH) {
		distribution = true;
	}
	
	// Distribution des médicaments
	if (distribution) {
		Serial.println("uuu");
		// Placer le pilulier à l'endroit par défaut.
		for (int repas = 0; repas < NB_PRISES; repas++) {
			// Décaller le pilulier sur la largeur pour positionner le bon repas.
			Serial.print("repas numéro : ");
			Serial.println(repas);
			for (int medoc = 0; medoc < NB_MEDICAMENTS; medoc++) {
				// Si (int)traitement[jour_choisi][repas][medoc] != 0:
				if ((int)traitement[jour_choisi][repas][medoc] != 0) {
					Serial.print(id_medicaments[medoc]);
					Serial.print(": ");
					Serial.println((int)traitement[jour_choisi][repas][medoc]);
					// On place le pilulier sous le distributeur du médicament
					// On fait vibrer le réservoir
					// On fait sortir le bon nombre de médicaments
					// Vérifier que les médicaments soit bien passé?
					// Arrêter de vibrer le réservoir

					// Tout le temps vérifier que le moteur ne soit pas bloqué
					// Afficher une barre de progression sur l'écran.
					// Afficher des messages sur l'écran en cas de problème
					// Décaler le pilulier avec un certain nombre de tours ou un système asseri en position?
					// Éviter de tout bloquer le système avec les boucles imbriqués.
				}
			}
			Serial.println(' ');
		}
		/* Serial.println("uuu"); */
		distribution = false;
	}

	der_e_suivant = e_suivant;
	der_e_distrib = e_distrib;
}
