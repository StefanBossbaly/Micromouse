#ifndef POSITION_H
#define	POSITION_H

typedef enum
{
    north,
    south,
    east,
    west
} direction;

typedef enum
{
    front,
    back,
    left,
    right
} scalar;

struct position
{
    int row;
    int column;
    direction direction;
};

typedef struct position pos_t;

void position_rotate_right(pos_t *position);
void position_rotate_left(pos_t *position);
void position_move_forward(pos_t *position);

direction position_invert_direciton(direction dir);
direction position_right_adj_direciton(direction dir);
direction position_left_adj_direciton(direction dir);

direction position_convert_to_direction(pos_t *position, scalar scalar);

#endif	/* POSITION_H */

