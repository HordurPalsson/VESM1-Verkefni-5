// Libraries
#include "NewPing.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "tdelay.h"
#include <Servo.h>

// Servo
Servo motor;                
int motor_pinni = 4;                      // pinninn sem ég nota til að stjórna mótornum
int motor_stefnur[] = {0, 90, 180, 90};   // geymir stefnurnar sem mótorinn á að fara í og í hvaða röð
int motor_stefnu_fjoldi = 4;              // breytan geymir hversu margar stefnur eru í listanum
int motor_stefnu_teljari = 0;             // breytan heldur utan um í hvaða stefnu mótorinn á að benda
void munnur();                            // fall útfært neðar
TDelay motor_bid(500);                    // bíða í hálfa sekúndu á milli hreyfinga

// DC mótor
const int HRADI = 5;                      // Verður að vera PWM pinni
const int STEFNA_A = 2;
const int STEFNA_B = 4;
void afram(int hradi);
void bakka(int hradi);
void stoppa();

/*
  VCC tengist í 5V
  Trig tengist í digital pinna. Þarf EKKI að vera PWM.
  Echo tegist í digital pinna. Þarf EKKI að vera PWM.
  Gnd tengist í GND.
*/

// Skynjari
const int ECHO = 2; // digital pinni
const int TRIG = 3; // digital pinni
int distance = 0;  
int fjarlaegd();  // fall sem sér um fjarlægðamælinguna, skilar fjarlægð í cm. 

void setup() {

  // Skynjari
  Serial.begin(9600); 
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);

  // Servo
  motor.attach(motor_pinni);    // segi servo tilvikinu hvaða pinna á að nota
  motor.write(0);               // mótorinn að byrja í 0°

  pinMode(HRADI, OUTPUT);
  pinMode(STEFNA_A, OUTPUT);
  pinMode(STEFNA_B, OUTPUT);
  stoppa();                    // upphafsstaðan, verður stopp þar til annað er ákveðið 
  
}

void talk() {
  afram(150);
  munnur();
}

void loop () {
    
    distance = fjarlaegd();         // fáum fjarlægðamælingu í cm.
  
    // fjarlægð getur ekki verið mínustala
    if(distance < 0) { 
      distance = 0;
    } 
  
    // ef fjarlægð í hlut er minna en 50 cm, má ekki vera neikvæð tala.
    if(distance < 50 && distance != 0) {  
      // setja sýninguna af stað


      if(motor_bid.timiLidinn()) {
        // uppfæra stefnu_teljara breytuna, modulus notað til að talan verði
        // aldrei hærri en fjöldi stefnanna sem eru í listanum
        motor_stefnu_teljari = (motor_stefnu_teljari + 1) % motor_stefnu_fjoldi;
        // veljum svo rétta stefnu úr listanum
        motor.write(motor_stefnur[motor_stefnu_teljari]);
      }
      
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

int fjarlaegd() {
  
    // sendir út púlsa
    digitalWrite(TRIG,LOW);
    delayMicroseconds(2); // of stutt delay til að skipta máli
    digitalWrite(TRIG,HIGH);
    delayMicroseconds(10); // of stutt delay til að skipta máli
    digitalWrite(TRIG,LOW);

    // mælt hvað púlsarnir voru lengi að berast til baka
    return (int)pulseIn(ECHO,HIGH)/58.0; // deilt með 58 til að breyta í cm
  
}