#include "detection.h"
#include "motor.h"
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

void dectection_update_adj(int s0, int s1, int s2)
{
	// Values to see if sensors are usable
	int s0_use = 0, s2_use = 0;

	// See if the s0 is usable
	if (s0 >= 135 && s0 <= 165)
	{
		s0_use = 1;
	}

	// See if the s2 is usable
	if (s2 >= 85 && s2 <= 115)
	{
		s2_use = 1;
	}

	// If both sensors are usable
	if (s0_use == 1 && s2_use == 1)
	{
		int diff = s0 - s2 - 50;

		if (diff >= -5 && diff <= 5)
		{
			motor_adjustment = MOTOR_NO_ADJ;
		}
		else if (diff >= -5 && diff <= -15)
		{
			motor_adjustment = MOTOR_S_L_ADJ;
		}
		else if (diff >= 5 && diff <= 15)
		{
			motor_adjustment = MOTOR_S_R_ADJ;
		}
		else if (diff < -15)
		{
			motor_adjustment = MOTOR_H_L_ADJ;
		}
		else if (diff > 15)
		{
			motor_adjustment = MOTOR_H_R_ADJ;
		}
	}
	// Running blind
	else
	{
		motor_adjustment = MOTOR_NO_ADJ;
	}
}
