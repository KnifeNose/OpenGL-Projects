#ifndef PARTICLESYSTEMS_H
#define PARTICLESYSTEMS_H

#include <vector>
#include "Particle.h"

class ParticleSystem
{
public:
	ParticleSystem();


	void startPos(float x, float y);

	void emitter();
	
	float position[2];
	
	void addParticle();



	bool isFirstFrame1;



private:
	size_t particleTotal;
	std::vector<Particle> particles;

};

#endif
