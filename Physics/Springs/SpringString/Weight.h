#ifndef WEIGHT_H
#define WEIGHT_H

class Weight
{
public:
	Weight();

	void motion();

	void drawCircle();

	void addForce(float force[2]);

	void startingPos(float x, float y);

	void lock();


	float weightPosition[2];
	float weightVelocity[2];
	float weightAcceleration[2];

private:
	float mass;
	bool isLocked;
};


#endif // !WEIGHT_H
