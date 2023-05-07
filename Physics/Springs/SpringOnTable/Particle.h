#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
	Particle(float x, float y);

	void applyForce(float force[2]);
	void update();
	void drawCircle();

	float position[2];
	float velocity[2];
	float acceleration[2];

private:
	float mass;
};

#endif // PARTICLE_H
