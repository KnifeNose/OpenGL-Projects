#ifndef SPRING_H
#define SPRING_H

#include "Particle.h"

class Spring {
public:
	Spring(float k, float restLength, Particle& a, Particle& b);

	void update();
	void drawline();

private:
	float k;
	float restLength;
	Particle& a;
	Particle& b;
};

#endif // SPRING_H
