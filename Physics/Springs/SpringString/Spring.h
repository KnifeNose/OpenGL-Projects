#ifndef SPRING_H
#define SPRING_H

#include "Weight.h"

class Spring
{
public:
	Spring(Weight& aA, Weight& bB);
	//Spring(float k, float restLength, Weight& a, Weight& b);

	void motion();

	void drawLine();

	void springStats(float k, float restLength);



private:
	float k;
	float restLength;
	Weight& a;
	Weight& b;
};

#endif
