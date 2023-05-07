#include "Particle.h"
#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

Particle::Particle(float x, float y)
    : mass(1.0f) {
    position[0] = x;
    position[1] = y;
    velocity[0] = 0.0f;
    velocity[1] = 0.0f;
    acceleration[0] = 0.0f;
    acceleration[1] = 0.0f;
}

void Particle::applyForce(float force[2]) {
    float f[2] = { force[0] / mass, force[1] / mass };
    acceleration[0] += f[0];
    acceleration[1] += f[1];
}

void Particle::update() {
    velocity[0] *= 0.99f;
    velocity[1] *= 0.99f;

    velocity[0] += acceleration[0];
    velocity[1] += acceleration[1];
    position[0] += velocity[0];
    position[1] += velocity[1];
    acceleration[0] = 0.0f;
    acceleration[1] = 0.0f;
}

void Particle::drawCircle()
{
    glColor3f(0.18f, 0.77f, 0.95f);
    glBegin(GL_TRIANGLE_FAN);
    const int num_segments = 32;
    const float radius = 0.05f;
    glVertex2f(position[0], position[1]);
    for (int i = 0; i <= num_segments; ++i) 
    {
        const float angle = i * (2.0f * PI / num_segments);
        glVertex2f(position[0] + radius * std::cos(angle),
            position[1] + radius * std::sin(angle));
    }
    glEnd();
}
