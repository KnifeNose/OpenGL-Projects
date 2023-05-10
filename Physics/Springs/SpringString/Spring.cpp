#include "Spring.h"
#include <cmath>
#include <GLFW/glfw3.h>


Spring::Spring(Weight& aA, Weight& bB)
	:k(0.001f), restLength(0.1f), a(aA), b(bB)
{
}

void Spring::motion()
{
		float force[2] = { b.weightPosition[0] - a.weightPosition[0], b.weightPosition[1] - a.weightPosition[1] };
		float x = std::sqrt(force[0] * force[0] + force[1] * force[1]) - restLength;
		float length = std::sqrt(force[0] * force[0] + force[1] * force[1]);
		force[0] /= length;
		force[1] /= length;
		force[0] *= k * x;
		force[1] *= k * x;
		a.addForce(force);
		force[0] *= -1.0f;
		force[1] *= -1.0f;
		b.addForce(force);
}

void Spring::drawLine()
{
	glBegin(GL_LINES);
	glVertex2f(a.weightPosition[0], a.weightPosition[1]);
	glVertex2f(b.weightPosition[0], b.weightPosition[1]);
	glEnd();
}

void Spring::springStats(float k, float restLength)
{
	Spring::k = k;
	Spring::restLength = restLength;
}
