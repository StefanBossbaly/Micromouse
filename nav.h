#ifndef NAV_H
#define	NAV_H

#include "position.h"
#include "inttypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct nav_cell
{
    int flood_num;
    int has_visited;
    uint8_t wall;
    int row;
    int column;
};

struct nav_array
{
    struct nav_cell *cells;
    int columns;
    int rows;
};

int nav_is_pos_in_bounds(struct nav_array *array, pos_t *position);
int nav_is_in_bounds(struct nav_array *array, int row, int column);
int nav_size(struct nav_array *array);


/*Init*/
void nav_init(struct nav_array *array, struct nav_cell *cells, int rows, int columns);

/*Getters*/
struct nav_cell *nav_get_cell_pos(struct nav_array *array, pos_t *position);
struct nav_cell *nav_get_cell(struct nav_array *array, int row, int column);

/*Flood Stuff*/
void nav_reset_flood_num(struct nav_array *array);
int nav_is_flooded(struct nav_cell *cell);
void nav_flood(struct nav_array *array, pos_t *start);

/*Exploration Stuff*/
void nav_explore(struct nav_array *array, pos_t *start);
void nav_explore_rec(struct nav_array *array, pos_t *current);

/*Driver*/
void nav_drive_to_target(struct nav_array *array, pos_t *start, pos_t *target);
struct nav_cell *nav_get_next_neighbor(struct nav_array *array, int row, int column);

/*Wall*/
void nav_update_wall_cell(struct nav_cell *cell, dir_t dir);
void nav_update_wall(struct nav_array *array, pos_t *position, facing_t dir);

inline uint8_t nav_north_wall(struct nav_cell *cell);
inline uint8_t nav_east_wall(struct nav_cell *cell);
inline uint8_t nav_south_wall(struct nav_cell *cell);
inline uint8_t nav_west_wall(struct nav_cell *cell);


#ifdef __cplusplus
}
#endif

#endif	/* NAV_H */
