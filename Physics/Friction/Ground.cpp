#include "Ground.h"
#include <GLFW/glfw3.h>

void Ground::drawGround(float x, float y, float width, float height) 
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

