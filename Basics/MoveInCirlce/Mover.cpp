#include "Mover.h"
#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;


void Mover::drawCircle(float circleX, float circleY, float circleRadius, int numOfSeg)
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

void Mover::drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void Mover::circleMove()
{
    circleX = r * cos(a);
    circleY = r * sin(a);

    a += aVelocity;
    aVelocity += aAcceleration;

}

void Mover::resetAcceleration()
{
    aAcceleration *= 0.0f;
}

