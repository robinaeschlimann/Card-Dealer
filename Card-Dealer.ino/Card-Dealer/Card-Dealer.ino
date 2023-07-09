// LCD1602 to Arduino Uno connection example

#include <LiquidCrystal.h>

#define DOWN_BUTTON 0
#define UP_BUTTON 1
#define BACK_BUTTON 2
#define CONFIRM_BUTTON 3

#define X_POSITION 15
#define TEXT_START_POSITION 0

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int menuPosition = 0;
int menuDept = 0;

void setup() {
  lcd.begin(16, 2);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  pinMode(CONFIRM_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);        // Initialize serial communication
  menuPosition = 0;
}

void showMenu() {
  lcd.print( "Austeilen" );
  if ( menuPosition == 0 )
  {
    lcd.setCursor( X_POSITION, 1);
    lcd.print( " " );
  }
  else
  {
    lcd.setCursor( X_POSITION, 0);
    lcd.print( " " );
  }

  lcd.setCursor( X_POSITION, menuPosition );
  lcd.print( "X" );
  lcd.setCursor(0, 1);
  lcd.print( "Ausschalten" );

  if ( digitalRead(DOWN_BUTTON) == LOW )
  {
    menuPosition = 1;
  }

  if ( digitalRead(UP_BUTTON) == LOW)
  {
    menuPosition = 0;
  }


  if ( digitalRead(CONFIRM_BUTTON) == LOW)
  {
    menuDept = 1;
    lcd.clear();
  }

  lcd.setCursor( 0, 0 );
  delay( 100 );
}

void newGame() {
  // Start Cursor Position
  int cursorPosition = 0;


  lcd.setCursor(TEXT_START_POSITION, 0);
  lcd.print("Anz Spieler");

  lcd.setCursor(TEXT_START_POSITION, 1);
  lcd.print("Anz Karten");

  lcd.setCursor(TEXT_START_POSITION, 2);
  lcd.print("Anz Karten");

  // Switch back to main menu
  if ( digitalRead(BACK_BUTTON) == LOW)
  {
    menuDept = 0;
    lcd.clear();
  }

  lcd.setCursor( 0, 0 );
  delay( 100 );
}

void loop() {
  
  switch (menuDept) {
    case 0:
      showMenu();
      break;
    case 1:
      newGame();
      break;
  }
}