#include <GLFW/glfw3.h>
#include "Particle.h"
#include "ParticleSystem.h"
#include <vector>

#include <iostream>

float worldX = 0.0f;
float worldY = 0.0f;

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

    // Enable alpha blending
    glEnable(GL_BLEND);

    // Set the blend function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    std::vector<ParticleSystem> emitArray;

    int pressed = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSetCursorPosCallback(window, cursor_position_callback);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
        {
            if (pressed == 0)
            {
                emitArray.push_back(ParticleSystem());
                pressed++;
            }
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            pressed = 0;
        }


            for (ParticleSystem& q : emitArray)
            {
                if (q.isFirstFrame1 == true) 
                {
                    q.startPos(worldX, worldY);
                    q.isFirstFrame1 = false;
                }
                q.emitter();

            }
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
