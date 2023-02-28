// Libraries
#include "NewPing.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "tdelay.h"
#include <Servo.h>

// Objects
// Tölur eru hvaða pinnar fara á arduino-inn
// Skynjari
#define TRIGGER_PIN 9  // Fyrir skynjarann
#define ECHO_PIN 10    // Fyrir skynjarann

// DC mótor
const int HRADI = 5;  // Verður að vera PWM pinni
const int STEFNA_A = 2;
const int STEFNA_B = 4;
void afram(int hradi);
void bakka(int hradi);
void stoppa();

Servo motor;
int motor_pinni = 11;

// Motor
int motor_stefnur[] = { 0, 45, 90, 135 };  // 360 movement
int motor_stefnu_fjoldi = 4;               // breytan geymir hversu margar stefnur eru í listanum
int motor_stefnu_teljari = 0;              // breytan heldur utan um í hvaða stefnu mótorinn á að benda

// Hversu nálagt þarf að vera til að
// kveikja á kóðanum í cm
int distance = 20;

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

TDelay motor_bid(500);  // bíða í hálfa sekúndu á milli hreyfinga

void setup() {
  Serial.begin(9600);
  motor.attach(motor_pinni);                         // segir servo tilvikinu hvaða pinna á að nota
  motor.write(motor_stefnur[motor_stefnu_teljari]);  // í þessu tilfelli á mótorinn að byrja í 0°
  stoppa();                                          // upphafsstaðan, verður stopp þar til annað er ákveðið
}

void loop() {
  if (sonar.ping_cm() < 0) {
  }

  if (sonar.ping_cm() < distance) {
    if (motor_bid.timiLidinn()) {
      // uppfæra stefnu_teljara breytuna, modulus notað til að talan verði
      // aldrei hærri en fjöldi stefnanna sem eru í listanum
      motor_stefnu_teljari = (motor_stefnu_teljari + 1) % motor_stefnu_fjoldi;
      // veljum svo rétta stefnu úr listanum
      motor.write(motor_stefnur[motor_stefnu_teljari]);
    }

    // Keyrir í staðinn ef enginn er nálagt
  } else {
  }
}

// DC mótor
void afram(int hradi) {
  digitalWrite(STEFNA_A, HIGH);
  digitalWrite(STEFNA_B, LOW);
  analogWrite(HRADI, hradi);
}

void stoppa() {
  digitalWrite(STEFNA_A, LOW);
  digitalWrite(STEFNA_B, LOW);
  analogWrite(HRADI, 0);
}
