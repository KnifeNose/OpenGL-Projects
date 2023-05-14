#include "ParticleSystem.h"
#include "Particle.h"
#include <ctime>
#include <random>



//create a unsigned variable that gives a number that chages each second

unsigned seed = static_cast<unsigned>(std::time(nullptr));

// returns a random number using the seed so generate different random numbers

std::mt19937 gen(seed);

// use gen(dist) to generate a random number between the numbers defined in dist()

std::uniform_real_distribution<> dist(-0.01f, 0.01f);

float randomForce[2] = { (float)dist(gen), (float)dist(gen) };


ParticleSystem::ParticleSystem()
    :isFirstFrame1(true)
{

    particles = {};

	position[0] = 0.0f;
	position[1] = 0.0f;
}

void ParticleSystem::addParticle()
{
	particles.push_back(Particle());
}

void ParticleSystem::startPos(float x, float y)
{
	position[0] = x;
	position[1] = y;

    isFirstFrame1 = false;
}

void ParticleSystem::emitter()
{
    float randomForce[2] = { (float)dist(gen), (float)dist(gen) };
	addParticle();
    particleTotal = particles.size();
    for (Particle& p : particles)
    {
        if (p.isFirstFrame)
        {
            p.startFunc(position[0], position[1]);
            p.addForce(randomForce);
        }
        p.color();
        p.drawCircle(p.position[0], p.position[1], 0.01f, 32);
        p.enableGravity();
        p.motion();
    }
    
    for (int i = 0; i < particleTotal; i++)
    {
        if (particles[i].health < 0.0f)
        {
            particles.erase(particles.begin());
            particleTotal--;
            i--;
        }
    }

}
