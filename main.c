/* 
 * File:   main.c
 * Author: Stefan
 *
 * Created on March 27, 2013, 10:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "nav.h"
#include "queue.h"
#include "position.h"

void print_nav(struct nav_array *nav)
{
    int i,j;
    for (i = 0; i < nav->rows; i++)
    {
        for (j = 0; j < nav->columns; j++)
        {
            struct nav_cell *cell = nav_get_cell(nav, i, j);
            printf("%02d ", cell->flood_num);
        }
        printf("\n");
    }
}

void print_wall(struct nav_array *nav)
{
    int i,j;
    for (i = 0; i < nav->rows; i++)
    {
        for (j = 0; j < nav->columns; j++)
        {
            struct nav_cell *cell = nav_get_cell(nav, i, j);
            if (cell->north || cell->east || cell->south || cell->west)
            {
                printf("Index: (%i, %i) (%i, %i, %i, %i)", i, j, cell->north, cell->east, cell->south, cell->west);
                printf("\n");
            }
        };
    }
}

void load_test_maze_walls(struct nav_array *nav, pos_t *pos)
{
    pos->row = 5;
    pos->column = 2;
    pos->direction = north;
    
    nav_update_wall(nav, pos, front);
    
    pos->column = 1;
    pos->row = 4;
    
    nav_update_wall(nav, pos, left);
    nav_update_wall(nav, pos, front);
    
    pos->column = 2;
    nav_update_wall(nav, pos, front);
    
    pos->row = 3;
    pos->column = 1;
    nav_update_wall(nav, pos, left);
    
    pos->row = 2;
    nav_update_wall(nav, pos, left);
    nav_update_wall(nav, pos, front);
    
    pos->row = 1;
    pos->column = 0;
    nav_update_wall(nav, pos, front);
    
    pos->column = 1;
    nav_update_wall(nav, pos, right);
    
    
    pos->row = 5;
    pos->column = 2;
    pos->direction = north; 
}

int main(int argc, char** argv) {
    struct nav_cell cells[3*6];
    struct nav_array nav;
    pos_t pos;
    
    nav.cells = cells;
    nav.rows = 6;
    nav.columns = 3;
    
    nav_init(&nav);
    
    print_wall(&nav);
    
    printf("========================\n");
    load_test_maze_walls(&nav, &pos);
    nav_flood(&nav, &pos);
    print_nav(&nav);
    
    printf("========================\n");
    
    return (EXIT_SUCCESS);
}

