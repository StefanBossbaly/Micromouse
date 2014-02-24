#include "motor.h"

void motor_turn_left(stepper_t *stepper0, stepper_t *stepper1)
{
	motor_status = MOTOR_TURNING;

	int i;

	for (i = 0; i < TURN_ADJ; i++)
	{
		stepper_step(stepper0, FORWARD);
		stepper_step(stepper1, BACKWARD);
	}

	motor_status = MOTOR_STANDBY;
}

void motor_turn_right(stepper_t *stepper0, stepper_t *stepper1)
{
	motor_status = MOTOR_TURNING;

	int i;

	for (i = 0; i < TURN_ADJ; i++)
	{
		stepper_step(stepper0, BACKWARD);
		stepper_step(stepper1, FORWARD);
	}

	motor_status = MOTOR_STANDBY;
}

void motor_turn_180(stepper_t *stepper0, stepper_t *stepper1)
{
	motor_status = MOTOR_TURNING;

	int i;

	for (i = 0; i < TURN_180; i++)
	{
		stepper_step(stepper0, FORWARD);
		stepper_step(stepper1, BACKWARD);
	}

	motor_status = MOTOR_STANDBY;
}

void motor_move_forward(stepper_t *stepper0, stepper_t *stepper1)
{
	motor_status = MOTOR_MOVING;

	int i;
	for (i = 0; i < BLOCK; i++)
	{
		stepper_step(stepper0, FORWARD);
		stepper_step(stepper1, FORWARD);
	}

	motor_status = MOTOR_STANDBY;
}
