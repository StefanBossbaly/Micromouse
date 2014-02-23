#ifndef MOTOR_H
#define	MOTOR_H

#include "position.h"
#include "detection.h"
#include "stepper.h"

#define TURN_ADJ 82
#define TURN_180 164

#ifdef __cplusplus
extern "C"
{
#endif

void motor_turn_left(stepper_t *stepper0, stepper_t *stepper1);
void motor_turn_right(stepper_t *stepper0, stepper_t *stepper1);
void motor_turn_180(stepper_t *stepper0, stepper_t *stepper1);

#ifdef __cplusplus
}
#endif

#endif	/* MOTOR_H */
