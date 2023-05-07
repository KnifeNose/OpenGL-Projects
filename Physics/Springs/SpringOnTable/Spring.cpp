#include "Spring.h"
#include <GLFW/glfw3.h>
#include <cmath>

Spring::Spring(float k, float restLength, Particle& a, Particle& b)
	: k(k), restLength(restLength), a(a), b(b) {}

void Spring::update() {
	float force[2] = { b.position[0] - a.position[0], b.position[1] - a.position[1] };
	float x = std::sqrt(force[0] * force[0] + force[1] * force[1]) - restLength;
	float length = std::sqrt(force[0] * force[0] + force[1] * force[1]);
	force[0] /= length;
	force[1] /= length;
	force[0] *= k * x;
	force[1] *= k * x;
	a.applyForce(force);
	force[0] *= -1;
	force[1] *= -1;
	b.applyForce(force);
}

void Spring::drawline() 
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(a.position[0], a.position[1]);
	glVertex2f(b.position[0], b.position[1]);
	glEnd();
}
