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
// Segir til um hvaða pinnar gera hvad
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define servoPin 11
#define motorPin 12

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
  motor.attach(motorPin);  // segi servo tilvikinu hvaða pinna á að nota
}

void loop() {

  myservo.write(45);  // rotate the motor counterclockwise

  delay(5000);  // keep rotating for 5 seconds (5000 milliseconds)

  myservo.write(90);  // stop the motor

  delay(5000);  // stay stopped

  myservo.write(135);  // rotate the motor clockwise

  delay(5000);  // keep rotating :D




  if (sonar.ping_cm() < 20) {
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
}
