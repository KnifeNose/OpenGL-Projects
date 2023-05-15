#include "PSystem.h"
#include <random>
#include <ctime>

//create a unsigned variable that gives a number that chages each second

unsigned seed = static_cast<unsigned>(std::time(nullptr));

// returns a random number using the seed 

std::mt19937 gen(seed);

// use gen(dist) to generate a random number between the numbers defined in dist()

std::uniform_real_distribution<> dist(-0.01f, 0.01f);

PSystem::PSystem()
{

}

void PSystem::motion()
{
    float randomForce[2] = { (float)dist(gen), (float)dist(gen) };
    p.push_back(SParticle());

    for (Particle& part : p)
    {
        if (part.isFirstFrame)
        {
            part.startPos(0.0f, 0.5f);
            part.addForce(randomForce);
        }
        part.motion();
        part.addGravity();
    }
}

void PSystem::addForce(float force[2])
{
    for (Particle& part : p)
    {
        part.addForce(force);
    }
}
