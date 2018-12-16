/*
 * S3DRServoMotor.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: tutu
 */

#include "S3DRServoMotor.h"
#include "S3DRMotor_calcul.h"

S3DRServoMotor::S3DRServoMotor(uint8_t rpm,uint8_t restPos):Servo()
{
	m_RPM = rpm;
	m_RestPos = restPos;
}

S3DRServoMotor::~S3DRServoMotor()
{
}

float S3DRServoMotor::timeToTurn(float nbrRound)
{
	float time = nbrRound * 60 / m_RPM;
	Serial.print("time:");
	Serial.println(time);
	return time;
}

void S3DRServoMotor::run(eDirection dir)
{
	switch(dir){
	case BACKWARD:
		this->write(0);
		break;
	case RELEASE:
		this->write(m_RestPos);
		break;
	case FORWARD:
		this->write(180);
		break;
	}
}
