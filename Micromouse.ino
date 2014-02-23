#include "nav.h"
#include "queue.h"
#include "position.h"
#include "motor.h"
#include "timer.h"
#include "stepper.h"
#include "detection.h"


volatile unsigned long start_time = 0;
volatile uint8_t stop = 0; 

volatile int s0 = -1, s1 = -1, s2 = -1, s3 = -1, s4 = -1;

shield_t shield;
stepper_t motor0, motor1;


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
    s0 = dectection_reading(0);
    s1 = dectection_reading(1);
    s2 = dectection_reading(2);
    s3 = dectection_reading(3);
    s4 = dectection_reading(4);
    
    Serial.println("");
    Serial.print(s0);
    Serial.print(", ");
    Serial.print(s1);
	Serial.print(", ");
	Serial.print(s2);
	Serial.print(", ");
	Serial.print(s3);
	Serial.print(", ");
	Serial.print(s4);
	Serial.println("");
}

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
    
    // Get inital sensor values
    //handle_sensors();

    // Start a callback to the sensors
    //timer2_init_ms(1000, handle_sensors);
    //start_time = millis();
}

void loop() 
{
	motor_turn_180(&motor0, &motor1);
	
	delay(3000);
}
