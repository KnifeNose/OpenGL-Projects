#include <GLFW/glfw3.h>
#include "Weight.h"
#include "Spring.h"
#include <vector>

float gravity[2]{ 0.0f , -0.001f };

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


    Weight weights[6];
    std::vector<Spring> springs;

    int numOfWeights = 6;
    int numOfSprings = 5;

    for (int i = 0; i < numOfWeights; i++)
    {
        float x = 0.0f;
        float y = 1.0f - (i * 0.3f);
        weights[i].startingPos(x, y);
    }

    for (int i = 0; i < numOfSprings; i++)
    {
        springs.push_back(Spring::Spring(weights[i], weights[i + 1]));
        springs[i].springStats(0.02f, 0.1f);
    }

    weights[0].lock();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < numOfWeights; i++)
        {
            weights[i].motion();
            weights[i].drawCircle();
            weights[i].addForce(gravity);
        }

        for (int i = 0; i < numOfSprings; i++)
        {
            springs[i].motion();
            springs[i].drawLine();
        }

        glfwSetCursorPosCallback(window, cursor_position_callback);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            weights[5].weightPosition[0] = worldX;
            weights[5].weightPosition[1] = worldY;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
