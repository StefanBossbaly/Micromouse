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

// Upper and lower bounds of ideal for s0
#define S0_UPPER_IDEAL 145
#define S0_LOWER_IDEAL 135

// Upper and lower bounds of ideal for s2
#define S2_UPPER_IDEAL 110
#define S2_LOWER_IDEAL 100

// Thresholds for using the sensors
#define S0_USE_THRESHOLD 90
#define S2_USE_THRESHOLD 40

#ifdef __cplusplus
extern "C"
{
#endif


void dectection_switch_relay(int sensor);
int dectection_relay_position();
int dectection_reading(int sensor);

#ifdef __cplusplus
}
#endif


#endif	/* DETECTION_H */
