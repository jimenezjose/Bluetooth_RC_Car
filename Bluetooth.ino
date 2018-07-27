char buffer[ BUFFER_SIZE ] = { 0 }; /* user input buffer */
int (* commandFunc)();         /* interpreted bluetooth command */

/***************************************************************************
% Routine Name : bluetoothRead
% File :         Bluetooth.ino
% Parameters:    None
% Description :  
% Return:        
***************************************************************************/
int ( * bluetoothRead() )() {
  commandFunc = NULL;
  
  if( BT.available() > 0 ) {
    /* incomming Bluetooth data */
    populateBuffer( buffer, BUFFER_SIZE );         /* populate buffer BT data */
    Serial.println( buffer );         /* report command on the serial monitor */
    commandFunc = interpretCmd( buffer );         /* interpret button pressed */
  }

  if( Serial.available() > 0 ) {
    /* Bluetooth message communication */
    String message = getMessage();
    sendMessage( message );
  }

  return commandFunc;
  
}

