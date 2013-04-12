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
    for (i = 0; i < nav->width; i++)
    {
        for (j = 0; j < nav->length; j++)
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
    for (i = 0; i < nav->width; i++)
    {
        for (j = 0; j < nav->length; j++)
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

int main(int argc, char** argv) {
    struct nav_cell cells[256];
    struct nav_array nav;
    pos_t pos;
    nav.cells = cells;
    nav.length = 16;
    nav.width = 16;
    
    nav_init(&nav);
    
    pos.row = 0;
    pos.column = 0;
    pos.direction = south;
    
    nav_update_wall(&nav, &pos, left);
    pos.column = 1;
    nav_update_wall(&nav, &pos, front);
    
    /*struct nav_cell *first = nav_get_cell(&nav, 0, 0);
    struct nav_cell *second = nav_get_cell(&nav, 0, 1);
    struct nav_cell *thrid = nav_get_cell(&nav, 1, 1);
    
    first->east = 1;
    second->west = 1;
    second->south = 1;
    thrid->north = 1;*/
    
    print_wall(&nav);
    
    printf("========================\n");
    
    nav_flood(&nav);
    print_nav(&nav);
    
    printf("========================\n");
    
    return (EXIT_SUCCESS);
}

