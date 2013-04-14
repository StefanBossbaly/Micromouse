#ifndef POSITION_H
#define	POSITION_H

/**
 * Coordinate system direction
 */
typedef enum
{
    north,
    south,
    east,
    west
} direction;

/**
 * Facing direction relative to the mouse
 */
typedef enum
{
    front,
    back,
    left,
    right
} facing;

/**
 * Used to keep track of the position of the mouse
 */
typedef struct
{
    int row;
    int column;
    direction direction;
} pos_t;

/**
 * Checks to see if the two positions are equal (they have the same location and direction)
 * @param pos1 the first position
 * @param pos2 the second position
 * @return true if the two positions are equal; false otherwise
 */
int position_equal(pos_t *pos1, pos_t *pos2);

/**
 * Checks to see if the two positions have equal location
 * @param pos1 the first position
 * @param pos2 the second position
 * @return true if the two positions have equal locations; false otherwise
 */
int position_equal_location(pos_t *pos1, pos_t *pos2);

/**
 * Rotates the direction in the position to the right
 * @param position the position to be rotated
 */
void position_rotate_right(pos_t *position);

/**
 * Rotates the direction in the position to the left
 * @param position the position to be rotated
 */
void position_rotate_left(pos_t *position);

/**
 * Moves the position forward to the direction it is facing
 * @param position the position to be moved forward
 */
void position_move_forward(pos_t *position);

/**
 * Returns the direction that is 180 degrees to the given direction
 * @param dir the given direction
 * @return the direction that is 180 degrees to the given direction
 */
direction position_invert_direciton(direction dir);

/**
 * Returns the direction that is to the right of the given direction
 * @param dir the given direction
 * @return the direction that is to the right of the given direction
 */
direction position_right_adj_direciton(direction dir);

/**
 * Returns the direction that is to the left of the given direction
 * @param dir the given direction
 * @return the direction that is to the left of the given direction
 */
direction position_left_adj_direciton(direction dir);

/**
 * Converts the scalar value into a directional value
 * @param position the position of the mouse
 * @param facing which facing we want
 * @return the directional value of the facing
 */
direction position_convert_to_direction(pos_t *position, facing facing);

direction position_get_direction_to(pos_t *position, int row, int column);
#endif	/* POSITION_H */