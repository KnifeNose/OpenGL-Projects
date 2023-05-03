#include <GLFW/glfw3.h>
#include "Water.h"
#include "Balls.h"
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

    Balls ball[5];
    Water water;
    float x = -0.85f;

    
    for (int i = 0; i < 5; i++)
    {
        ball[i].randomMass();
        ball[i].startingPos(x, 0.9f);
        x = x + 0.4f;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        glColor3f(0, 0.2f, 0.4f);
        water.drawWater(-1, -1, 2, 1);


        glColor3f(0.1f, 0.4f, 0.1f);
        for (int i = 0; i < 5; i++)
        {
            ball[i].drawCircle(ball[i].circlePosX, ball[i].circlePosY, ball[i].circleRadius, 32);
            ball[i].addGravity(-0.0001f);
            if (ball[i].circlePosY - ball[i].circleRadius < 0)
            {
                ball[i].waterResistance();
            }
            ball[i].ballMotion();
        }

        for (int i = 0; i < 5; i++)
        {
            ball[i].resetAcceleration();
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
