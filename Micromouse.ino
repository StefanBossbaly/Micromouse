#include "nav.h"
#include "queue.h"
#include "position.h"
#include "motor.h"
#include "timer.h"
#include "stepper.h"
#include "detection.h"
#include "inttypes.h"

volatile unsigned long start_time = 0;

// Motor shield and stepper motors
shield_t shield;
stepper_t motor0, motor1;

// Our empty maze
struct nav_cell cells[16 * 16];
struct nav_array array;

// Starting postion
pos_t start;

// Current position
pos_t current;

// Target position
pos_t target;

void print_pos(pos_t *position) {
	Serial.print("(");
	Serial.print(position->row);
	Serial.print(", ");
	Serial.print(position->column);
	Serial.print(")");
	Serial.println("");
}

uint8_t calibrate(struct nav_array *nav, pos_t *pos) {
	uint8_t wall = 0;
	struct nav_cell *cell = nav_get_cell_pos(nav, pos);

	// See if we can calibrate
	if (pos->direction == north && nav_north_wall(cell)) {
		wall = 1;
	} else if (pos->direction == east && nav_east_wall(cell)) {
		wall = 1;
	} else if (pos->direction == south && nav_south_wall(cell)) {
		wall = 1;
	} else if (pos->direction == west && nav_west_wall(cell)) {
		wall = 1;
	}
	
	if (wall == 1){
		int reading = dectection_reading(1);
		
		while (reading > 205 || reading < 195)
		{
			if (reading > 205)
			{
				stepper_step(&motor0, BACKWARD);
				stepper_step(&motor1, BACKWARD);
			}
			else
			{
				stepper_step(&motor0, FORWARD);
				stepper_step(&motor1, FORWARD);
			}
			
			delay(5);
			reading = dectection_reading(1);
		}
		
		return 1;
	}
	
	return 0;
}

void print_maze(struct nav_array *array) {
	int i, j;
	for (i = 0; i < array->rows; i++) {
		for (j = 0; j < array->columns; j++) {
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

void print_flood(struct nav_array *array) {
	int i, j;
	for (i = 0; i < array->rows; i++) {
		for (j = 0; j < array->columns; j++) {
			struct nav_cell *cell = nav_get_cell(array, i, j);

			if (cell->flood_num < 10) {
				Serial.print("0");
			}

			Serial.print(cell->flood_num);
			Serial.print(" ");
		}

		Serial.println("");
	}
}

void callback(void) {
	dectection_timer_callback();

	if (motor_adj_status == MOTOR_EXP_COR) {
		Serial.println("");
		Serial.print(motor_correction);
		if (motor_correction_dir == MOTOR_ADJ_LEFT) {
			Serial.println(" left");
		} else if (motor_correction_dir == MOTOR_ADJ_RIGHT) {
			Serial.println(" right");
		}

		Serial.println("");
	}
}

// Micromouse.ino
void setup() {
	delay(5000);

	Serial.println("setup() called");

	// Triggers for relays
	pinMode(S3, INPUT);
	pinMode(S4, INPUT);

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
	motor_adj_status = MOTOR_NO_ADJ;
	
	// Set the starting position
	start.row = 0;
	start.column = 0;
	start.direction = east;

	// Setup our position
	current.row = 0;
	current.column = 0;
	current.direction = east;
	
	//TODO pick a target
	target.row = 7;
	target.column = 7;
	
	// Start a callback to the sensors
	timer2_init_ms(150, dectection_timer_callback);
	start_time = millis();

	Serial.println("setup() complete");
}

void loop() {
	Serial.println("loop() called");

	// Init our maze
	nav_init(&array, cells, 16, 16);
	
	// Update the start walls
	nav_update_wall(&array, &current, left);
	nav_update_wall(&array, &current, right);
	
	// We are at the starting postion
	struct nav_cell *current_cell = nav_get_cell(&array, current.row, current.column);
	current_cell->has_explored = 1;
	
	// While we are not at the target location
	while (!position_equal_location(&current, &target))
	{	
		// Flood the maze starting with the target
		nav_flood(&array, &target);
		
		// Get the neighbor cell that has current - 1
		struct nav_cell *cell = nav_get_next_neighbor(&array, current.row, current.column);
		
		// Mark the current cell as explored
		cell->has_explored = 1;
		
		// Turn towards the new cell
		dir_t direction = position_get_direction_to(&current, cell->row, cell->column);
		motor_turn_to_direction(&current, direction);
		current.direction = direction;
		
		// Move forward
		motor_move_forward();
		position_move_forward(&current);
		
		// Update walls
		detection_update_walls(&array, &current);
		detection_update_front_wall(&array, &current);
	}
	
	// Ok we are at the target now flood back to the starting position
	while (!position_equal_location(&current, &start))
	{
		// Flood the maze starting with the start
		nav_flood(&array, &start);
		
		// Get the neighbor cell that has current - 1
		struct nav_cell *cell = nav_get_next_neighbor(&array, current.row, current.column);
		
		// Mark the current cell as explored
		cell->has_explored = 1;
				
		// Turn towards the new cell
		dir_t direction = position_get_direction_to(&current, cell->row, cell->column);
		motor_turn_to_direction(&current, direction);
		current.direction = direction;
				
		// Move forward
		motor_move_forward();
		position_move_forward(&current);
				
		// Update walls
		detection_update_walls(&array, &current);
		detection_update_front_wall(&array, &current);
	}
	
	//insert walls around all unexplored cells
	for (int8_t i = 0; i < array.rows; i++)
	{
		for (int8_t j = 0; j < array.columns; j++)
		{
			struct nav_cell *cell = nav_get_cell(&array, i, j);
			
			if (cell->has_explored != 1)
			{
				nav_update_wall_cell(cell, north);
				nav_update_wall_cell(cell, south);
				nav_update_wall_cell(cell, east);
				nav_update_wall_cell(cell, west);
			}
		}
	}
	
	// We are at the start position
	nav_flood(&array, &target);
	
	//"smart" move to target using all of the known wall locations
	nav_drive_to_target(&array, &current, &target);
	
	//victory dance :D
	motor_turn_180();
	motor_turn_180();
	motor_turn_180();
	motor_turn_180();
	
	delay(10000);
	
	
}
