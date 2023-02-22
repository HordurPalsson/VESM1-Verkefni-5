// Include NewPing Library
#include "NewPing.h"
#include "Servo.h"

// Servo Object
Servo myservo;

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define servoPin 11

// Servo position
int angle = 0;


// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
	Serial.begin(9600);
  // Kveikir servoinum
  myservo.attach(servoPin);
}

void loop() {
  if (sonar.ping_cm() > 40)  {
    Serial.print("OFF");
    //Controls Skeleton
    myservo.write(120);
    delay(300);
    myservo.write(30);
    delay(150);
    myservo.write(0);
    delay(250);
  } else {
    Serial.print("ON");
        myservo.write(0);
  }
  delay(625);
}