// This code runs a 2-axis system of two stepper motors connected on linear rails
// TODO I don't think delay approach will work; convert to timer approach. Delay approach will combine delay timing of x and y
// TODO create a repo

// Variables
  const int microsteps = 16;
  const int stepsPerRev = 200 * microsteps;

  const int x_dirPin = 3;
  const int x_stepPin = 2;
  const int x_potPin = A0;

  const int y_dirPin = 3;
  const int y_stepPin = 2;
  const int y_potPin = A0;

  int x_potVal;
  int x_stepDelay;
  int y_potVal;
  int y_stepDelay;

void setup()
{
	pinMode(x_stepPin, OUTPUT);
	pinMode(x_dirPin, OUTPUT);
  pinMode(x_potPin, INPUT);
  pinMode(y_stepPin, OUTPUT);
	pinMode(y_dirPin, OUTPUT);
  pinMode(y_potPin, INPUT);

  Serial.begin(9600);
}

void loop()
{
  // read x & y pots
  x_potVal = analogRead(x_potPin);
  y_potVal = analogRead(y_potPin);
  x_potVal = map(x_potVal, 0, 1023, -10, 10); // returns long
  y_potVal = map(x_potVal, 0, 1023, -10, 10); // returns long

  // move x step
  if (x_potVal < 0){
    digitalWrite(x_dirPin, LOW);
  } else if (x_potVal > 0){
    digitalWrite(x_dirPin, HIGH);
  }
  // x_potVal = abs(x_potVal);
  if (x_potVal != 0){
    x_stepDelay = 1000 / (x_potVal*x_potVal);
    digitalWrite(x_stepPin, HIGH);
    delayMicroseconds(x_stepDelay);
    digitalWrite(x_stepPin, LOW);
    delayMicroseconds(x_stepDelay);
  }

  // move y step
  if (y_potVal < 0){
    digitalWrite(y_dirPin, LOW);
  } else if (y_potVal > 0){
    digitalWrite(y_dirPin, HIGH);
  }
  //y_potVal = abs(y_potVal);
  if (y_potVal != 0){
    y_stepDelay = 1000 / (y_potVal*y_potVal);
    digitalWrite(y_stepPin, HIGH);
    delayMicroseconds(y_stepDelay);
    digitalWrite(y_stepPin, LOW);
    delayMicroseconds(y_stepDelay);
  }

  // Serial.println(potVal);
  // delay(50);
}
