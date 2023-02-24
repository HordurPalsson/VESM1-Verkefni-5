// Librarys
#include "NewPing.h"
#include "Servo.h"

// Objects
Servo myservo;
Servo motor;
int motorPin = 12;
int stefna = 0;
bool movement = true;

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
// Segir til um hvada pinnar gera hvad
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define servoPin 11
#define motorPin 12

// Servo position
int angle = 0;

// Motor position
int motor_stefnur[] = { 0, 90, 180, 90 };
int motor_stefnu_fjoldi = 4;   // breytan geymir hversu margar stefnur eru í listanum
int motor_stefnu_teljari = 0;  // breytan heldur utan um í hvaða stefnu mótorinn á að benda

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  // Kveikir servoinum
  myservo.attach(servoPin);
  // motorinn
  motor.attach(motorPin); // segi servo tilvikinu hvaða pinna á að nota
  motor.write(motor_stefnur[motor_stefnu_teljari]); // í þessu tilfelli á mótorinn að byrja í 0°
}

void loop() {
  if(sonar.ping() > 10) {
    // uppfæra stefnu_teljara breytuna, modulus notað til að talan verði
    // aldrei hærri en fjöldi stefnanna sem eru í listanum
    motor_stefnu_teljari = (motor_stefnu_teljari + 1) % motor_stefnu_fjoldi;
    // veljum svo rétta stefnu úr listanum
    motor.write(motor_stefnur[motor_stefnu_teljari]);
  }

  
  if (sonar.ping_cm() > 10) {


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