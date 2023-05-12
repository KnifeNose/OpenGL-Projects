#include "Circles.h"
#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

void Circles::drawCircle(float circleX, float circleY, float circleRadius, int numOfSeg)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(circleX, circleY);
    for (int i = 0; i <= numOfSeg; i++)
    {
        float angle = i * 2.0f * PI / numOfSeg;
        float x = circleX + circleRadius * cos(angle);
        float y = circleY + circleRadius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

}

void Circles::startPos(float x, float y)
{
    circleCenterX = x;
    circleCenterY = y;

}

void Circles::sinMovementX(float a)
{
    angle += a;
    circleCenterY = amplitude * sin(angle);
}

void Circles::startingAngle(float ang)
{
    angle = ang;
}
