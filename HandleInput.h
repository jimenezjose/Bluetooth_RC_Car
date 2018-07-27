#ifndef HANDLEINPUT_H /* multiple inclusion guard */
#define HANDLEINPUT_H

#define BT_TX_DELAY 2
#define MAX_DIM_LENGTH 3

#define TRUE 1
#define FALSE 0

#define COMMANDS { "up", "down", "left", "right",\
                   "select", "start", "triangle",\
                   "square", "o", "x", "on", "off",\
                   "info", "test", "done", NULL }

void populateBuffer( char *, long );
int ( * interpretCmd( char * ))();
String getMessage();
void sendMessage( String message );

#endif
