/****************************************************************************
                                                Jose Jorge Jimenez-Olivas
                                                June 25, 2018

File Name:      Controller.ino
Description:    Button command functions. Button behavior is handled in this
                file, every function is mapped to a specific button from the 
                bluetooth controller. 
****************************************************************************/
#include "Controller.h"

/* test function variables */
static unsigned long previousMillis = 0;
static unsigned long currentMillis  = 0;
static unsigned long interval = 1000; 

/****************************************************************************
                           Bluetooth Controller
****************************************************************************/

/* Connected in: Controller Mode */

int button_up() {
  int knobVal = analogRead( knobPin );
  velocity = map(knobVal, 0, MAX_KNOB_VAL, 0, MAX_SPEED);
  motor.setM1Speed( velocity );
  BT.print( "Up Velocity:  " );
  BT.println( velocity );

  return 0;
}

int button_down() {
  int knobVal = analogRead( knobPin );
  velocity = -1 * map(knobVal, 0, MAX_KNOB_VAL, 0, MAX_SPEED);
  motor.setM1Speed( velocity );
  BT.print( "Down Velocity:  " );
  BT.println( velocity );
  return 0;
}

int button_left() {
  if( turn > MAX_TURN ) {
    turn = MAX_TURN;
  }
  turn -= MAX_TURN;
  motor.setM1Speed( 0 );
  motor.setM2Speed( turn );
  BT.println( turn );
  motor.setM1Speed( velocity );
  return 0;
}

int button_right() {
  if( turn < MIN_TURN ) {
    turn = MIN_TURN;
  }
  turn += MAX_TURN;
  motor.setM1Speed( 0 );
  motor.setM2Speed( turn );
  BT.println( turn );
  motor.setM1Speed( velocity );
  return 0;
}

int button_select() {
  done();
  return 0;
}

int button_start() {
  testMode = true;
  return 0;
}

int button_triangle() {

  return 0;
}

int button_square() {
  velocity = 0;
  motor.setM1Speed( velocity );
  BT.println( "Stop" );
  
  return 0;
}

int button_o() {

  return 0;
}

int button_x() {

  return 0;
}

/* Connected in: Swicth Mode */

int powerButton() {
  
  return 0;
}

/* Connected in: Dimmer Mode */

int slideButton() {

  return 0;
}

/* terminal */

int info() {
  int knobVal = analogRead( knobPin );

  BT.print( "Knob Status: " );
  BT.println( knobVal );
  BT.print( "Velocity Status: " );
  BT.println( velocity );
  BT.print( "Turn Status: " );
  BT.println( turn );

   return 0;
}

int test() {

  if( testMode == false ) {
    /* test mode setup */
    testMode = true;
    previousMillis = millis();
    digitalWrite( statusLED, LOW );
  }

  velocity = map( analogRead(knobPin), 0, 1023, 0, 400 );
  motor.setM1Speed( velocity );

  currentMillis = millis();
  if( currentMillis - previousMillis > interval ) {
    /* one second bursts of velocity status */
    BT.print( "velocity:  " );
    BT.println( velocity );
    previousMillis = currentMillis;
    digitalWrite( statusLED, !digitalRead( statusLED ) );
  }
  
  return 0;
}

int done() {
  testMode = false;
  velocity = 0;
  motor.setM1Speed( velocity ); 
  digitalWrite( statusLED, HIGH );
  
  return 0;
}

