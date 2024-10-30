


unsigned long pulseCount = 0;
unsigned long startTime;
unsigned long duration = 100; // Timeframe duration in milliseconds
const int potPin = A0; // The pin where the potentiometer is connected
const int relayPin = 3; // The pin controlling the relay
long scaledPulseCount;
  long scaledPotValue;
bool ignitionOff = false;

void setup() {
  pinMode(2, INPUT);
  pinMode(relayPin, OUTPUT); // Initialize the relay pin as output
  digitalWrite(relayPin, LOW); // Ensure relay is off to start
  attachInterrupt(digitalPinToInterrupt(2), countPulse, RISING);
  startTime = millis();
  Serial.begin(9600);

}

void loop() {
 
  
      int potValue = analogRead(potPin);
  scaledPotValue = map(potValue, 0, 1023, 400, 6000);

    // Map the pulse count to the desired value range
    scaledPulseCount = map(pulseCount, 0, 100, 0, 10000);

    // Print the scaled pulse count and the potentiometer value
    Serial.println("Scaled pulse count: " + String(scaledPulseCount));
    Serial.println(scaledPotValue);
    Serial.println(ignitionOff);

    if (scaledPulseCount > scaledPotValue) {
      digitalWrite(relayPin, LOW);
      ignitionOff = true;
    } else if (ignitionOff) {
      digitalWrite(relayPin, HIGH); // Turn off relay
      delay(40);
      ignitionOff = false;
       pulseCount = 0;
       digitalWrite(relayPin, LOW);
    }
if ((millis() - startTime) >= duration) {
  startTime = millis();
  pulseCount = 0;
}


}

void countPulse() {
  pulseCount++;
}
