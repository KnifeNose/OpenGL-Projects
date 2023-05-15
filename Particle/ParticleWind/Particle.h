#ifndef PARTICLE_H
#define PARTICLE_H
class Particle
{
public:
	Particle();

	void drawShape(float x, float y, float radius, int seg);
	
	void motion();

	void addForce(float force[2]);

	void addGravity();

	void startPos(float x, float y);

	float position[2];

	bool isFirstFrame;

	float acceleration[2];
	
	float velocity[2];

private:



};



class SParticle : public Particle
{
public:
	SParticle();

	void drawShape(float x, float y, float widthandheight);

	void motion();


private:

};

#endif
