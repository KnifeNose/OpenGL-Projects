#include "Particle.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include <ctime>

// PI
const float PI = 3.14159265358979323846f;

float damping = 0.99f;
// Force up
float rising[2] = { 0.0f, 0.00002f };

//create a unsigned variable that gives a number that chages each second

unsigned seed = static_cast<unsigned>(std::time(nullptr));

// returns a random number using the seed so generate different random numbers

std::mt19937 gen(seed);

// use gen(dist) to generate a random number between the numbers defined in dist()

std::uniform_real_distribution<> dist(-0.0007f, 0.0007f);

// Particle constructor 
Particle::Particle()
{
	position[0] = 0.0f;
	position[1] = 0.0f;
	velocity[0] = 0.0f;
	velocity[1] = 0.0f;
	acceleration[0] = 0.0f;
	acceleration[1] = 0.0f;

	health = 1.0f;

	isFirstFrame = true;
}

// Draw the particle, circle shape
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

// Update motion
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

	health = health - 0.002f;
}

// Set starting position
void Particle::startPos(float x, float y)
{
	position[0] = x;
	position[1] = y;

	isFirstFrame = false;
}

// Draw the particle
void Particle::draw()
{
	drawShape(position[0], position[1], 0.0028f, 32);
}

// Function to add a force 
void Particle::addForce(float force[2])
{
	acceleration[0] += force[0];
	acceleration[1] += force[1];
}

// Constant force being applied upwards 
void Particle::forces()
{
	addForce(rising);
}

// Add a starting force to the particle in a random direction 
void Particle::startForce()
{
	float randomForce[2] = { (float)dist(gen), (float)dist(gen) };

	addForce(randomForce);
}

// Set the particles color
void Particle::color()
{
	glColor4f(0.4f, 0.4f, 0.4f, health);
}
