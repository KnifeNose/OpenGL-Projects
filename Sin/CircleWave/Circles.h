#ifndef CIRCLES_H
#define CIRCLES_H
class Circles
{
public:

	void drawCircle(float circleX, float circleY, float circleRadius, int numOfSeg);
	
	void startPos(float x, float y);

	void sinMovementX(float a);

	void startingAngle(float ang);

	float circleCenterX = 0.0f;
	float circleCenterY = 0.0f;
	
	float amplitude = 1.0f;
	float angle = 0.0f;


};



#endif
