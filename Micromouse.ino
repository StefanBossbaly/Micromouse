#include "nav.h"
#include "queue.h"
#include "position.h"
#include "timer.h"
#include "Adafruit_MotorShield.h"
#include "detection.h"

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


volatile int s0 = -1, s1 = -1, s2 = -1, s3 = -1, s4 = -1;

// Forward = 1
// Adjust Left = 2
// Adjust Right = 3
volatile int motor = -1;


void calculate_motors()
{
    if (s1 > 240)
    {
        motor = 0;
    }
    // Both sensors are good!
    else if (s0 > 90 && s2 > 40)
    {
        int sub = s0 - 40 - s2;

        if (sub > 10)
        {
            motor = 2;
        }
        else if (sub < -10)
        {
            motor = 3;
        }
        else
        {
            motor = 1;
        }
    }
    // We can only use s0
    else if (s0 > 90)
    {
        if (s0 > 145)
        {
            motor = 2;
        }
        else if (s0 < 135)
        {
            motor = 3;
        }
        else
        {
            motor = 1;
        }
    }
    // We can only use s2
    else if (s2 > 40)
    {
        if (s2 > 110)
        {
            motor = 3;
        }
        else if (s2 < 100)
        {
            motor = 2;
        }
        else
        {
            motor = 1;
        }
    }
    else
    {
        motor = 0;
    }
}

void handle_sensors (void)
{
    /*s0 = analogRead(A0);
    s1 = analogRead(A1);
    s2 = analogRead(A2);
    s3 = analogRead(A3);
    s4 = analogRead(A5);

    Serial.print("S0: ");
    Serial.println(s0);
    Serial.print("S1: ");
    Serial.println(s1);
    Serial.print("S2: ");
    Serial.println(s2);
    Serial.print("S3: ");
    Serial.println(s3);
    Serial.print("S4: ");
    Serial.println(s4);*/

    for (int i = 0; i < 6; i++)
    {
        Serial.print(i);
        Serial.print(":");
        Serial.println(analogRead(i));
    }

    //calculate_motors();
    /*unsigned long delta = millis() - start_time;
    Serial.println(delta);

    start_time = millis();*/
}

int on_off = 0;

// Micromouse.ino
void setup() 
{
	// Triggers for relays
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    // Start a serial with 115200 baud rate
    Serial.begin(115200);

    // Start the pwm
    //AFMS.begin(1000);

    //handle_sensors();

    // Start a callback to the sensors
    //timer2_init_ms(500, handle_sensors);
    //start_time = millis();
}

void loop() 
{
	Serial.println(dectection_relay_position());
	on_off = (on_off + 1) % 2;
	
	if (on_off == 0)
	{
		dectection_switch_relay(3);
	}
	else
	{
		dectection_switch_relay(4);
	}
	
	Serial.println(dectection_relay_position());
	
    delay(2000);
}
