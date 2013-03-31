/* 
 * File:   main.c
 * Author: Stefan
 *
 * Created on March 27, 2013, 10:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "wall.h"

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

int main(int argc, char** argv) {
    struct nav_cell cells[256];
    struct nav_array nav;
    nav.cells = cells;
    nav.length = 16;
    nav.width = 16;
    
    nav_init(&nav);
    print_nav(&nav);
    
    nav_flood(&nav);
    print_nav(&nav);
    
    nav_reset_visited(&nav);
    print_nav(&nav);
    
    return (EXIT_SUCCESS);
}

