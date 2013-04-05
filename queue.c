#include "queue.h"
#include <stdio.h>

void nav_queue_init(nav_queue *queue, nav_queue_cell *cells, int capicity)
{
  queue->array = cells;
  queue->current = 0;
  queue->capicity = capicity;
}

void nav_queue_enqueue(nav_queue *queue, struct nav_cell *cell, int row, int column, int n)
{ 
    if (queue->capicity < queue->current + 1)
    {
        printf("Error");
    }
    nav_queue_cell *queue_cell = &queue->array[queue->current];
    queue_cell->cell = cell;
    queue_cell->row = row;
    queue_cell->column = column;
    queue_cell->n = n;
    
    queue->current++;
}

void nav_queue_dequeue(nav_queue *queue, nav_queue_cell *buffer)
{
    nav_queue_cell *queue_cell = &queue->array[0];
    
    buffer->cell = queue_cell->cell;
    buffer->row = queue_cell->row;
    buffer->column = queue_cell->column;
    buffer->n = queue_cell->n;
    
    int i;
    for (i = 0; i < queue->current; i++)
    {
        queue->array[i] = queue->array[i + 1];
    }
    
    queue->current--;
}

int nav_queue_empty(nav_queue *queue)
{
    return (queue->current == 0);
}
