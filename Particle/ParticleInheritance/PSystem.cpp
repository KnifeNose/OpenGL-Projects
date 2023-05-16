#include "PSystem.h"
#include "Particle.h"
#include <random>
#include <ctime>

int runningCount = 0;
//create a unsigned variable that gives a number that chages each second

unsigned seed = static_cast<unsigned>(std::time(nullptr));

// returns a random number using the seed so generate different random numbers

std::mt19937 gen(seed);

// use gen(dist) to generate a random number between the numbers defined in dist()

std::uniform_real_distribution<> dist(-0.01f, 0.01f);


PSystem::PSystem()

{
    postition[0] = 0.0f;
    postition[1] = 0.0f;
    p = {};
    firstFrame = true;
}


void PSystem::motion()
{
    float randomForce[2] = { (float)dist(gen), (float)dist(gen) };

        p.push_back(Particle());

        for (Particle& part : p)
        {
            if (part.isFirstFrame)
            {
                part.startPos(postition[0], postition[1]);
                part.addForce(randomForce);
            }
            part.drawShape(part.position[0], part.position[1], 0.01f, 32);
            part.motion();
            part.addGravity();
        }
        
}

void PSystem::startPos(float x, float y)
{
    if (firstFrame)
    {
    postition[0] = x;
    postition[1] = y;
    firstFrame = false;
    }

}

void PSystem::pLimit()
{
    size_t length = p.size();

    for (int i = 0; i < length; i++)
    {
        if (p[i].health <= 0)
        {
            p.erase(p.begin());
            i--;
            length--;
        }
    }
}

SPSystem::SPSystem()
{
    postition[0] = 0.0f;
    postition[1] = 0.0f;
    sp = {};
    firstFrame = true;
}

void SPSystem::motion()
{

    float randomForce[2] = { (float)dist(gen), (float)dist(gen) };

    sp.push_back(SquareParticle());


    for (SquareParticle& spart : sp)
    {
        if (spart.isFirstFrame)
        {
            spart.startPos(postition[0], postition[1]);
            spart.addForce(randomForce);
        }
        spart.drawShape(spart.position[0], spart.position[1], 0.1f, 0.1f);
        spart.motion();
        spart.addGravity();
    }
}

void SPSystem::pLimit()
{
    size_t splength = sp.size();

    for (int i = 0; i < splength; i++)
    {
        if (sp[i].health <= 0)
        {
            sp.erase(sp.begin());
            i--;
            splength--;
        }
    }
}
