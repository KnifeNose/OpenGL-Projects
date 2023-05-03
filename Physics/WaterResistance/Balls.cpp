#include "Balls.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include <ctime>

const float PI = 3.14159265358979323846f;

unsigned seed = static_cast<unsigned>(std::time(nullptr));
std::mt19937 gen(seed);
std::uniform_real_distribution<> dist(0.09f, 0.99f);

void Balls::drawCircle(float circleX, float circleY, float circleRadius, int numOfSeg)
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

void Balls::ballMotion()
{
    circlePosX += circleVelocityX;
    circlePosY += circleVelocityY;
    circleVelocityX += circleAccelerationX;
    circleVelocityY += circleAccelerationY;
}

void Balls::addForce(float x, float y)
{
    circleForceX = x / circleMass;
    circleForceY = y / circleMass;
    circleAccelerationX += circleForceX;
    circleAccelerationY += circleForceY;
}

void Balls::addGravity(float y)
{
    circleAccelerationY += y;
}

void Balls::randomMass()
{
    circleMass = dist(gen);
    circleRadius = circleMass / 6;
}

void Balls::startingPos(float startX, float startY)
{
    circlePosX = startX;
    circlePosY = startY;
}

void Balls::waterResistance()
{
    resistanceForceX = circleVelocityX;
    resistanceForceY = circleVelocityY;
    resistanceForceX = resistanceForceX * -2000 * circleVelocityX * circleVelocityX;
    resistanceForceY = resistanceForceY * -2000 * circleVelocityY * circleVelocityY;
    addForce(resistanceForceX, resistanceForceY);

}

void Balls::resetAcceleration()
{
    circleAccelerationX *= 0;
    circleAccelerationY *= 0;
}
