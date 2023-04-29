#ifndef MOVERS_H
#define MOVERS_H

class Movers
{
public:
    void drawCircle(float circleCenterX, float circleCenterY, float circleRadius, int numOfSegments);
    
    void addMotion();

    void addForce(float x, float y);

    void resetAcceleration();

    void collision();

    void startingPos();

    void limitSpeed(float limit);


    float circleCenterX = 0;
    float circleCenterY = 0;
    float circleVelocityX = 0;
    float circleVelocityY = 0;
    float circleAccelerationX = 0;
    float circleAccelerationY = 0;
    float circleRadius = 0.1f;
    float mass = 0;
    float forceX = 0;
    float forceY = 0;
    float forceMass = 0;
};

#endif
