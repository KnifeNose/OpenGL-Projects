#include "Particle.h"
#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

const float damping = 0.99f;

float gravity[2] = { 0.0f, -0.00036f };

Particle::Particle()
{
	position[0] = 0.0f;
	position[1] = 0.0f;
	velocity[0] = 0.0f;
	velocity[1] = 0.0f;
	acceleration[0] = 0.0f;
	acceleration[1] = 0.0f;

	isFirstFrame = true;
}


void Particle::drawShape(float x, float y, float radius, int seg)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= seg; i++)
	{
		float angle = i * (2.0f * PI) / seg;
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

	drawShape(position[0], position[1], 0.01f, 32);
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


SParticle::SParticle()
{
	position[0] = 0.0f;
	position[1] = 0.0f;
	velocity[0] = 0.0f;
	velocity[1] = 0.0f;
	acceleration[0] = 0.0f;
	acceleration[1] = 0.0f;

	isFirstFrame = true;
}

void SParticle::drawShape(float x, float y, float widthandheight)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y + widthandheight);
	glVertex2f(x + widthandheight, y + widthandheight);
	glVertex2f(x + widthandheight, y);
	glEnd();
}

void SParticle::motion()
{
	velocity[0] *= damping;
	velocity[1] *= damping;

	velocity[0] += acceleration[0];
	velocity[1] += acceleration[1];
	position[0] += velocity[0];
	position[1] += velocity[1];

	acceleration[0] *= 0.0f;
	acceleration[1] *= 0.0f;

	drawShape(position[0], position[1], 0.1f);
}
