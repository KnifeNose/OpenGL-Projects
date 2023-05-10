#include "Weight.h"
#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

Weight::Weight() 
	:mass(1.0f)
{
	weightPosition[0] = 0.0f;
	weightPosition[1] = 0.0f;
	weightVelocity[0] = 0.0f;
	weightVelocity[1] = 0.0f;
	weightAcceleration[0] = 0.0f;
	weightAcceleration[1] = 0.0f;
	isLocked = false;
}

void Weight::motion()
{
	if (!isLocked)
	{
		weightVelocity[0] *= 0.99f;
		weightVelocity[1] *= 0.99f;

		weightVelocity[0] += weightAcceleration[0];
		weightVelocity[1] += weightAcceleration[1];
		weightPosition[0] += weightVelocity[0];
		weightPosition[1] += weightVelocity[1];
		weightAcceleration[0] *= 0.0f;
		weightAcceleration[1] *= 0.0f;
	}
}

void Weight::drawCircle()
{
	glBegin(GL_TRIANGLE_FAN);
	const int num_segments = 32;
	const float radius = 0.04f;
	glVertex2f(weightPosition[0], weightPosition[1]);
	for (int i = 0; i <= num_segments; ++i)
	{
		const float angle = i * (2.0f * PI / num_segments);
		glVertex2f(weightPosition[0] + radius * std::cos(angle),
			weightPosition[1] + radius * std::sin(angle));
	}
	glEnd();
}

void Weight::addForce(float force[2])
{
	float f[2] = { force[0] / mass, force[1] / mass };
	weightAcceleration[0] += f[0];
	weightAcceleration[1] += f[1];
}

void Weight::startingPos(float x, float y)
{
	weightPosition[0] = x;
	weightPosition[1] = y;
}

void Weight::lock()
{
	isLocked = true;
}
