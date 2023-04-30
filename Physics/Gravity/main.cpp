#include <GLFW/glfw3.h>
#include "Sun.h"
#include "Planet.h"
#include <iostream>

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

    Sun sun;
    Planet planet;

    planet.startPos(0, 0.5f);

    planet.addForce(0.000004f, 0.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the sun
        sun.drawSun(0, 0, 0.09f, 32);

        // Draw the planet
        planet.drawPlanet(planet.planetCenterX, planet.planetCenterY, 0.05f, 32);
        
        // Add gravity to the planet
        planet.addGravity(sun);

        // Give the planet motion 
        planet.motion();

        std::cout << planet.planetAccelerationY << "\n";

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
