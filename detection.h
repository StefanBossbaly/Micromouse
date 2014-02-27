#ifndef DETECTION_H
#define	DETECTION_H

#include "position.h"

// Sensors and their unique number
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4

// Digital Trigger pins for relay
#define S3_TRIG 3
#define S4_TRIG 4

// The delay for the relays
#define S_CLOSE_MS 10
#define S_OPEN_MS 10

// Ideal center values
#define S0_IDEAL 150
#define S2_IDEAL 110

// Tolerance
#define S_TOL 5

// Our ranges
#define S_S_RANGE 20
#define S_H_RANGE 20



#ifdef __cplusplus
extern "C"
{
#endif


void dectection_switch_relay(int sensor);
int dectection_relay_position();
int dectection_reading(int sensor);

void dectection_timer_callback();
void dectection_force_update();
void dectection_update_adj(int s0, int s1, int s2);
void dectection_centering_adj(int s0, int s2);

#ifdef __cplusplus
}
#endif


#endif	/* DETECTION_H */
