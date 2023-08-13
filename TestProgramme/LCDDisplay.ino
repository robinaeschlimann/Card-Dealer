#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("LCD Test!");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(500);
  lcd.clear();
  delay(500);
}
