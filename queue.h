#ifndef QUEUE_H
#define	QUEUE_H

typedef struct
{
    struct nav_cell *cell;
    int row;
    int column;
    int n;
} nav_queue_cell;

typedef struct
{
    nav_queue_cell *array;
    int capicity;
    int current;
} nav_queue;

void nav_queue_init(nav_queue *queue, nav_queue_cell *cells, int capicity);
void nav_queue_enqueue(nav_queue *queue, struct nav_cell *cell, int row, int column, int n);
void nav_queue_dequeue(nav_queue *queue, nav_queue_cell *buffer);
int nav_queue_empty(nav_queue *queue);

#endif	/* QUEUE_H */

