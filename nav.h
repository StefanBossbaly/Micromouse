#ifndef NAV_H
#define	NAV_H

#include "position.h"

struct nav_cell
{
    int flood_num;
    int has_visited;
    int north;
    int south;
    int east;
    int west;
};

struct nav_array
{
    struct nav_cell *cells;
    int width;
    int length;
};

//Other
int nav_is_pos_in_bounds(struct nav_array *array, pos_t *position);
int nav_is_in_bounds(struct nav_array *array, int row, int column);
inline int nav_size(struct nav_array *array);


//Init
void nav_init(struct nav_array *array);

//Getters
struct nav_cell *nav_get_cell_pos(struct nav_array *array, pos_t *position);
struct nav_cell *nav_get_cell(struct nav_array *array, int row, int column);

//Flood Stuff
void nav_reset_flood_num(struct nav_array *array);
inline int nav_is_flooded(struct nav_cell *cell);
void nav_flood(struct nav_array *array);
void nav_flood_rec(struct nav_array *array, int row, int column, int flood_num);

//Wall
void nav_update_wall_cell(struct nav_cell *cell, direction dir);
void nav_update_wall(struct nav_array *array, pos_t *position, facing dir);

#endif	/* NAV_H */

