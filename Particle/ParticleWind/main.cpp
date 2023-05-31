#include <GLFW/glfw3.h>
#include "Particle.h"
#include "PSystem.h"

float worldX = 0.0f;
float worldY = 0.0f;

// Get cursor position
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int win_width, win_height;
    glfwGetWindowSize(window, &win_width, &win_height);

    // Convert cursor position to world coordinates
    worldX = (float)xpos / win_width * 2.0f - 1.0f;
    worldY = -((float)ypos / win_height * 2.0f - 1.0f);

}

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

    PSystem p;
    
    // Wind force
    float wind[2] = { 0.0004f, 0.0f };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
 
        glfwSetCursorPosCallback(window, cursor_position_callback);
        
        // When left mouse button is pressed add wind force to particle
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            p.addForce(wind);
        }
        p.motion();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
