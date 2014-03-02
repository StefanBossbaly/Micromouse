#include "nav.h"
#include "queue.h"
#include "position.h"
#include "motor.h"
#include "timer.h"
#include "stepper.h"
#include "detection.h"

volatile unsigned long start_time = 0;

// Motor shield and stepper motors
shield_t shield;
stepper_t motor0, motor1;

// Our empty maze
struct nav_cell cells[3*6];
struct nav_array array;

// Current position
pos_t current;

int stop = 0;
int blah = 0;

void print_maze(struct nav_array *array)
{
	int i, j;
	for (i = 0; i < array->rows; i++)
	{
		for (j = 0; j < array->columns; j++)
		{
			struct nav_cell *cell = nav_get_cell(array, i, j);
			
			Serial.print("(");
			Serial.print(cell->row);
			Serial.print(",");
			Serial.print(cell->column);
			Serial.print(") ");
		}
		
		Serial.println("");
	}
}

void callback(void)
{
	int s0 = dectection_reading(0);
	int s2 = dectection_reading(2);
	
	Serial.println("");
	Serial.print(s0);
	Serial.print(",");
	Serial.print(s2);
	Serial.println("");
}

// Micromouse.ino
void setup() 
{
	// Triggers for relays
    pinMode(S3_TRIG, OUTPUT);
    pinMode(S4_TRIG, OUTPUT);
    
    // Start a serial with 115200 baud rate
    Serial.begin(115200);
    
    // Motor shield is at i2c address of 0x60
    shield_init(&shield, 0x60);
    
    // Begin the pwm at a frequency of 1600
    shield_begin(&shield, 1600);
    
    // Init our steppers
    stepper_init(&motor0, &shield, 0);
    stepper_init(&motor1, &shield, 1);
    
    // Give the stepper to our motor functions
    motor_init(&motor0, &motor1);
    
    // Init shared motor values
    motor_status = MOTOR_STANDBY;
    motor_adjustment = MOTOR_NO_ADJ;
    
    // Init our empty maze
    nav_init(&array, cells, 6, 3);
    
    // Setup our position
    current.row = 5;
    current.column = 2;
    current.direction = north;
    
    nav_update_wall(&array, &current, left);
    nav_update_wall(&array, &current, right);
    
    current.direction = west;
    
    // Get inital sensor values
    dectection_force_update();

    // Start a callback to the sensors
    timer2_init_ms(150, dectection_timer_callback);
    start_time = millis();
}

void loop() 
{
	//delay(4000);
	if (blah == 0)
	{
		print_maze(&array);
		//nav_explore(&array, &current);
	}
	
	blah = 1;
}
