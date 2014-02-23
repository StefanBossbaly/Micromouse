#include "detection.h"
#include "Arduino.h"


volatile int selected_sensor = -1;

int dectection_relay_position()
{
	return selected_sensor;
}

void dectection_switch_relay(int sensor)
{
	// No bad values please
	if (sensor != S3 && sensor != S4)
	{
		return;
	}

	if (sensor == S3)
	{
		digitalWrite(S4_TRIG, LOW);
		delay(S_CLOSE_MS);
		digitalWrite(S3_TRIG, HIGH);
		delay(S_OPEN_MS);
		selected_sensor = S3;
	}
	else
	{
		digitalWrite(S3_TRIG, LOW);
		delay(S_CLOSE_MS);
		digitalWrite(S4_TRIG, HIGH);
		delay(S_CLOSE_MS);
		selected_sensor = S4;
	}
}

int dectection_reading(int sensor)
{
	// Make sure the sensor is in bounds
	if (sensor < S0 || sensor > 5)
	{
		return -1;
	}

	// If it is the from sensors then just return
	if (sensor >= 0 && sensor < 3)
	{
		return analogRead(sensor);
	}

	// Switch the relays to the correct sensor
	if (dectection_relay_position() != sensor)
	{
		dectection_switch_relay(sensor);
	}

	// Return the value
	return analogRead(3);
}
