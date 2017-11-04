#include <Arduino.h>
#include "roomba.h"

int trigPin = 3;
int echoPin = 2;
int distance;
long duration;

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
void setup() {
	pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(echoPin, INPUT); // Sets the echoPin as an Input
	Serial.begin(9600); // Starts the serial communication
}
void loop() {

	

}