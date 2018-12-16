#ifndef DCMOTOR_CALCUL_H
#define DCMOTOR_CALCUL_H

#include <Arduino.h>

static float angleToNumberTurn(uint8_t angle, uint8_t robotWidth, uint8_t wheelDiam)
{
	if (angle > 360 || robotWidth < 0 || wheelDiam < 0){
		return 0;
	}
	float distance = 2 * PI * robotWidth * angle / 360;
	Serial.print("distance:");
	Serial.println(distance);
	Serial.print("wheel Diameter:");
	Serial.println(wheelDiam);
	float nbrTurn = distance / (PI * wheelDiam);
	return nbrTurn;
}

#endif
