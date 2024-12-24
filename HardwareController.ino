
#define BAUDRATE 115200
#include "commands.h"
#include "pins.h"


/* Variable initialization */

// A pair of varibles to help parse serial commands (thanks Fergs)
int arg = 0;
int indx = 0;

// Character arrays to hold the first and second arguments
#define MAX_ARGS 6
#define MAX_DIGITS 16
char argv[MAX_ARGS][MAX_DIGITS];  // Args as strings
long argi[MAX_ARGS];              // The arguments converted to integers

void runCommand() {
  Serial.println("");  
  char cmd = argv[0][0];
  if (cmd == NULL) {
    Serial.println("Cmd: NULL");
    return;
  }
  Serial.print("Cmd: ");
  Serial.println(cmd);
  for (int i=0;i<MAX_ARGS;i++) {
    argi[i] = argv[i] == NULL ? 0 : atoi(argv[i]);  // Convert to integers  
    Serial.print("Arg[");
    Serial.print(i);
    Serial.print("]: '");
    Serial.print(argv[i]);
    Serial.print("'\t(");
    Serial.print(argi[i]);
    Serial.println(")");
  }
    

  Serial.println("----------------");
  
  switch(cmd) {
    case GET_BAUDRATE:
      Serial.print("b ");
      Serial.println(BAUDRATE);
      break;
    case MOTOR_RAW_PWM:
      int left  = argi[1]<255 ? argi[1] : 255; // Cap at 255
      int right = argi[2]<255 ? argi[2] : 255; // Cap at 255
      analogWrite(PIN_MOTOR_PWM_LEFT, left);
      analogWrite(PIN_MOTOR_PWM_RIGHT, right);
      break;
  }
}

void resetCommand() {
  indx = 0;
  arg = 0;
  for (int i=0;i<MAX_ARGS;i++) {
    memset(argv[i], 0, sizeof(argv[i]));
    argi[i] = 0;
  }
}

void setup() {
  // Setup serial port
  Serial.begin(BAUDRATE);
  Serial.println("Starting");
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);

}

void loop() {  
  while (Serial.available() > 0) {
    
    // Read the next character
    char chr = Serial.read();
    

    // Terminate a command with a CR
    if (chr == 13) {        // CR is end of command
      argv[arg][indx] = NULL;
      runCommand();
      resetCommand();
    } else if (chr == ' ') { // Space is arg delim
      if (arg < MAX_ARGS) {
        argv[arg++][indx] = NULL;
        indx = 0;
      }
    }
    else {
      if (indx < MAX_DIGITS) {
        argv[arg][indx++] = chr;
      }
    }

  }
  
  
}
