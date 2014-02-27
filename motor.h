#ifndef MOTOR_H
#define	MOTOR_H

#include "position.h"
#include "detection.h"
#include "stepper.h"

#define TURN_ADJ 82
#define TURN_180 164
#define BLOCK 233

#ifdef __cplusplus
extern "C"
{
#endif

// Status of the motor
#define MOTOR_STANDBY 0
#define MOTOR_MOVING 1
#define MOTOR_TURNING 2

//Slight right adjustment
#define MOTOR_NO_ADJ 0
#define MOTOR_S_R_ADJ 1
#define MOTOR_S_L_ADJ 2
#define MOTOR_M_R_ADJ 3
#define MOTOR_M_L_ADJ 3
#define MOTOR_H_R_ADJ 5
#define MOTOR_H_L_ADJ 6
#define MOTOR_WALL 7

// Shared values
extern volatile int motor_status;
extern volatile int motor_adjustment;

void motor_turn_left(stepper_t *stepper0, stepper_t *stepper1);
void motor_turn_right(stepper_t *stepper0, stepper_t *stepper1);
void motor_turn_180(stepper_t *stepper0, stepper_t *stepper1);
void motor_move_forward(stepper_t *stepper0, stepper_t *stepper1);
void motor_turn_to_direction(pos_t *current, dir_t dir);

#ifdef __cplusplus
}
#endif

#endif	/* MOTOR_H */
