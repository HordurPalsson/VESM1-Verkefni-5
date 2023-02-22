// Include NewPing Library
#include "NewPing.h"

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 9
#define ECHO_PIN 10

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
	Serial.begin(9600);
}

void loop() {
	// Serial.print(sonar.ping_cm());
	// Serial.println(" cm");
  if (sonar.ping_cm() > 100)  {
    Serial.print("OFF = ");
  } else {
    Serial.print("ON = ");
  }
  delay(625);
}