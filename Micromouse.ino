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

// Micromouse.ino
void setup() 
{
	// Triggers for relays
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    // Start a serial with 115200 baud rate
    Serial.begin(115200);
    
    // Motor shield is at i2c address of 0x60
    shield_init(&shield, 0x60);
    
    // Begin the pwm at a frequency of 1600
    shield_begin(&shield, 1600);
    
    // Init our steppers
    stepper_init(&motor0, &shield, 0);
    stepper_init(&motor1, &shield, 1);
    
    // Init shared motor values
    motor_status = MOTOR_STANDBY;
    motor_adjustment = MOTOR_NO_ADJ;
    
    // Init our empty maze
    nav_init(&array, 3, 6);
    
    // Setup our position
    current.row = 0;
    current.column = 0;
    current.direction = west;
    
    // Get inital sensor values
    dectection_force_update();

    // Start a callback to the sensors
    timer2_init_ms(150, dectection_timer_callback);
    start_time = millis();
}

void loop() 
{
	if (blah == 0)
	{
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_180(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_left(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_left(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		motor_turn_right(&motor0, &motor1);
		motor_move_forward(&motor0, &motor1);
		
	}
	
	blah = 1;
	
}
