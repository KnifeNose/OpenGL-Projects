#include "Particle.h"
#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

float damping = 0.99f;

float gravity[2] = { 0.0f, -0.00023f };

Particle::Particle()
{
	position[0] = 0;
	position[1] = 0;
	velocity[0] = 0.0f;
	velocity[1] = 0.0f;
	acceleration[0] = 0.0f;
	acceleration[1] = 0.0f;
	isFirstFrame = true;

	health = 1.0f;
}


void Particle::drawShape(float x, float y, float radius, int numOfSeg)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= numOfSeg; i++)
	{
		float angle = i * (2.0f * PI) / numOfSeg;
		glVertex2f(x + radius * std::cos(angle), y + radius * std::sin(angle));
	}
	glEnd();
}

void Particle::motion()
{
	velocity[0] *= damping;
	velocity[1] *= damping;

	velocity[0] += acceleration[0];
	velocity[1] += acceleration[1];
	position[0] += velocity[0];
	position[1] += velocity[1];

	acceleration[0] *= 0.0f;
	acceleration[1] *= 0.0f;

	health = health - 0.02f;
}

void Particle::addForce(float force[2])
{
	acceleration[0] += force[0];
	acceleration[1] += force[1];
}

void Particle::addGravity()
{
	addForce(gravity);
}

void Particle::startPos(float x, float y)
{
	position[0] = x;
	position[1] = y;
	isFirstFrame = false;
}

void SquareParticle::drawShape(float x1, float y1, float height, float width)
{
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x1 + height, y1);
	glVertex2f(x1 + height, y1 + width);
	glVertex2f(x1, y1 + width);
	glEnd();
}
