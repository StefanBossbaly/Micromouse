#include "motor.h"
#include "detection.h"

volatile int motor_status = -1;
volatile int motor_adjustment = -1;

stepper_t *stepper0, *stepper1;

void motor_init(stepper_t *left, stepper_t *right)
{
	stepper0 = left;
	stepper1 = right;
}

void motor_turn_left()
{
	motor_status = MOTOR_TURNING;

	int i;

	for (i = 0; i < TURN_ADJ; i++)
	{
		stepper_step(stepper0, BACKWARD);
		stepper_step(stepper1, FORWARD);
	}

	dectection_force_update();

	motor_status = MOTOR_STANDBY;
}

void motor_turn_right()
{
	motor_status = MOTOR_TURNING;

	int i;

	for (i = 0; i < TURN_ADJ; i++)
	{
		stepper_step(stepper0, FORWARD);
		stepper_step(stepper1, BACKWARD);
	}

	dectection_force_update();

	motor_status = MOTOR_STANDBY;
}

void motor_turn_180()
{
	motor_status = MOTOR_TURNING;

	int i;

	for (i = 0; i < TURN_180; i++)
	{
		stepper_step(stepper0, FORWARD);
		stepper_step(stepper1, BACKWARD);
	}

	dectection_force_update();

	motor_status = MOTOR_STANDBY;
}

void motor_move_forward()
{
	motor_status = MOTOR_MOVING;

	int i;
	for (i = 1; i < BLOCK; i++)
	{
		if (motor_adjustment == MOTOR_WALL)
		{
			break;
		}

		stepper_step(stepper0, FORWARD);

		if (motor_adjustment == MOTOR_S_R_ADJ && (i % 12) == 0)
		{
			stepper_step(stepper0, FORWARD);
		}
		else if (motor_adjustment == MOTOR_M_R_ADJ && (i % 6) == 0)
		{
			stepper_step(stepper0, FORWARD);
		}
		else if (motor_adjustment == MOTOR_H_R_ADJ && (i % 2) == 0)
		{
			stepper_step(stepper0, FORWARD);
		}

		stepper_step(stepper1, FORWARD);

		if (motor_adjustment == MOTOR_S_L_ADJ && (i % 12) == 0)
		{
			stepper_step(stepper1, FORWARD);
		}
		else if (motor_adjustment == MOTOR_M_L_ADJ && (i % 6) == 0)
		{
			stepper_step(stepper1, FORWARD);
		}
		else if (motor_adjustment == MOTOR_H_L_ADJ && (i % 2) == 0)
		{
			stepper_step(stepper1, FORWARD);
		}
	}

	motor_status = MOTOR_STANDBY;
}

void motor_turn_to_direction(pos_t *current, dir_t dir)
{
	if (current->direction == dir)
	{
		return;
	}
	else if (position_right_adj_direciton(current->direction) == dir)
	{
		motor_turn_right(stepper0, stepper1);
		current->direction = dir;
	}
	else if (position_left_adj_direciton(current->direction) == dir)
	{
		motor_turn_left(stepper0, stepper1);
		current->direction = dir;
	}
	else
	{
		motor_turn_180(stepper0, stepper1);
		current->direction = dir;
	}
}
