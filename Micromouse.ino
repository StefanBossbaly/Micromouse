#include "nav.h"
#include "queue.h"
#include "position.h"
#include "timer.h"
#include "Adafruit_MotorShield.h"

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

volatile unsigned long start_time = 0;
volatile uint8_t stop = 0; 

Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(200, 1);

void handle_sensors (void)
{
    Serial.print("S0: ");
    Serial.println(analogRead(0));
    Serial.print("S1: "); 
    Serial.println(analogRead(1));
    Serial.print("S2: "); 
    Serial.println(analogRead(2));


    unsigned long delta = millis() - start_time;
    Serial.println(delta);

    start_time = millis();
}


// Micromouse.ino
void setup() 
{
	// Start a serial with 115200 baud rate
	Serial.begin(115200);

    // Start the pwm
    AFMS.begin(1000);

    // Start a callback to the sensors
    timer_init_ms(500, handle_sensors);
    start_time = millis();
}

void loop() 
{
}