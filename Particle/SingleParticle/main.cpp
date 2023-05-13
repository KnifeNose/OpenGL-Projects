#include <GLFW/glfw3.h>
#include "Particle.h"
#include <random>
#include <ctime>
#include <vector>

//create a unsigned variable that gives a number that chages each second

unsigned seed = static_cast<unsigned>(std::time(nullptr));

// returns a random number using the seed so generate different random numbers

std::mt19937 gen(seed);

// use gen(dist) to generate a random number between the numbers defined in dist()

std::uniform_real_distribution<> dist(-0.01f, 0.01f);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Enable alpha blending
    glEnable(GL_BLEND);

    // Set the blend function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    float gravity[2] = { 0.0f, -0.00023f };

    std::vector<Particle> particles;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        float randomForce[2] = { (float)dist(gen), (float)dist(gen) };

        int particleTotal = particles.size();

        particles.push_back(Particle());

        for (Particle& p : particles)
        {
            if (p.isFirstFrame)
            {
                p.startFunc(0.0f, 0.7f, randomForce);
            }
            p.color();
            p.drawCircle(p.position[0], p.position[1], 0.01f, 32);
            p.motion();
            p.addForce(gravity);
        }

        for (int i = 0; i < particleTotal; i++)
        {
            if (particles[i].health < 0.0f)
            {
                particles.erase(particles.begin());
            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
