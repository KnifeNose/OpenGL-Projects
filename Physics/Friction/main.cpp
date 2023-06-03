#include <GLFW/glfw3.h>
#include "Ground.h"
#include "Box.h"

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

    Ground grounds[5];
    Box b;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw ground
        float x = -1;
    for (int i = 0; i < 5; i++)
    {
        float temp = 0.4f;
        float y = -1;

        grounds[i].drawGround(x, y, 0.5f, 0.5f);
        x += temp;
    }
        // Color
        glColor3f(0.0f, 1.0f, 0.0f);

        // Box functionality 
        b.drawBox(b.posX, b.posY, 0.2f, 0.1f);
        b.motion();
        b.addForce(0.0000001f);
        b.addFriction();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
