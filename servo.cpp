#include "servo.h"
#include <esp32-hal-ledc.h>

Servo::Servo() {
}
void Servo::init(uint8_t pin, uint8_t ch) {
	_pin = pin;
	_ch = ch;
	_initialized = true;
	ledcAttachChannel(_pin,_def.hz,PWM_RESOLUTION_BITS,_ch);
	setDeg(_deg);
}
void Servo::init(uint8_t pin, uint8_t ch, servoDef def) {
	_def = def;
	init(pin,ch);
}
void Servo::setTrim(float trim) {
	_def.trim = trim;
	setDeg(_deg);
}
void Servo::setDeg(float deg) {
	if (! _initialized) return;
	_deg = deg;
	int psPerDeg =(_def.wRight - _def.wLeft)*1000/180;
	int wCenter = _def.wLeft+(_def.wRight - _def.wLeft)/2;
	int wTrim = _def.trim*psPerDeg/1000;
	int wTurn = _deg*psPerDeg/1000;
	int w = wCenter + wTrim + wTurn;
	
	if (w<_def.wMin) {
		w=_def.wMin;
	} else if (w>_def.wMax) {
		w=_def.wMax;
	}

	float carrierPeriod =1000000.0/_def.hz;	// Nanosec
	float duty = w / carrierPeriod;
	uint32_t ch_duty_cnt = (1 << PWM_RESOLUTION_BITS) * duty;
	ledcWriteChannel(_ch,ch_duty_cnt);
	Serial.print("------ ");
  	Serial.print(_pin);
  	Serial.print(":");
  	Serial.print(_ch);
	Serial.println(" ------");
	Serial.print("deg: ");
  	Serial.println(_deg);
	Serial.print("psPerDeg: ");
  	Serial.println(psPerDeg);
	Serial.print("wCenter: ");
  	Serial.println(wCenter);
	Serial.print("wTrim: ");
  	Serial.println(wTrim);
	Serial.print("wTurn: ");
  	Serial.println(wTurn);
	Serial.print("w: ");
  	Serial.println(w);
	Serial.print("carrierPeriod: ");
  	Serial.println(carrierPeriod);
	Serial.print("duty: ");
  	Serial.println(duty);
	Serial.print("ch_duty_cnt: ");
  	Serial.println(ch_duty_cnt);
}
int32_t Servo::getDeg() {
	return(_deg);
}
uint32_t Servo::getPulseWidth() {
	return(_w);
}