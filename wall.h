#ifndef WALL_H
#define	WALL_H

#include "position.h"

struct nav_cell
{
    int flood_num;
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

int nav_is_pos_in_bounds(struct nav_array *array, pos_t *position);
int nav_is_in_bounds(struct nav_array *array, int row, int column);


void nav_init(struct nav_array *array);

struct nav_cell *nav_get_cell_pos(struct nav_array *array, pos_t *position);
struct nav_cell *nav_get_cell(struct nav_array *array, int row, int column);

void nav_reset_visited(struct nav_array *array);
inline int nav_has_visited(struct nav_cell *cell);
void nav_flood(struct nav_array *array);
void nav_flood_rec(struct nav_array *array, int row, int column, int flood_num);


#endif	/* WALL_H */

