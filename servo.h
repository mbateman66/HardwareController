
#include <Arduino.h>
#ifndef Servo_h
#define Servo_h

#define PWM_RESOLUTION_BITS 16

// Recommend only the following pins 2,4,12-19,21-23,25-27,32-33

class Servo {

  typedef struct {
    uint32_t hz=50;         // Frequency of pulses
    uint32_t wLeft=500;    // Pulse width for 90deg left
    uint32_t wRight=2500;   // Pulse width for 90deg right
    uint32_t wMin=450;     // Min pulse width
    uint32_t wMax=2550;     // Max pulse width
    float trim=0;         // Degrees +/- to center servo
  } servoDef;

  public:
    Servo();
    void init(uint8_t pin, uint8_t ch);
    void init(uint8_t pin, uint8_t ch, servoDef def);
    void setTrim(float trim);
    void setDeg(float deg);  // -90  = full right, 0 = center,  90 = full left
    int32_t getDeg();
    uint32_t getPulseWidth();
  private:
    bool _initialized = false;
    uint8_t _ch;
    uint8_t _pin;
    float _deg=0; // Center by default
    uint32_t _w;
    servoDef _def;
};
#endif