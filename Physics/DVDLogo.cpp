#include <GLFW/glfw3.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <random>

const float PI = 3.14159265358979323846f;

// Draw a circle function
void drawCircle(float circlePosX, float circlePosY, float circleRadius, int numOfSegments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circlePosX, circlePosY);
    for (int i = 0; i <= numOfSegments; i++)
    {
        float angle = i * 2.0f * PI / numOfSegments;
        float x = circlePosX + circleRadius * cos(angle);
        float y = circlePosY + circleRadius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
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

    // Circle properties
    float circlePositionX = 0.1f;
    float circlePositionY = 0.1f;
    float circleRadius = 0.1f;

    // Delta time
    float lastFrameTime = 0;
    float deltaTime = 0;

    // Random number between 0.002 and 0.005
    unsigned seed = static_cast<unsigned>(std::time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(0.002f, 0.005f);

        float circleVelocityX = (float)dist(gen);
        float circleVelocityY = (float)dist(gen);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
    

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Delta time
        float currentTime = (float)time(0);
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // Draw circle
        glColor3f(1, 0, 0);
        drawCircle(circlePositionX, circlePositionY, circleRadius, 32);

        // if circle touches the edge of the world, reverse its direction
        if (circlePositionX + circleRadius > 1 || circlePositionX - circleRadius < -1)
        {
            circleVelocityX *= -1;
        }

        if (circlePositionY + circleRadius > 1 || circlePositionY - circleRadius < -1)
        {
            circleVelocityY *= -1;
        }

        circlePositionX += circleVelocityX;
        circlePositionY += circleVelocityY;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
