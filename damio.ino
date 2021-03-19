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


void Deplacer (int medoc, int medoc_suivant, int repas, int repas_suivant, int jour, int jour_suivant) {
	// déplacement de de la plaque mobile pour les médicaments
	float deplacement_medoc[2] = { 
		(position_medoc[medoc_suivant *2] - position_medoc[medoc *2]),       // en x
		(position_medoc[medoc_suivant *2 +1] - position_medoc[medoc *2 +1])  // en y
	};

	// déplacement de de la plaque mobile pour les différents repas (sur l'axe x)
	float deplacement_repas = (position_repas[repas_suivant] - position_repas[repas]);

	// déplacement de de la plaque mobile pour les différents jours (sur l'axe y)
	float deplacement_jour = (position_jours[jour_suivant] - position_jours[jour]);

	float deplacement[2] = {  // déplacement total de la plaque mobile
		(deplacement_medoc[0] + deplacement_repas),  // déplacement total en x
		(deplacement_medoc[1] + deplacement_jour),   // déplacement total en y
	};

	// test:
	/* Serial.print("déplacement de medoc "); */
	/* Serial.print(medoc); */
	/* Serial.print(" vers "); */
	/* Serial.println(medoc_suivant); */

	/* Serial.print("x : "); */
	/* Serial.println(deplacement_medoc[0]); */
	/* Serial.print("y : "); */
	/* Serial.println(deplacement_medoc[1]); */

	/* Serial.print("déplacement de repas"); */
	/* Serial.print(repas); */
	/* Serial.print(" vers "); */
	/* Serial.println(repas_suivant); */
	/* Serial.print("x : "); */
	/* Serial.println(deplacement_repas); */

	/* Serial.print("déplacement de jour "); */
	/* Serial.print(jour); */
	/* Serial.print(" vers "); */
	/* Serial.println(jour_suivant); */
	/* Serial.print("y : "); */
	/* Serial.println(deplacement_jour); */

	/* Serial.print("déplacement en x: "); */
	/* Serial.println(deplacement[0]); */

	/* Serial.print("déplacement en y: "); */
	/* Serial.println(deplacement[1]); */

	/* Serial.println(" "); */
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
		// test de la fonction.
		//       medoc, repas, jour
		Deplacer(0, 0,  1, 1,  1, 0);
		Deplacer(2, 4,  2, 1,  4, 2);
		Deplacer(1, 8,  2, 0,  5, 6);
		Deplacer(5, 3,  1, 2,  0, 5);
		Deplacer(2, 0,  1, 0,  6, 2);

		/*
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
		// Serial.println("uuu");
		*/

		distribution = false;
	}

	der_e_suivant = e_suivant;
	der_e_distrib = e_distrib;
}
