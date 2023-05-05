#ifndef PENDULUM_H
#define PENDULUM_H


class Pendulum
{
public:
	void drawCircle(float centerX, float centerY, float radius, int numOfSeg);

	void drawLine(float x1, float y1, float x2, float y2);

	void addMotion();

    void resetAcceleration();

    void setAngle();

    float originX = 0.0f;
    float originY = 1.0f;
    float circleX = 0.0f;
    float circleY = 0.0f;
    float gravity = 0.001f;

    float damping = 0.99;

    float angleA = 0.0f;
    float angleV = 0;

    float angle = 0;
    float armLength = 1;
};




#endif
