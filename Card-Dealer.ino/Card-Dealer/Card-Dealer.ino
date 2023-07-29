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
#define COUNT_POSITION 12

RBD::Button button(0, false);

int maxSteps = 2048;
Stepper Schrittmotor(maxSteps, 4, 6, 5, 7);

const int rs = 8, en = 9, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int menuPosition = 0;
int menuDept = 0;

int playerCount = 4;
int cardCount = 1;

bool editMode = false;

void setup() {
  lcd.begin(16, 2);

  Schrittmotor.setSpeed(10);

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
  lcd.setCursor( COUNT_POSITION, 0 );
  lcd.print( playerCount );
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
  
 
  lcd.setCursor(TEXT_START_POSITION, 1);
  lcd.print( "Anz Karten:" );
  lcd.setCursor( COUNT_POSITION, 1 );
  lcd.print( cardCount );

  if( digitalRead( CONFIRM_BUTTON ) == LOW )
  {
    if( menuPosition == 0 )
    {
      playerCount = editCount( editMode, playerCount, 2, 10 );
    }
    else if( menuPosition == 1 )
    {
      cardCount = editCount( editMode, cardCount, 1, 15 );
    }
  }

  // Don't switch menu position while a value is been edited
  if( !editMode )
  {
    if ( digitalRead(DOWN_BUTTON) == LOW )
    {
      menuPosition = 1;
    }

    if ( digitalRead(UP_BUTTON) == LOW)
    {
      menuPosition = 0;
    }
  }

  lcd.setCursor( 0, 0 );
  delay( 100 );
}

void loop() {
  //showMenu();
  //dealCard();
  turn();

}

int editCount( bool editMode, int count, int minValue, int maxValue )
{

  if( !editMode && digitalRead( CONFIRM_BUTTON ) == LOW )
  {
    editMode = true;
    lcd.setCursor( X_POSITION, menuPosition );
    lcd.print( "<" );
  }
  else if( editMode && digitalRead( CONFIRM_BUTTON ) == LOW )
  {
    editMode = false;
    lcd.setCursor( X_POSITION, menuPosition );
    lcd.print( "X" );
  }

  delay( 500 );

  while( editMode )
  {
    
    if( digitalRead( DOWN_BUTTON ) == LOW )
    {
      if( count > minValue )
      {
        count = count - 1;
      }
    }
    
    if( digitalRead(UP_BUTTON) == LOW )
    {
      if( count < maxValue )
      {
        count = count + 1;
      }
    }

    if( digitalRead( CONFIRM_BUTTON ) == LOW )
    {
      editMode = false;
    }
    
    lcd.setCursor( COUNT_POSITION + 1, menuPosition );
    lcd.print( " " );
    lcd.setCursor( COUNT_POSITION, menuPosition );
    lcd.print( count );
    delay( 200 );
  }

  return count;
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