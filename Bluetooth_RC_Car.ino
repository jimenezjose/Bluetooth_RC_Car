/****************************************************************************

                                                Jose Jorge Jimenez-Olivas
                                                June 25, 2018

                      Arduino bluetooth controller

File Name:       RC_CarHack.ino
Description:     This program integrates the HC-06 bluetooth module
		 with the "Arduino Bluetooth Controller" app. Compatible to 
		 Controller, Swicth, Dimmer, and Terminal mode.
Sources of Help: Example sketch for the Xbox Wireless Reciver library 
                   - developed by Kristian Lauszus
                   - Example "XBOXRECV"
Libraries Used:
                 - https://github.com/pololu/drv8835-motor-shield
                 - https://github.com/PaulStoffregen/SoftwareSerial
                 - https://github.com/felis/USB_Host_Shield_2.0
****************************************************************************/

#include <DRV8835MotorShield.h> 
#include <SoftwareSerial.h>               
#include "Bluetooth.h"

SoftwareSerial BT(11, 12);     /* RX, TX */
DRV8835MotorShield motor;      /* Polulu H-Bridge sheild */

/* Pin variables */
const int knobPin = A0;
const int statusLED = 13;

int (* buttonFunc)();          /* interpreted bluetooth command */
boolean testMode = false;      /* rc car in test mode */
int velocity = 0;              /* relative vector speed of dc motor */
int turn = 0;                  /* rc vector steering */

void setup() {
  Serial.begin( 9600 );
  BT.begin( 9600 );
  pinMode( knobPin, INPUT );
  pinMode( statusLED, OUTPUT );
  
  /* initial car state */
  digitalWrite( statusLED, HIGH );
  motor.setM1Speed( velocity );
  motor.setM2Speed( turn );

}

void loop() {

  buttonFunc = bluetoothRead(); /* read and parse bluetooth data */
  if( buttonFunc != NULL ) {
    /* valid button comand - execute button function */
    buttonFunc();
  }
  if( testMode ) {
    /* test Mode On */
    test();
  }
  
}


