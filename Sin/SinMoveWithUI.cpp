#include <GLFW/glfw3.h>
#include <cmath>
#include <chrono>

const float PI = 3.14159265358979323846f;
float y = 0;
float a = 0.4;
float f = 1;
float worldX = 0.0f;
float worldY = 0.0f;
float rightCircleY = 0.0f;
float leftCircleY = -0.6f;
float frequency;

void drawLine(float x, float y, float x1, float y1)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x1, y1);
    glEnd();
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int win_width, win_height;
    glfwGetWindowSize(window, &win_width, &win_height);

    // Convert cursor position to world coordinates
    worldX = (float)xpos / win_width * 2.0f - 1.0f;
    worldY = -((float)ypos / win_height * 2.0f - 1.0f);

}

void drawCircle(float x, float y, float radius, int seg)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= seg; i++)
    {
        float angle = i * (PI * 2) / seg;
        glVertex2f(x + radius * std::sin(angle), y + radius * std::cos(angle));
    }
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    auto startTime = std::chrono::high_resolution_clock::now();


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        auto now = std::chrono::high_resolution_clock::now();

        auto elapsed = std::chrono::duration<float>(now - startTime).count();

        glfwSetCursorPosCallback(window, cursor_position_callback);
        
        frequency = (leftCircleY + 0.6f) * 2;

        a = rightCircleY;
        f = frequency;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if (worldX < 0.96 && worldX > 0.84f && worldY < 0.6f && worldY > -0.6f)
            {
                rightCircleY = worldY;
            }

            if (worldX < -0.84f && worldX > -0.96f && worldY < 0.6f && worldY > -0.6f)
            {
                leftCircleY = worldY;
            }
        }

        y = a * std::sin(f * elapsed);

        glColor3f(0.7, 0.1, 0.1);
        drawLine(0.9, 0.6, 0.9, -0.6);
        drawLine(-0.9, 0.6, -0.9, -0.6);


        glColor3f(0.8, 0.9, 0.8);
        drawCircle(0, y, 0.06, 32);

        glColor3f(0, 0.7, 0.1);
        drawCircle(0.9f, rightCircleY, 0.06, 32);
        drawCircle(0.9f, rightCircleY * -1.0f, 0.06, 32);
        drawCircle(-0.9f, leftCircleY, 0.06, 32);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
