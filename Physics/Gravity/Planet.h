#ifndef PLANET_H
#define PLANET_H

#include "Sun.h"
class Planet
{
public:

	void drawPlanet(float circleX, float circleY, float circleRadius, int numOfSeg);

	void motion();

	void addForce(float x, float y);

	void addGravity(Sun &sun);

	void startPos(float x, float y);


	float planetCenterX = 0;
	float planetCenterY = 0;
	float planetVelocityX = 0;
	float planetVelocityY = 0;
	float planetAccelerationX = 0;
	float planetAccelerationY = 0;
	float planetMass = 0.8f;
	float planetForceX = 0;
	float planetForceY = 0;

};



#endif
