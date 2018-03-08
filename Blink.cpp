// 20131330 ÀÌ¿¹ÈÆ, 2018.03.08

#include "Arduino.h"
#include "Blink.h"

Blink::Blink(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
}

void Blink::off(int msec0)
{
	digitalWrite(_pin, HIGH);
	delay(msec0);
}

void Blink::on(int msec1)
{
	digitalWrite(_pin, LOW);
	delay(msec1);
}