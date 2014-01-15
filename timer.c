#include "timer.h"


void (*intFunc)();

void timer_setup()
{
	timer_stop();           // Disable Timer2 interrupt.
	ASSR &= ~(1 << AS2);      // Set clock, not pin.
	TCCR2A = (1 << WGM21);    // Set Timer2 to CTC mode.
	TCCR2B = (1 << CS22);     // Set Timer2 prescaler to 64 (4uS/count, 4uS-1020uS range).
	TCNT2 = 0;              // Reset Timer2 counter.
}

void timer_init_us(unsigned long frequency, void (*function)(void))
{
	timer_setup();      // Configure the timer interrupt.
	intFunc = function; // User's function to call when there's a timer event.
	OCR2A = min((frequency >> 2) - 1, 255); // Every count is 4uS, so divide by 4 (bitwise shift right 2) subtract one, then make sure we don't go over 255 limit.
	TIMSK2 |= (1 << OCIE2A);                // Enable Timer2 interrupt.
}

void timer_stop()
{
	TIMSK2 &= ~(1 << OCIE2A);
}

ISR (TIMER2_COMPA_vect)
{
	if (intFunc)
	{
		intFunc(); // If wrapped function is set, call it.
	}
}