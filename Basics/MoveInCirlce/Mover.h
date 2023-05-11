#ifndef MOVER_H
#define MOVER_H

class Mover
{
public:
	void drawCircle(float circleX, float circleY, float circleRadius, int numOfSeg);

	void drawLine(float x1, float y1, float x2, float y2);

	void circleMove();

	void resetAcceleration();


	float r = 0.5f;
	float a = 0.0f;
	float circleX = 0.0f;
	float circleY = 0.0f;
	float aVelocity = 0.0f;
	float aAcceleration = 0.01f;



};



#endif // !MOVER_H
