/* Code Written by Roy Pe'er. I've explained all the code in the grey comments.
I recommend you to go over the code, examine it, play with it, improve it and modify it according to your needs. 
For more awesome videos, subsrice to my channel:
http://www.youtube.com/subscription_center?add_user=Roypeer1
*/
#include <S3DRServoMotor.h> //import your motor shield library
#include "Arduino.h"
#include <S3DRMotor_calcul.h>

#define trigPin 12 // define the pins of your sensor
#define echoPin 13
uint8_t wheelDiam = 10;
uint8_t width = 20;
uint8_t angle = 0;
bool leftBlocked = false;
bool rightBlocked = false;
S3DRServoMotor motor1(45, 98); // left front.
S3DRServoMotor motor2(45, 92); // left back
S3DRServoMotor motor3(45, 92); // right front.
S3DRServoMotor motor4(45, 92); // right back.
static void turnLeft(uint8_t angle);
static void turnRight(uint8_t angle);
static void goForward();
static void goBackwardAndTurnRight(uint8_t angle);
static void goBackwardAndTurnLeft(uint8_t angle);
static void goBackward();
static void stop();

void setup()
{
	Serial.begin(9600); // begin serial communitication
	Serial.println("Motor test!");
	pinMode(trigPin, OUTPUT); // set the trig pin to output (Send sound waves)
	pinMode(echoPin, INPUT);  // set the echo pin to input (recieve sound waves)
	motor1.attach(11);		  //set the speed of the motors, between 0-255
	motor2.attach(10);
	motor3.attach(6);
	motor4.attach(9);
}

void loop()
{
	long duration, echodistance; // start the scan
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2); // delays are required for a successful sensor operation.
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10); //this delay is required as well!
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	echodistance = (duration / 2) / 29.1; // convert the distance to centimeters.
	goForward();
	if (echodistance < 25)
	{
		if (!leftBlocked)
		{
			if (/*echodistance < 25 ||*/ angle <= 60) /*if there's an obstacle 25 centimeters, ahead, do the following: */
			{
				angle += 10;
				turnLeft(10);
				//stop();
				//delay(2000);
			}
			else if (/*echodistance < 25 ||*/ angle > 60)
			{
				Serial.println("Left blocked!");
				goBackwardAndTurnLeft(60);
				leftBlocked = true;
				angle = 0;
				//stop();
				//delay(2000);
			}
			else
			{
				Serial.println("Found new way!");
				//goForward();
			}
		}
		else if (!rightBlocked)
		{
			if (/*echodistance < 25 ||*/ angle <= 60) /*if there's an obstacle 25 centimers, ahead, do the following: */
			{
				angle += 10;
				turnRight(10);
				//stop();
			}
			else if (/*echodistance < 25 ||*/ angle > 60)
			{
				Serial.println("Right blocked");
				goBackwardAndTurnRight(60);
				//stop();
				//delay(2000);
				rightBlocked = true;
				angle = 0;
			}
			else
			{
				Serial.println("Found new way!!");
				//goForward();
			}
		}
		else if (leftBlocked && rightBlocked)
		{
			Serial.println("Both sided blocked!");
			goBackward();
			delay(5000);
			//stop();
			//delay(2000);
			turnLeft(60);
			//delay(2000);
			leftBlocked = false;
			rightBlocked = false;
		}
	}
	else
	{
		if (leftBlocked)
			leftBlocked = false;
		if (rightBlocked)
			rightBlocked = false;
	}
}

static void turnLeft(uint8_t angle)
{
	Serial.println("Turn left");
	float nbrToTurn;
	nbrToTurn = angleToNumberTurn(angle, width, wheelDiam);
	Serial.print("Nbr Round:");
	Serial.println(nbrToTurn);
	float timeSec = motor2.timeToTurn(nbrToTurn);
	Serial.println(timeSec);
	motor3.run(FORWARD);
	motor4.run(FORWARD);
	motor1.run(RELEASE);
	motor2.run(RELEASE);
	delay(timeSec * 1000);
	motor3.run(RELEASE);
	motor4.run(RELEASE);
}

static void turnRight(uint8_t angle)
{
	Serial.println("Turn right");
	float nbrToTurn;
	nbrToTurn = angleToNumberTurn(angle, width, wheelDiam);
	float timeSec = motor1.timeToTurn(nbrToTurn);
	Serial.println(timeSec);
	motor1.run(FORWARD);
	motor2.run(FORWARD);
	motor3.run(RELEASE);
	motor4.run(RELEASE);
	delay(timeSec * 1000);
	motor1.run(RELEASE);
	motor2.run(RELEASE);
}

static void goBackwardAndTurnRight(uint8_t angle)
{
	Serial.println("go back and turn right");
	float nbrToTurn;
	nbrToTurn = angleToNumberTurn(angle, width, wheelDiam);
	float timeSec = motor2.timeToTurn(nbrToTurn);
	Serial.println(timeSec);
	motor1.run(BACKWARD);
	motor2.run(BACKWARD);
	motor3.run(RELEASE);
	motor4.run(RELEASE);
	delay(timeSec * 1000);
	motor1.run(RELEASE);
	motor2.run(RELEASE);
}

static void goBackwardAndTurnLeft(uint8_t angle)
{
	Serial.println("Go back and turn left");
	float nbrToTurn;
	nbrToTurn = angleToNumberTurn(angle, width, wheelDiam);
	float timeSec = motor1.timeToTurn(nbrToTurn);
	Serial.println(timeSec);
	motor3.run(BACKWARD);
	motor4.run(BACKWARD);
	motor2.run(RELEASE);
	motor1.run(RELEASE);
	delay(timeSec * 1000);
	motor3.run(RELEASE);
	motor4.run(RELEASE);
}

static void goForward()
{
	motor1.run(FORWARD);
	motor2.run(FORWARD);
	motor3.run(FORWARD);
	motor4.run(FORWARD);
}

static void goBackward()
{
	Serial.println("Go back");
	motor1.run(BACKWARD);
	motor2.run(BACKWARD);
	motor3.run(BACKWARD);
	motor4.run(BACKWARD);
}

static void stop()
{
	Serial.println("stop");
	motor1.run(RELEASE);
	motor2.run(RELEASE);
	motor3.run(RELEASE);
	motor4.run(RELEASE);
}
