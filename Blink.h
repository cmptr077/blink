// 20131330 ÀÌ¿¹ÈÆ, 2018.03.08


#ifndef Blink_h
#define Blink_h

#include "Arduino.h"

class Blink
{
public:
	Blink(int pin);
	void off(int msec0);
	void on(int msec1);
private:
	int _pin;
};
#endif // !Blink
