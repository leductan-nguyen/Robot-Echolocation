/*
 * S3DRServoMotor.h
 *
 *  Created on: Jun 25, 2016
 *      Author: tutu
 */

#ifndef SRC_S3DRServoMotor_H_
#define SRC_S3DRServoMotor_H_
#include <Servo.h>

typedef enum {
	BACKWARD			=0,
	RELEASE				=1,
	FORWARD				=2
} eDirection;


class S3DRServoMotor: public Servo
{
public:
	S3DRServoMotor(uint8_t rpm, uint8_t restPos);
	virtual ~S3DRServoMotor();
	float timeToTurn(float nbrRound);
	void run(eDirection dir);
	const int  & getRPM() const {return m_RPM;}
protected:
private:
	uint8_t m_RPM;
	uint8_t m_RestPos;
};

#endif /* SRC_S3DRServoMotor_H_ */
