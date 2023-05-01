#include "Rect.h"
#include <GLFW/glfw3.h>

void Rect::drawRect(float x, float y, float width, float height, float speed)
{
	float angle = (float)glfwGetTime() * speed;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void Rect::startPos(float x, float y)
{
	posX = x;
	posY = y;
}
