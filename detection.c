#include "detection.h"

#define WALL_INVALID 4
#define WALL_THRESHOLD 1

#define ALIGNMENT_INVALID 4
#define ALIGNMENT_IDEAL 4
#define ALIGNMENT_CLOSE 4


int detect_alignment_reading_analog(alignment_ir sensor)
{
    if (sensor == front_right)
    {
        
    }
    else if (sensor == front_left)
    {
        
    }
}

int detect_wall_reading_analog(wall_ir sensor)
{
    if (sensor == front_ir)
    {
        
    }
    else if (sensor == left_ir)
    {
        
    }
    else if (sensor == right_ir)
    {
        
    }
}

alignment_reading detect_alignment_reading(alignment_ir sensor)
{
    int reading = detect_alignment_reading_analog(sensor);
    
    if (reading >= ALIGNMENT_INVALID)
    {
        return not_available;
    }
    else if (reading >= ALIGNMENT_IDEAL)
    {
        return ideal;
    }
    else if (reading >= ALIGNMENT_CLOSE)
    {
        return close;
    }
    else
    {
        return danger;
    }
}

wall_reading detect_wall_reading(wall_ir sensor)
{
    int reading = detect_wall_reading_analog(sensor);
    
    if (reading > WALL_INVALID)
    {
        return error;
    }
    else if (reading > WALL_THRESHOLD)
    {
        return wall;
    }
    else
    {
        return no_wall;
    }
}