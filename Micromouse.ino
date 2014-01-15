#include "nav.h"
#include "queue.h"
#include "position.h"
#include "timer.h"

/*void print_nav(struct nav_array *nav)
{
	char temp[20];

    int i,j;
    for (i = 0; i < nav->rows; i++)
    {
        for (j = 0; j < nav->columns; j++)
        {
            struct nav_cell *cell = nav_get_cell(nav, i, j);

            if (cell->flood_num < 10)
            {
            	Serial.print('0');
            	Serial.print(cell->flood_num);
            }
            else
            {
            	Serial.print(cell->flood_num);
            }
        }
        Serial.print("\n");
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
}*/


void say_hello()
{
    Serial.println("Hello");
}

// Micromouse.ino
void setup() 
{
	//Start a serial with 115200 baud rate
	Serial.begin(115200);

    timer_init_us(1000000, say_hello);
}

uint8_t trig = 0;
uint8_t echo = 1;

void loop() 
{ 
    /*struct nav_cell cells[3*6];
    struct nav_array nav;
    pos_t pos;
    
    nav.cells = cells;
    nav.rows = 6;
    nav.columns = 3;
    
    nav_init(&nav);
    
    Serial.print("========================\n");
    load_test_maze_walls(&nav, &pos);
    nav_flood(&nav, &pos);
    print_nav(&nav);
    
    Serial.print("========================\n");

    delay(10000);*/
}