// #include <array>
// #include <tuple>
// #include <iostream>
// #include <vector>
// #include <string>
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);  // sets the pins used by the lcd screen

int next_prgm_pin = 8;
int start_pin = 9;
int stop_pin = 10;

typedef std::tuple<string, int> prgm_tuple;
std::array<prgm_tuple, 4> prgm_array;
// typedef std::array<tuple<string, int>> tuple_lst;
// std::vector<tuple<string, int>> tuple_lst;
tuple_lst tl;
tl.push_back(tuple<string, int>(">o_/", 1));
tl.push_back(tuple<string, int>("||_(o.o)_//", 2));
tl.push_back(tuple<string, int>("bbbbbbbb", 3));
tl.push_back(tuple<string, int>("uuuu", 4));
// char *test_prgm_names[] = {">o_/", "||_(o.o)_//", "bbbbbbbb", "uuuu"};
int current_prgm = 0;
int total_nb_prgm = sizeof(test_prgm_names) / sizeof(test_prgm_names[0]);
int button_down = 0;
int last_button_state = LOW;
// we divide the size of the array by the size of the first ellement in order to have the number of ellement in the array.

void setup() {
  pinMode (next_prgm_pin, INPUT);
  pinMode (start_pin, INPUT);
  pinMode (stop_pin, INPUT);
  lcd.begin (16, 2);
  lcd.print ('>');
  // lcd.print (test_prgm_names[current_prgm]);
  lcd.print (get<0>(tl[current_prgm]));
  lcd.print (get<1>(tl[current_prgm]));
  lcd.setCursor (1, 1);
  lcd.print (get<0>(tl[(current_prgm + 1) % total_nb_prgm]));
  lcd.print (get<1>(tl[(current_prgm + 1) % total_nb_prgm]))
  // lcd.print (test_prgm_names[(current_prgm + 1) % total_nb_prgm]);
}

void loop() {
  button_down = digitalRead(next_prgm_pin);
  if (button_down != last_button_state) {
    if (button_down == HIGH) {
      last_button_state = HIGH;
      current_prgm = (current_prgm + 1) % total_nb_prgm;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print ('>');
      lcd.print (get<0>(tl[current_prgm]));
      lcd.print (get<1>(tl[current_prgm]));
      // lcd.print (test_prgm_names[current_prgm]);
      lcd.setCursor (1, 1);
      lcd.print (get<0>(tl[(current_prgm + 1) % total_nb_prgm]));
      lcd.print (get<1>(tl[(current_prgm + 1) % total_nb_prgm]))
      // lcd.print (test_prgm_names[(current_prgm + 1) % total_nb_prgm]);
    }
    last_button_state = button_down;
  }
}
