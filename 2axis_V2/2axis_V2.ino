// This code runs a 2-axis system of two stepper motors connected on linear rails

// Variables
  const int microsteps = 16;
  const int stepsPerRev = 200 * microsteps;

  const int x_dirPin = 3; //TODO actual pins
  const int x_stepPin = 2; //TODO actual pins
  const int x_potPin = A0; //TODO actual pins

  const int y_dirPin = 3; //TODO actual pins
  const int y_stepPin = 2; //TODO actual pins
  const int y_potPin = A0; //TODO actual pins

  int x_potVal;
  int y_potVal;
  bool x_StepOn = false;
  bool y_StepOn = false;

  //Loop Timing
  unsigned long x_stepPeriod; // delay between x steps, in ms
  unsigned long y_stepPeriod; // delay between y steps, in ms
  unsigned long startTime;
  unsigned long currentTime;

void setup(){
	pinMode(x_stepPin, OUTPUT);
	pinMode(x_dirPin, OUTPUT);
  pinMode(x_potPin, INPUT);
  pinMode(y_stepPin, OUTPUT);
	pinMode(y_dirPin, OUTPUT);
  pinMode(y_potPin, INPUT);

  Serial.begin(9600);

  // Get starting time
  startTime = micros(); //overflow after ~70 minutes runtime
}

void loop(){
  currentTime = micros();

  // X Stepper Timing
  if ((currentTime - startTime >= x_stepPeriod) && !(x_StepOn)){
    digitalWrite(x_stepPin, HIGH);
    x_StepOn = true;

  } else if (currentTime - startTime >= (2 * x_stepPeriod)){
    digitalWrite(x_stepPin, LOW);

    // recalc x period
      x_potVal = analogRead(x_potPin);
      x_stepPeriod = map(x_potVal, 0, 1023, -10, 10); // returns long

      if (x_stepPeriod < 0){
        digitalWrite(x_dirPin, LOW);
      } else if (x_stepPeriod > 0){
        digitalWrite(x_dirPin, HIGH);
      }
      
      if (x_stepPeriod != 0){
        // x_stepPeriod = abs(x_stepPeriod);
        x_stepPeriod = 1000 / (x_stepPeriod*x_stepPeriod);
      }

    x_StepOn = false;


  // Y Stepper Timing
  if ((currentTime - startTime >= y_stepPeriod) && !(y_StepOn)){
    digitalWrite(y_stepPin, HIGH);
    y_StepOn = true;

  } else if (currentTime - startTime >= (2 * y_stepPeriod)){
    digitalWrite(y_stepPin, LOW);

    // recalc y period
      y_potVal = analogRead(y_potPin);
      y_stepPeriod = map(y_potVal, 0, 1023, -10, 10); // returns long

      if (y_stepPeriod < 0){
        digitalWrite(y_dirPin, LOW);
      } else if (y_stepPeriod > 0){
        digitalWrite(y_dirPin, HIGH);
      }
      
      if (y_stepPeriod != 0){
        // y_stepPeriod = abs(y_stepPeriod);
        y_stepPeriod = 1000 / (y_stepPeriod*y_stepPeriod);
      }

    x_StepOn = false;

  // Serial.println(potVal);
  // delay(50);
}

unsigned long StepperTiming(unsigned long period, int stepPin, int dirPin, int potPin){
  //TODO
}

