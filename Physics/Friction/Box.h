#ifndef BOX_H
#define BOX_H

class Box
{
public:
	void drawBox(float x, float y, float width, float height);

	void motion();
	
	void addForce(float x);

	void addFriction();

	float posX = -1;
	float posY = -0.5f;
	float rectVelocityX = 0;
	float rectVelocityY = 0;
	float rectAccelerationX = 0;
	float rectAccelerationY = 0;
	float frictionValue = 0;



};

#endif
