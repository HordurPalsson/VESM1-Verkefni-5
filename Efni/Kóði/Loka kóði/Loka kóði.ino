// Libraries
#include "NewPing.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "tdelay.h"
#include <Servo.h>

// DC mótor
const int HRADI = 5;  // Verður að vera PWM pinni
const int STEFNA_A = 2;
const int STEFNA_B = 4;
TDelay DC_Motorbid(1000) //Bíður í eina sek
void afram(int hradi);
void bakka(int hradi);
void stoppa();

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

// DC mótor
void afram(int hradi) {
  if(DC_Motorbid.timilidinn())
    digitalWrite(STEFNA_A, HIGH);
    digitalWrite(STEFNA_B, LOW);
    analogWrite(HRADI, hradi);
}

void stoppa() {
    digitalWrite(STEFNA_A, LOW);
    digitalWrite(STEFNA_B, LOW);
    analogWrite(HRADI, 0);
}
