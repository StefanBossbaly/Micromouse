/* 
 * File:   main.c
 * Author: Stefan
 *
 * Created on March 27, 2013, 10:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "wall.h"

int main(int argc, char** argv) {
    struct nav_cell cells[256];
    struct nav_array nav;
    nav.cells = cells;
    nav.length = 16;
    nav.width = 16;
    
    nav.cells[0].flood_num = -1;
    
    nav_init(&nav);
    
    
    int i;
    
    for (i = 0; i < 256; i++)
    {
        struct nav_cell cell = nav.cells[i];
        printf("%i\n", cell.flood_num);
    }
    
    return (EXIT_SUCCESS);
}

