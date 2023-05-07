#include <GLFW/glfw3.h>
#include "Particle.h"
#include "Spring.h"

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

    Particle p1(0.5f, 0.0f);
    Particle p2(0.0f, 0.0f);
    Spring spring(0.001f, 0.2f, p1, p2);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        spring.update();
        p1.update();
        p2.update();

        spring.drawline();
        p1.drawCircle();
        p2.drawCircle();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
