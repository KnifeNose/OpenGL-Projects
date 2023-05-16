#ifndef PARTICLE_H
#define PARTICLE_H
class Particle
{
public:
	Particle();

	void drawShape(float x, float y, float radius, int numOfSeg);

	void motion();

	void addForce(float force[2]);

	void addGravity();

	void startPos(float x, float y);


	float position[2];

	bool isFirstFrame;

	float health;


private:

	float velocity[2];
	float acceleration[2];
};


class SquareParticle : public Particle
{
public:
	void drawShape(float x1, float y1, float height, float width);


};

#endif
