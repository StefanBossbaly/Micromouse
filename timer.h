#ifndef TIMER_H
#define	TIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"
{
#endif

void timer_setup();
void timer_init_us(unsigned long frequency, void (*function)(void));
void timer_stop();

#ifdef __cplusplus
}
#endif

#endif	/* TIMER_H */