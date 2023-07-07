// LCD1602 to Arduino Uno connection example

#include <LiquidCrystal.h>

#define UP_BUTTON 1
#define DOWN_BUTTON 0

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int menuPosition = 0;

void setup() {
  lcd.begin(16, 2);
  
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);        // Initialize serial communication
  menuPosition = 0;
}

void loop() {
  lcd.print( "Austeilen" );
  if( menuPosition == 0 )
  {
    lcd.setCursor( 15, 1 );
    lcd.print( " " );
  }
  else
  {
    lcd.setCursor( 15, 0 );
    lcd.print( " " );
  }

  lcd.setCursor( 15, menuPosition );
  lcd.print( "X" );
  lcd.setCursor(0, 1);
  lcd.print( "Ausschalten" );

  if( digitalRead(DOWN_BUTTON) == LOW )
  {
    /*lcd.setCursor( 15, 0 );
    lcd.print( " " );
    lcd.setCursor( 15, 1 );
    lcd.print( "X" );*/
    menuPosition = 1;
  }
  
  if( digitalRead(UP_BUTTON) == LOW )
  {
    menuPosition = 0;
  }

  lcd.setCursor( 0, 0 );
  delay( 100 );
}