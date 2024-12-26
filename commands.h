/* Define single-letter commands that will be sent by the PC over the
   serial link.
*/

#ifndef COMMANDS_H
   #define COMMANDS_H

   #define SERVO_WRITE  's'   // indx +/-pct          example: s 4 45 5 -10
   #define SERVO_READ   'S'   // list of servo indx   example: s 4 5    output: same as write format
   #define SERVO_TRIM   't'   // indx trimNs          example: t 4 12 5 -13

#endif