/* 
 * File:   main.c
 * Author: Stefan
 *
 * Created on March 27, 2013, 10:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "nav.h"
#include "memmgr.h"

void print_nav(struct nav_array *nav)
{
    int i,j;
    for (i = 0; i < nav->width; i++)
    {
        for (j = 0; j < nav->length; j++)
        {
            struct nav_cell *cell = nav_get_cell(nav, i, j);
            printf("%i ", cell->flood_num);
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
    memmgr_init();
    struct nav_cell cells[256];
    struct nav_array nav;
    nav.cells = cells;
    nav.length = 16;
    nav.width = 16;
    
    pos_t pos;
    pos.column = 0;
    pos.row = 0;
    pos.direction = north;
    
    nav_init(&nav);
    print_nav(&nav);
    
    /*nav_flood(&nav);
    print_nav(&nav);
    
    nav_reset_visited(&nav);
    print_nav(&nav);*/
    
    nav_update_wall(&nav, &pos, right);
    print_wall(&nav);
    
    return (EXIT_SUCCESS);
}

