#include "Box.h"
#include <GLFW/glfw3.h>

// Draw box
void Box::drawBox(float x, float y, float width, float height)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

// Motion
void Box::motion()
{
	posX += rectVelocityX;
	posY = -0.5f;
	rectVelocityX += rectAccelerationX;
}

// Add a force
void Box::addForce(float x)
{
	rectAccelerationX += x;
}

// Apply friction 
void Box::addFriction()
{
	if (posX > -0.4f && posX < 0.5f)
	{
		frictionValue = -0.00000006f;
		rectAccelerationX += frictionValue;
	}
}
