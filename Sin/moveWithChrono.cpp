#include <GLFW/glfw3.h>
#include <cmath>
#include <chrono>

// Variables
const float PI = 3.14159265358979323846f;
float y = 0;
float a = 0.4;
float f = 1;

// Draw circle
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


    // Using chrono which is a high resolution clock
    auto startTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        auto now = std::chrono::high_resolution_clock::now();

        // Getting the delta time
        auto elapsed = std::chrono::duration<float>(now - startTime).count();


        // Sine calculation
        y = a * std::sin(f * elapsed);

        drawCircle(0, y, 0.06, 32);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
