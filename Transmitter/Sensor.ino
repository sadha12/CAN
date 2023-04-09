#define POTENTIAL_PIN A0
int potentialValue;

void initSensor() {
  pinMode(POTENTIAL_PIN, INPUT);
}

void sense(uint8_t* plainText) {
  potentialValue = analogRead(POTENTIAL_PIN);
  potentialValue = map(potentialValue, 0, 1023, 0, 255);
  *plainText = (uint8_t)potentialValue;
  Serial.print("Sensed data : " + String(*plainText));
}