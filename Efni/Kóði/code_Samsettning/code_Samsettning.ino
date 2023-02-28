// Libraries
#include "NewPing.h"
#include <tdelay.h>
#include <Servo.h>

// Objects
#define TRIGGER_PIN 9
#define ECHO_PIN 10

int distance = 20;

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


void setup() {
    Serial.begin(9600);
}

void loop() {
  if (sonar.ping_cm() < distance) {
      
    } else {
    
    }
}
