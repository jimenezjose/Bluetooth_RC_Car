#ifndef CONTROLLER_H 
#define CONTROLLER_H /* multiple inclusion guard */

/* Analog Button Ranges */
#define MAX_KNOB_VAL 1023
#define MAX_SPEED    400
#define MIN_TURN     -255
#define MAX_TURN     255

#define CONTROL_FUNCS { button_up, button_down,  button_left, button_right,\
                        button_select, button_start, button_triangle, \
                        button_square, button_o, button_x, powerButton, \
                        powerButton, info, test, done, NULL }


/****************************************************************************
                           Bluetooth Controller
****************************************************************************/

/* Controller Mode */
int button_up();
int button_down();
int button_left();
int button_right();
int button_select();
int button_start();
int button_triangle();
int button_square();
int button_o();
int button_x();
/* Switch Mode */
int powerButton();
/* Dimmer Mode */
int slideButton();
/* Terminal Mode*/
int info();
int test();
int done();

#endif 
