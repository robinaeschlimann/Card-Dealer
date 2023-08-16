// LCD1602 to Arduino Uno connection example

#include <LiquidCrystal.h>
#include <Stepper.h>

#define DOWN_BUTTON 0
#define UP_BUTTON 1
#define START_BUTTON_RED A4
#define CONFIRM_BUTTON_GREEN 2

#define DC_MOTOR_PIN 3

#define X_POSITION 15
#define TEXT_START_POSITION 0
#define COUNT_POSITION 12

const int DC_MOTOR_SPEED = 15;

int maxSteps = 2048;
Stepper StepperMotor(maxSteps, 4, 6, 5, 7);

const int rs = 8, en = 9, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int menuPosition = 0;
int menuDept = 0;

int playerCount = 4;
int cardCount = 2;

bool editMode = false;

void setup() {
  lcd.begin(16, 2);

  StepperMotor.setSpeed(DC_MOTOR_SPEED);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(START_BUTTON_RED, INPUT_PULLUP);
  pinMode(CONFIRM_BUTTON_GREEN, INPUT_PULLUP);
  pinMode(DC_MOTOR_PIN, OUTPUT);
  digitalWrite(DC_MOTOR_PIN, HIGH);

  //pinMode(5, OUTPUT);

  Serial.begin(115200);  // Initialize serial communication
  menuPosition = 0;
}

void showMenu() {
  lcd.print("Anz Spieler:");
  lcd.setCursor(COUNT_POSITION, 0);
  lcd.print(playerCount);
  if (menuPosition == 0) {
    lcd.setCursor(X_POSITION, 1);
    lcd.print(" ");
  } else {
    lcd.setCursor(X_POSITION, 0);
    lcd.print(" ");
  }

  lcd.setCursor(X_POSITION, menuPosition);

  lcd.print("X");


  lcd.setCursor(TEXT_START_POSITION, 1);
  lcd.print("Anz Karten:");
  lcd.setCursor(COUNT_POSITION, 1);
  lcd.print(cardCount);

  if (digitalRead(CONFIRM_BUTTON_GREEN) == LOW) {
    if (menuPosition == 0) {
      playerCount = editCount(editMode, playerCount, 2, 10);
    } else if (menuPosition == 1) {
      cardCount = editCount(editMode, cardCount, 1, 15);
    }
  }

  // Don't switch menu position while a value is been edited
  if (!editMode) {
    switchMenuPosition();

    if (digitalRead(START_BUTTON_RED) == LOW) {
      turn();
    }
  }

  lcd.setCursor(0, 0);
  delay(100);
}

void loop() {
  showMenu();
  //dealCards();
  //turn();
}

void switchMenuPosition() {
  if (digitalRead(DOWN_BUTTON) == LOW) {
    menuPosition = 1;
  }

  if (digitalRead(UP_BUTTON) == LOW) {
    menuPosition = 0;
  }
}

int editCount(bool editMode, int count, int minValue, int maxValue) {

  if (!editMode && digitalRead(CONFIRM_BUTTON_GREEN) == LOW) {
    editMode = true;
    lcd.setCursor(X_POSITION, menuPosition);
    lcd.print("<");
  } else if (editMode && digitalRead(CONFIRM_BUTTON_GREEN) == LOW) {
    editMode = false;
    lcd.setCursor(X_POSITION, menuPosition);
    lcd.print("X");
  }

  delay(500);

  while (editMode) {

    if (digitalRead(DOWN_BUTTON) == LOW) {
      if (count > minValue) {
        count = count - 1;
      }
    }

    if (digitalRead(UP_BUTTON) == LOW) {
      if (count < maxValue) {
        count = count + 1;
      }
    }

    if (digitalRead(CONFIRM_BUTTON_GREEN) == LOW) {
      editMode = false;
    }

    lcd.setCursor(COUNT_POSITION + 1, menuPosition);
    lcd.print(" ");
    lcd.setCursor(COUNT_POSITION, menuPosition);
    lcd.print(count);
    delay(200);
  }

  return count;
}

/* void debug()
{
  lcd.clear();
lcd.print(button.onPressed());

delay(1000);
} */

void turn() {
  for (int i = 0; i < cardCount; i++) {
    for (int j = 0; j < playerCount - 1; j++) {
      //deal card
      dealCards();
      StepperMotor.step(maxSteps / playerCount);
      delay(500);
    }
    dealCards();
    StepperMotor.step(-maxSteps + (maxSteps / playerCount));
    delay(1000);
  }

  lcd.clear();
  lcd.print("Ausgabe beendet");
  delay(1000);
  lcd.clear();
}

void dealCards() {
  // LOW means running - HIGH means stop
  digitalWrite(DC_MOTOR_PIN, LOW);
  delay(1000);
  digitalWrite(DC_MOTOR_PIN, HIGH);
}