#ifndef DETECTION_H
#define	DETECTION_H

#include "position.h"

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


alignment_reading detect_alignment_reading(alignment_ir sensor);
wall_reading detect_wall_reading(wall_ir sensor);


#endif	/* DETECTION_H */

