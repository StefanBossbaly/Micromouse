#ifndef DETECTION_H
#define	DETECTION_H

#include "position.h"

#define WALL_INVALID 4
#define WALL_THRESHOLD 1

#define ALIGNMENT_INVALID 4
#define ALIGNMENT_IDEAL 4
#define ALIGNMENT_CLOSE 4

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    front_right,
    front_left
} alignment_ir;

typedef enum
{
    ideal,
    close,
    danger,
    not_available
} alignment_reading;

typedef enum
{
    front_ir,
    left_ir,
    right_ir
} wall_ir;

typedef enum
{
    wall,
    no_wall,
    error
} wall_reading;


int detect_alignment_reading_analog(alignment_ir sensor);
int detect_wall_reading_analog(wall_ir sensor);

alignment_reading detect_alignment_reading(alignment_ir sensor);
wall_reading detect_wall_reading(wall_ir sensor);

#ifdef __cplusplus
}
#endif


#endif	/* DETECTION_H */