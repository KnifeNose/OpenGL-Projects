#ifndef BALLS_H
#define BALLS_H
class Balls
{
public:
	void drawCircle(float circleX, float CricelY, float circleRadius, int numOfSeg);

	void ballMotion();

	void addForce(float x, float y);

	void addGravity(float y);

	void waterResistance();

	void randomMass();

	void resetAcceleration();

	void startingPos(float startX, float startY);

	float circlePosX = 0;
	float circlePosY = 0;
	float circleVelocityX = 0;
	float circleVelocityY = 0;
	float circleAccelerationX = 0;
	float circleAccelerationY = 0;
	float circleForceX = 0;
	float circleForceY = 0;
	float circleMass = 0;
	float circleRadius = 0;
	float resistanceForceX = 0;
	float resistanceForceY = 0;


};




#endif
