#include "Water.h"
#include <GLFW/glfw3.h>
#include "Balls.h"


void Water::drawWater(float x, float y, float width, float height)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void Water::waterCollision()
{
	
}
