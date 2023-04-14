#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // wait for Serial input
  while (!Serial.available()) {
    delay(100);
  }

  // read Serial input and print on LCD
  String input = Serial.readString();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(input);

  // print on Serial monitor for confirmation
  Serial.print("LCD display: ");
  Serial.println(input);
}
