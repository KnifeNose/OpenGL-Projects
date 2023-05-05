#include "Pendulum.h"
#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

void Pendulum::drawCircle(float centerX, float centerY, float radius, int numOfSeg)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX, centerY);
    for (int i = 0; i <= numOfSeg; i++)
    {
        float angle = i * 2.0f * PI / numOfSeg;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void Pendulum::drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void Pendulum::addMotion()
{
    float force = gravity * sin(angle);

    angleA += force;

    angleV += angleA;
    angle += angleV;
    angleV *= damping;

    circleX = armLength * sin(angle) + originX;
    circleY = armLength * cos(angle) + originY;
}


void Pendulum::resetAcceleration()
{
    angleA *= 0;
}

void Pendulum::setAngle()
{
    angle = PI / 2;
}
