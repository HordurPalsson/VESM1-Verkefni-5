#include <Servo.h>
#include "tdelay.h"

Servo motor; // bý til tilvik af Servo klasanum
int motor_pinni = 9; // pinninn sem ég nota til að stjórna mótornum

// svipað og listi í python, geymir stefnurnar sem mótorinn á að fara í og í hvaða röð
int motor_stefnur[] = {0, 45, 90, 135}; 
int motor_stefnu_fjoldi = 4; // breytan geymir hversu margar stefnur eru í listanum
int motor_stefnu_teljari = 0; // breytan heldur utan um í hvaða stefnu mótorinn á að benda

TDelay motor_bid(500); // bíða í hálfa sekúndu á milli hreyfinga

void setup() {
  motor.attach(motor_pinni); // segi servo tilvikinu hvaða pinna á að nota
  motor.write(motor_stefnur[motor_stefnu_teljari]); // í þessu tilfelli á mótorinn að byrja í 0°
}

void loop() {
  if(motor_bid.timiLidinn()) {
    // uppfæra stefnu_teljara breytuna, modulus notað til að talan verði
    // aldrei hærri en fjöldi stefnanna sem eru í listanum
    motor_stefnu_teljari = (motor_stefnu_teljari + 1) % motor_stefnu_fjoldi;
    // veljum svo rétta stefnu úr listanum
    motor.write(motor_stefnur[motor_stefnu_teljari]);
  }
}