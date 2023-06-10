#include <GLFW/glfw3.h>
#include <cmath>
#include "Movers.h"
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

    Movers move[5];

    // Set starting point
    for (int i = 0; i < 5; i++)
    {
        move[i].startingPos();
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            for (int i = 0; i < 5; i++)
            {
            move[i].addForce(0.0001f, 0);
            }
        }

        glColor3f(0, 0.6f, 0);
        for (int i = 0; i < 5; i++)
        {
        move[i].collision();
        move[i].drawCircle(move[i].circleCenterX, move[i].circleCenterY, move[i].circleRadius, 32);
        move[i].addForce(0, -0.0001f);
        move[i].addMotion();
        move[i].limitSpeed(0.01f);
        move[i].resetAcceleration();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
