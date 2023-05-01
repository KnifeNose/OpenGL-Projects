#include "Rect.h"
#include <GLFW/glfw3.h>

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

        float tempX = -0.6f;

    Rect rect[4];
    for (int i = 0; i < 4; i++)
    {
        rect[i].startPos(tempX, 0);
        tempX += 0.3f;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < 4; i++)
        {
        rect[i].drawRect(rect[i].posX, rect[i].posY, 0.1f, 0.1f, 3);

        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
