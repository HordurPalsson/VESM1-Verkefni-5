// Include NewPing Library
#include "NewPing.h"
#include "Servo.h"
#include "tdelay.h"

// Servo Object
Servo myservo;

Servo motor;
int motorPin = 12;
int stefna = 0;
bool movement = true;

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
  // motorinn
  motor.attach(motorPin);
  motor.write(stefna);
}

void loop() {
    if (sonar.ping_cm() > 10) {
      if (movement == true) {
        stefna++;  // jafngildir stefna += 1 og stefna = stefna + 1
      } else {     // mótorinn er að hreyfast til hægri
        stefna--;  // jafngildir stefna -= 1 og stefna = stefna - 1
      }
      if (stefna == 0 || stefna == 180) {  // ef mótirnn er kominn út á enda, víxla áttunum
        movement = !movement;
      }
      motor.write(stefna);

    if (sonar.ping_cm() > 20) {
      Serial.print("OFF");
      //Controls Skeleton
      //ArduinoFFT potentionally could automate this
      myservo.write(120);
      myservo.write(30);
      myservo.write(0);
    } else {
      Serial.print("ON");
      myservo.write(0);
    }
    delay(625);
  }
}