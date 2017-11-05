#include <Arduino.h>
#include "roomba.h"

/***********************************************
**											  **
**    Ultrasonic Sensor Variables/Functions   **
**											  **
***********************************************/
// Pins for the ultrasonic sensor
int trigPin = 12;
int echoPin = 13;
// Current distance reading
int distance;
// Distance threshold to initiate turn (in cm)
int turn_distance = 40;
// Time for echo to return
long duration;

// Get current distance to closest object (in cm)
int get_distance() {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	duration = pulseIn(echoPin, HIGH);

	distance = duration*0.034/2;

	Serial.print("Distance: ");
	Serial.println(distance);

	return distance;
}
/*											        -   (6)  -------------  (5)   -
											       |0|       |           |       |1|
************************************************    -   (7)  -           -  (4)   -
**											  **             -           -
**       Wheel/Motor Variables/Functions      ** 	      	-           -
**											  **    -   (3)  -           -  (9)   -
************************************************   |2|       |           |       |3|
                                                    -   (2)  -------------  (8)   -
*/

//****** WHEEL SPINS FROM LOW->HIGH ******//

// Wheel group 0: Pins 6/7
// Wheel group 1: Pins 4/5
// Wheel group 2: Pins 2/3
// Wheel group 3: Pins 8/9 

int turn_delay = 3000; // Time to initiate turn for (in ms)

/* Turn 90 degrees to the left. 
 * Reverse wheel group 0 and 2,
 * Push wheel group 1 and 3 high. */

void turn_left() {
  // Reverse group 0
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);

  // Reverse group 2
  digitalWrite(3, LOW);
  digitalWrite(2, HIGH);

  // Keep groups 1 and 3 going straight
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);

  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);

  delay(turn_delay);
}

void turn_right() {
  // Reverse group 1
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);

  // Reverse group 3
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);

  // Keep groups 0 and 2 going straight
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);

  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);

  delay(turn_delay);
}

void setup() {
	// Sensor pins
	pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(echoPin, INPUT); // Sets the echoPin as an Input
	Serial.begin(9600); // Starts the serial communication

	// Wheel pins
	pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
}
void loop() {

  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);

  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);

  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);

  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);

	int rand = random(0, 2);
	distance = get_distance();
	Serial.println(distance);
	if (distance < turn_distance) {
		if (rand == 0) {
			turn_left();
		}
		else {
			turn_right();
		}
	}	
}