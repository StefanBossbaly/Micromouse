#ifndef POSITION_H
#define	POSITION_H

enum
{
    north,
    south,
    east,
    west
} direction;

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

#endif	/* POSITION_H */

