#include "Planet.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "Sun.h"

const float PI = 3.14159265358979323846f;


void Planet::drawPlanet(float circleX, float circleY, float circleRadius, int numOfSeg)
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

void Planet::motion()
{
    planetCenterX += planetVelocityX;
    planetCenterY += planetVelocityY;
    planetVelocityX += planetAccelerationX;
    planetVelocityY += planetAccelerationY;
}

void Planet::addForce(float x, float y)
{
    planetForceX += x / planetMass;
    planetForceY += y / planetMass;
    planetAccelerationX += planetForceX;
    planetAccelerationY += planetForceY;
}


void Planet::addGravity(Sun &sun)
{
    float forceX = planetCenterX - sun.circleX;
    float forceY = planetCenterY - sun.circleY;
    float distance = std::sqrt(std::pow(sun.circleX - planetCenterX, 2) + std::pow(sun.circleY - planetCenterY, 2));
    float strength = (-0.00000001f * planetMass * sun.sunMass) / (distance * distance);
    forceX *= strength;
    forceY *= strength;
    planetAccelerationX = 0; // reset acceleration to zero
    planetAccelerationY = 0;
    addForce(forceX, forceY);
}

void Planet::startPos(float x, float y)
{
    planetCenterX = x;
    planetCenterY = y;
}
