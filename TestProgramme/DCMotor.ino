const int dcMotorPin = 6;

void setup()
{
  pinMode(dcMotorPin, OUTPUT);
}

void loop()
{
  digitalWrite(dcMotorPin, HIGH);
  delay(1000);
  digitalWrite(dcMotorPin, LOW);
  delay(1000);
}