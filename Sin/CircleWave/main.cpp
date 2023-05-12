#include <GLFW/glfw3.h>
#include "Circles.h"

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

    int const numOfCircles = 20;

    Circles circles[20];

    float startTemp = -0.95f;
    float startAng = 0.0f;

    for (int i = 0; i < numOfCircles; i++)
    {
        circles[i].startPos(startTemp, 0.0f);
        circles[i].startingAngle(startAng);
        startTemp += 0.1f;
        startAng += 0.3f;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < numOfCircles; i++)
        {
            circles[i].drawCircle(circles[i].circleCenterX, circles[i].circleCenterY, 0.05f, 32);
            circles[i].sinMovementX(0.01f);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
