#ifndef PARTICLE_H
#define PARTICLE_H	
class Particle
{
public:
	Particle();

	void drawShape(float x, float y, float radius, int seg);

	void motion();

	void startPos(float x, float y);

	void draw();

	void addForce(float force[2]);

	void forces();

	void startForce();

	void color();


	float position[2];
	float velocity[2];
	float acceleration[2];

	float health;

	bool isFirstFrame;

private:

};

#endif
