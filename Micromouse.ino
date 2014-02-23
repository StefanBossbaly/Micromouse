#include "nav.h"
#include "queue.h"
#include "position.h"
#include "timer.h"
#include "stepper.h"
#include "detection.h"

volatile unsigned long start_time = 0;
volatile uint8_t stop = 0; 

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

shield_t shield;
stepper_t motor0, motor1;

// Micromouse.ino
void setup() 
{
	// Triggers for relays
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    // Start a serial with 115200 baud rate
    Serial.begin(115200);

    //handle_sensors();

    // Start a callback to the sensors
    //timer2_init_ms(500, handle_sensors);
    //start_time = millis();
    
    shield_init(&shield, 0x60);
    
    shield_begin(&shield, 1600);
    
    stepper_init(&motor0, &shield, 0);
    stepper_init(&motor1, &shield, 1);
}

void loop() 
{
	for (int i = 0; i < 85; i++)
	{
		stepper_step(&motor0, FORWARD);
		stepper_step(&motor1, BACKWARD);
	}
	
	delay(3000);
}
