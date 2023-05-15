#ifndef PSYSTEM_H
#define PSYSTEM_H

#include "Particle.h"
#include <vector>

class PSystem
{
public:
	PSystem();

	void motion();

	void addForce(float force[2]);

	std::vector<Particle> p;
};


#endif
