#include "timer.h"


void (*intFunc)(void);
void (*intFunc2)(void);
int times = 0;
int times_init = 0;

void timer_setup()
{
	// Disable Timer2 interrupt.
	timer_stop();

	// Clock source is from internal and prescaler (PG 145)
	ASSR &= ~(1 << AS2);

	// Set Timer2 to CTC mode.
	TCCR2A = (1 << WGM21);

	// Set Timer2 prescaler to 1024 (64uS/count, 64uS - 14400us range).
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);

	// Reset Timer2 counter.
	TCNT2 = 0;
}

void timer_init_us(unsigned long frequency, void (*function)(void))
{
	timer_setup();      // Configure the timer interrupt.
	intFunc = function; // User's function to call when there's a timer event.
	OCR2A = min((frequency >> 6) - 1, 255); // Every count is 64uS, so divide by 64 (bitwise shift right 2) subtract one, then make sure we don't go over 255 limit.
	
	TIMSK2 |= (1 << OCIE2A);                // Enable Timer2 interrupt.
}

void timer_ms_countdown()
{
	if (times == 0)
	{
		intFunc2();
		times = times_init;
	}
	else
	{
		times--;
	}
}

void timer_init_ms(unsigned long frequency, void (*function)(void))
{
	timer_setup();
	times = times_init = frequency;

	intFunc = timer_ms_countdown;
	intFunc2 = function;

	// (16 - 1) * 64 = 1024 uS ... close enough 
	OCR2A = 15;

	// Enable Timer2 interrupt
	TIMSK2 |= (1 << OCIE2A);
}

void timer_stop()
{
	// Page 163 of documentation
	// Disable OCIE2A (Timer/Counter2 Output Compare Match A Interrupt Enable)
	TIMSK2 &= ~(1 << OCIE2A);
}

// ISR of timer 2 compare vector
ISR (TIMER2_COMPA_vect)
{
	if (intFunc)
	{
		intFunc(); // If wrapped function is set, call it.
	}
}