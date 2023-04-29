#include <GLFW/glfw3.h>
#include <cmath>
#include "Movers.h"
#include <random>
#include <ctime>

unsigned seed = static_cast<unsigned>(std::time(nullptr));
std::mt19937 gen(seed);
std::uniform_real_distribution<> dist(-0.8f, 0.8f);
std::uniform_real_distribution<> dist2(0.1f, 0.2f);

const float PI = 3.14159265358979323846f;

// Draw circle
void Movers::drawCircle(float circleCenterX, float circleCenterY, float circleRadius, int numOfSegments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circleCenterX, circleCenterY);
    for (int i = 0; i <= numOfSegments; i++)
    {
        float angle = i * 2.0f * PI / numOfSegments;
        float x = circleCenterX + circleRadius * cos(angle);
        float y = circleCenterY + circleRadius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void Movers::addMotion()
{
    circleCenterX += circleVelocityX;
    circleCenterY += circleVelocityY;
    circleVelocityX += circleAccelerationX;
    circleVelocityY += circleAccelerationY;
}

void Movers::addForce(float x, float y)
{
    forceX = x;
    forceY = y;

    forceMass = mass * 10;

    forceX = forceX / forceMass;
    forceY = forceY / forceMass;

circleAccelerationX += forceX;
circleAccelerationY += forceY;
}

void Movers::resetAcceleration()
{
    circleAccelerationX *= 0;
    circleAccelerationY *= 0;
}

void Movers::collision()
{
    if (circleCenterX + circleRadius > 1)
    {
        circleVelocityX *= -1;
    }
    else if (circleCenterX - circleRadius < -1)
    {
        circleVelocityX *= -1;
    }
    else if (circleCenterY - circleRadius < -1)
    {
        circleVelocityY *= -1;
    }
}

// Give the circles a random starting position and a random mass
void Movers::startingPos()
{
    circleCenterX = dist(gen);
    mass = dist2(gen);
    circleRadius = mass;
}

void Movers::limitSpeed(float limit)
{
    if (circleVelocityX > limit) 
    {
        circleVelocityX = limit;
    }
    if (circleVelocityX < limit * -1)
    {
        circleVelocityX = limit * -1;
    }
    if (circleVelocityY > limit)
    {
        circleVelocityY = limit;
    }
    if (circleVelocityY < limit * -1)
    {
        circleVelocityY = limit * -1;
    }
}
