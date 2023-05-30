#include <GLFW/glfw3.h>
#include "Pendulum.h"

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

    Pendulum pend;

    pend.setAngle();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Pendulum physics
        pend.addMotion();
        
        // Draw pendulum
        pend.drawCircle(pend.circleX, pend.circleY, 0.1f, 32);
        pend.drawLine(pend.circleX, pend.circleY, pend.originX, pend.originY);


        pend.resetAcceleration();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
