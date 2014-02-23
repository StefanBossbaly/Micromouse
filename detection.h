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

#define S_CLOSE_MS 5
#define S_OPEN_MS 5

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

typedef enum
{
    ideal = 0,
    close = 1,
    danger = 2,
    not_available = 3,
    error = 4
} sensor_reading;

typedef enum
{
    front_ir,
    left_ir,
    right_ir
} wall_ir;

void dectection_switch_relay(int sensor);
int dectection_relay_position();
int dectection_reading(int sensor);


#ifdef __cplusplus
}
#endif


#endif	/* DETECTION_H */
