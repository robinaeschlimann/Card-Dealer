
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int buttonState0 = 0;  // variable for reading the pushbutton status
int buttonState1 = 0;  // variable for reading the pushbutton status
int buttonState2 = 0;  // variable for reading the pushbutton status
int buttonState3 = 0;  // variable for reading the pushbutton status

const int BUTTONPIN0 = 0;
const int BUTTONPIN1 = 1;
const int BUTTONPIN2 = 2;
const int BUTTONPIN3 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTONPIN0, INPUT);
  pinMode(BUTTONPIN1, INPUT);
  pinMode(BUTTONPIN2, INPUT);
  pinMode(BUTTONPIN3, INPUT);
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
    // read the state of the pushbutton value:
  buttonState0 = digitalRead(BUTTONPIN0);
  buttonState1 = digitalRead(BUTTONPIN1);
  buttonState2 = digitalRead(BUTTONPIN2);
  buttonState3 = digitalRead(BUTTONPIN3);

  // put your main code here, to run repeatedly:
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState0 == LOW ) {
    // turn LED on:
    lcd.print("0");
  }
  if (buttonState1 == LOW) {
    // turn LED on:
    lcd.print("1");
  }
  if (buttonState2 == LOW) {
    // turn LED on:
    lcd.print("2");
  }
  if (buttonState3 == LOW ) {
    // turn LED on:
    lcd.print("3");
  }

  delay(1000);
  lcd.clear();
}


