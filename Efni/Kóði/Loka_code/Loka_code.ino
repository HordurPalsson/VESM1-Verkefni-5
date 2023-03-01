// Libraries
#include "NewPing.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "tdelay.h"
#include <Servo.h>

// Sensor
const int ECHO = 7;
const int TRIG = 6;
int distance = 0;
int fjarlaegd();  // fall sem sér um fjarlægðamælinguna, skilar fjarlægð í cm.


// DC mótor
const int HRADI = 5;  // Verður að vera PWM pinni
const int STEFNA_A = 2;
const int STEFNA_B = 4;
void afram(int hradi);
TDelay DC_Motorbid(500);  //Bíður í tvær sek
void bakka(int hradi);
void stoppa();

// MP3 hljóð
DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial mySoftwareSerial(12, 13);  // RX, TX
void playSound();                         // útfært neðar
TDelay spilun(4500);                      // Tími fyrir hljóðskrá að spila í millis, 5 sekúndur hér.

// Servo
Servo motor;
int motor_pinni = 3;                // pinninn sem ég nota til að stjórna mótornum
int motor_stefnur[] = { 0, 90 };  // geymir stefnurnar sem mótorinn á að fara í og í hvaða röð
int motor_stefnu_fjoldi = 2;        // breytan geymir hversu margar stefnur eru í listanum
int motor_stefnu_teljari = 0;       // breytan heldur utan um í hvaða stefnu mótorinn á að benda
void munnur();                      // fall útfært neðar
TDelay motor_bid(900);              // bíða í hálfa sekúndu á milli hreyfinga

void setup() {
  // Sensor
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Hljóð
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    while (true)
      ;
  }
  myDFPlayer.volume(10);  // Set volume value. From 0 to 30

  // Servo
  motor.attach(motor_pinni);  // segi servo tilvikinu hvaða pinna á að nota
  motor.write(motor_stefnur[motor_stefnu_teljari]);             // mótorinn að byrja í 0°
}

void loop() {
  distance = fjarlaegd();

  // fjarlægð getur ekki verið mínustala
  if (distance < 0) {
    distance = 0;
  }

  // ef fjarlægð í hlut er minna en 50 cm, má ekki vera neikvæð tala.
  if (distance < 50 && distance != 0) {
    // setja sýninguna af stað
    playSound();
    afram(150);
    mouth();
    delay(5000);

  } else {
    distance = 0;
    stoppa();
  }

}




// spilar hljóðskrá á x fresti
void playSound() {
  if (spilun.timiLidinn() == true) {
    myDFPlayer.play(1);  // Play mp3
  }
}

// DC mótor
void afram(int hradi) {
  if (DC_Motorbid.timiLidinn())
    digitalWrite(STEFNA_A, HIGH);
  digitalWrite(STEFNA_B, LOW);
  analogWrite(HRADI, hradi);
}

void stoppa() {
  digitalWrite(STEFNA_A, LOW);
  digitalWrite(STEFNA_B, LOW);
  analogWrite(HRADI, 0);
}

// munnurinn
void munnur() {
  motor_stefnu_teljari = (motor_stefnu_teljari + 1) % motor_stefnu_fjoldi;
  if (motor_bid.timiLidinn()) {
    // uppfæra stefnu_teljara breytuna, modulus notað til að talan verði
    // aldrei hærri en fjöldi stefnanna sem eru í listanum
    motor_stefnu_teljari = (motor_stefnu_teljari + 1) % motor_stefnu_fjoldi;
    // veljum svo rétta stefnu úr listanum
    motor.write(motor_stefnur[motor_stefnu_teljari]);
  }
}

// Munnur v2
void mouth() {
  delay(500);
  motor.write(90);
  delay(500);
  motor.write(10);
  delay(500);
  motor.write(90);
  delay(500);
  motor.write(10);
  delay(500);
  motor.write(90);
  delay(500);
  motor.write(10);
  delay(500);
  motor.write(90);
  delay(500);
  motor.write(10);

}



int fjarlaegd() {

  // sendir út púlsa
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); // of stutt delay til að skipta máli
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); // of stutt delay til að skipta máli
  digitalWrite(TRIG, LOW);

  // mælt hvað púlsarnir voru lengi að berast til baka
  return (int)pulseIn(ECHO, HIGH) / 58.0; // deilt með 58 til að breyta í cm

}
