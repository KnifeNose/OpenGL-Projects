#ifndef PSYSTEM_H
#define PSYSTEM_H

#include <vector>
#include "Particle.h"

class PSystem
{
public:
	PSystem();

	void motion();

	void startPos(float x, float y);

	void pLimit();

	float postition[2];

	bool firstFrame;




private:
	std::vector<Particle> p;

};

class SPSystem : public PSystem
{
public: 
	SPSystem();

	void pLimit();

	void motion();



private:
	std::vector<SquareParticle> sp;
};

#endif
