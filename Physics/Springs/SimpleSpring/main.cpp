#include <GLFW/glfw3.h>
#include "Circle.h"
#include <cmath>

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

    Circle circle;

    float anchorX = 0.0f;
    float anchorY = 1.0f;
    float restLength = 1.0f;
    float attatchX = 0.0f;
    float attatchY = 0.5f;
    float k = 0.001f;
    float velocityY = 0.0f;
    float velocityX = 0.0f;

    float differenceX = 0.0f;
    float differenceY = 0.0f;

    float damping = 0.992f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        circle.drawCircle(attatchX, attatchY, 0.1f, 32);

        circle.drawCircle(anchorX, anchorY, 0.05f, 32);

        circle.drawLine(anchorX, anchorY, attatchX, attatchY);

        differenceX = attatchX - anchorX;
        differenceY = attatchY - anchorY;

        float distanceLength = sqrt(pow((float)attatchX - (float)anchorX, 2) + pow((float)attatchY - (float)anchorY, 2)) - restLength;

        differenceX = differenceX * k * -1 * distanceLength;
        differenceY = differenceY * k * -1 * distanceLength;

        velocityX += differenceX;
        velocityY += differenceY;
        attatchX += velocityX;
        attatchY += velocityY;

        velocityX *= damping;
        velocityY *= damping;


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
