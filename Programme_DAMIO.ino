#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);  // sets the pins used by the lcd screen

int next_prgm_pin = 8;
int start_pin = 9;
int stop_pin = 10;

void setup() {
  pinMode (next_prgm_pin, INPUT);
  pinMode (start_pin, INPUT);
  pinMode (stop_pin, INPUT);
  lcd.begin(16, 2);
  lcd.print(">o_/");
}

void loop() {
  // put your main code here, to run repeatedly:

}
