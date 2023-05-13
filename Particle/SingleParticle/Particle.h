#ifndef PARTICLE_H
#define PARTICLE_H
class Particle
{
public:
	Particle();

	void drawCircle(float centerX, float centerY, float radius, int numOfSeg);

	void motion();
	
	void addForce(float force[2]);

	void startFunc(float x, float y, float force[2]);

	void color();

	float position[2];

	bool isFirstFrame;

	float health;

private:

	float velocity[2];
	float acceleration[2];

	float mass;
	float damping;
	//float health;

};

#endif
