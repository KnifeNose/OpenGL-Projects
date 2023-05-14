#include "Particle.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include <ctime>
#include "ParticleSystem.h"

const float PI = 3.14159265358979323846f;

float gravity[2] = { 0.0f, -0.00023f };

Particle::Particle()
	:mass(1.0f), damping(0.98f), isFirstFrame(true)
{
	position[0] = 0.0f;
	position[1] = 0.0f;
	velocity[0] = 0.0f;
	velocity[1] = 0.0f;
	acceleration[0] = 0.0f;
	acceleration[1] = 0.0f;

	health = 1.0f;
}

void Particle::drawCircle(float centerX, float centerY, float radius, int numOfSeg)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX, centerY);
	for (int i = 0; i <= numOfSeg; i++)
	{
		float angle = i * (2.0f * PI / numOfSeg);
		glVertex2f(centerX + radius * std::cos(angle), centerY + radius * std::sin(angle));
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
}

void Particle::addForce(float force[2])
{
	float f[2] = { force[0] / mass, force[1] / mass };
	acceleration[0] += f[0];
	acceleration[1] += f[1];
}

void Particle::startFunc(float x, float y)
{
	position[0] = x;
	position[1] = y;

	isFirstFrame = false;
}

void Particle::color()
{
	health -= 0.008f;
	glColor4f(0.9f, 0.9f, 1.0f, health);
}

void Particle::enableGravity()
{
	addForce(gravity);
}
