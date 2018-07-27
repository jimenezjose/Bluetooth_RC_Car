/****************************************************************************
                                                Jose Jorge Jimenez-Olivas
                                                June 25, 2018

File Name:      HandleInput.ino
Description:    Reads Serial data recieved from the bluetooth module and 
                interprets the serial data into button commands. 
****************************************************************************/
#include "HandleInput.h"
#include "Controller.h"

static const char * const COMMANDS_LIST[] = COMMANDS;
static int (* const button_funcs[])() = CONTROL_FUNCS;

/***************************************************************************
% Routine Name : populateBuffer
% File :         HandleInput.ino
% Parameters:    buffer: character buffer awaiting to be filled with bytes
%                        of bluetooth data.
%                size:   size of the character buffer.
% Description :  Populates buffer with bytes of Serial data. After the 
%                all the bytes are read, the message is null terminated.
% Return:        Nothing
***************************************************************************/
void populateBuffer( char * buffer, long size ) {

  int index; /* buffer index */

  index = 0;
  while( BT.available() > 0 && index < size - 1 ) {
    /* populate buffer with bluetooth data */
    buffer[ index ] = toLowerCase( BT.read() );
    index++;
    delay( BT_TX_DELAY );
  }

  buffer[ index ] = '\0';

}

/***************************************************************************
% Routine Name : interpretCmd
% File :         HandleInput.ino
% Parameters:    command: command string
% Description :  Translates the command string into its button function 
%                pointer
% Return:        pointer to the interpreted command function OR NULL if 
%                command is not recognized. 
***************************************************************************/
int ( * interpretCmd( char * command ))() {

  int validInt = atoi( buffer ) || buffer[ 0 ] == '0';  /* valid integer conv.*/
  int stringLen = strlen( command );         /* length of user command string */
  int index = 0;                                       /* commands list index */

  while( COMMANDS_LIST[ index ] != NULL ) {
    /* searching for command in list */
    if( strncmp( command, COMMANDS_LIST[ index ], stringLen ) == 0 && strlen(COMMANDS_LIST[ index ]) == stringLen ) {
      /* Command found */
      return button_funcs[ index ];
    }
    index++;
  }

  if( validInt ) {
    /* Controller in Dimmer Mode */
    return slideButton;
  }

  return NULL;
}

/***************************************************************************
% Routine Name : getMessage
% File :         HandleInput.ino
% Parameters:    None
% Description :  Interprets buffered bytes from serial monitor as message 
%                characters
% Return:        Message from Serial monitor
***************************************************************************/
String getMessage() {
  String message = "";

  while( Serial.available() > 0 ) {
    /* populating string with Serial data */
    message += (char) Serial.read();
    delay( BT_TX_DELAY );
  }

  return message;
}

/***************************************************************************
% Routine Name : sendMessage
% File :         HandleInput.ino
% Parameters:    message: character string to send
% Description :  send a character string to bluetooth linked device
% Return:        Nothing 
***************************************************************************/
void sendMessage( String message ) {
    BT.print( message );
    Serial.print( "> " + message ); 
}

