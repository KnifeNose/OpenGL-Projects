#include <GLFW/glfw3.h>
#include "Particle.h"
#include <vector>
#include "PSystem.h"

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

    std::vector<PSystem> q;
    std::vector<SPSystem> sq;

    int pressed = 0;
    int runningCount = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSetCursorPosCallback(window, cursor_position_callback);
        
        
        for (PSystem& sys : q)
        {
            sys.startPos(worldX, worldY);
            sys.motion();
            sys.pLimit();
        }

        for (SPSystem& spsys : sq)
        {
            spsys.startPos(worldX, worldY);
            spsys.motion();
            spsys.pLimit();
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {

            if (pressed == 0)
            {
                if (runningCount % 2 == 1)
                {
                    sq.push_back(SPSystem());
                }
                else
                {
                    q.push_back(PSystem());
                }
                
            runningCount++;
                
            pressed++;
            }

        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            pressed = 0;
        }

        if (q.size() > 3)
        {
            q.erase(q.begin());
        }

        if (sq.size() > 3)
        {
            sq.erase(sq.begin());
        }



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
