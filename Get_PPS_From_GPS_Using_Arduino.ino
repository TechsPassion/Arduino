const int ppsPin = 2; //PPS to Arduino Pin D2 and VCC + GND

//A "PPS pin" on a GPS module stands for "Pulse Per Second" pin, 
//which outputs a signal that generates a pulse exactly once every second, 
//essentially providing a highly accurate time reference for synchronizing other devices. 
//with the GPS receiver's internal clock.

volatile unsigned long ppsTimestamp = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(ppsPin, INPUT_PULLUP); // Enable internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(ppsPin), ppsHandler, RISING);
}

void loop() {
 
  Serial.println(ppsTimestamp);
  delay(1000); 
}

void ppsHandler() {
  ppsTimestamp = micros(); 
}
