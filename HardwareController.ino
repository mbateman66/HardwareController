#include <HardwareSerial.h>

#include "commands.h"
#include "pins.h"
#include "servo.h"
#include <Arduino.h>

#define BAUDRATE 115200

#define MAX_SERVOS 16
/* Variable initialization */

// A pair of varibles to help parse serial commands
int arg = 0;
int indx = 0;

Servo servo[MAX_SERVOS];

// Character arrays to hold the first and second arguments
#define MAX_ARGS 32
#define MAX_DIGITS 16
char argv[MAX_ARGS][MAX_DIGITS];  // Args as strings
long argi[MAX_ARGS];              // The arguments converted to integers
float argf[MAX_ARGS];              // The arguments converted to floats

void runCommand() {
  Serial.println("");  
  char cmd = argv[0][0];
  if (cmd == NULL) {
    Serial.println("Cmd: NULL");
    return;
  }
  Serial.print("Cmd: ");
  Serial.println(cmd);
  for (int i=0;i<=arg;i++) {
    argi[i] = atoi(argv[i]);  // Convert to integers  
    argf[i] = atof(argv[i]);  // Convert to integers  
    Serial.print("Arg[");
    Serial.print(i);
    Serial.print("]: '");
    Serial.print(argv[i]);
    Serial.print("'\t(");
    Serial.print(argi[i]);
    Serial.print(")\t(");
    Serial.print(argf[i]);
    Serial.println(")");
  }
    

  Serial.println("----------------");
  
  switch(cmd) {
    case SERVO_WRITE: {
      for (int i=1;i<arg+1;i+=2) {
        int num = argi[i];
        float deg = argf[i+1];
        if (num>=0 && num<MAX_SERVOS) {
          servo[num].setDeg(deg);
        } else {
          Serial.print("Out of range: ");
          Serial.println(num);
        }
      }
      break;
    }
    case SERVO_READ: {
      Serial.print("s ");
      // int deg = servo1.getDeg();
      // Serial.println(deg);
      break;
    }
    case SERVO_TRIM: {
      float trim = argf[1];
      // servo1.setTrim(trim);
      break;
    }
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
  servo[0].init(13,0);
  servo[2].init(12,1);

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
