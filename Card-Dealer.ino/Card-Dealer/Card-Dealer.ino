// LCD1602 to Arduino Uno connection example

#include <LiquidCrystal.h>
#include <RBD_Button.h>
#include <Stepper.h>

#define DOWN_BUTTON 1
#define UP_BUTTON 0
#define BACK_BUTTON 2
#define CONFIRM_BUTTON 3

#define X_POSITION 15
#define TEXT_START_POSITION 0

RBD::Button button(0, false);

int maxSteps = 2048;
Stepper Schrittmotor(maxSteps, 3, 5, 4, 6);

const int rs = 8, en = 9, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int menuPosition = 0;
int menuDept = 0;

int playerCount = 4;
int cardCount = 1;

void setup() {
  lcd.begin(16, 2);

  Schrittmotor.setSpeed(3);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  pinMode(CONFIRM_BUTTON, INPUT_PULLUP);
  pinMode(5, OUTPUT);

  Serial.begin(115200);        // Initialize serial communication
  menuPosition = 0;
}

void showMenu() {
  lcd.print( "Anz Spieler:" );
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
  lcd.print( "Anz Karten" );

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

void loop() {
  //showMenu();
  //turn();
  dealCard();

}

void debug()
{
  lcd.clear();
lcd.print(button.onPressed());

delay(1000);
}

void turn()
{
  for( int i = 0; i < cardCount; i++ )
  {
    for( int j = 0; j < playerCount-1; j++ )
    {
      //deal card
      Schrittmotor.step(maxSteps/playerCount);
      delay(500);
    }
    Schrittmotor.step(-maxSteps + (maxSteps/playerCount));
    delay(1000);
  }
}

void dealCard()
{
  analogWrite( 5, 255);
}