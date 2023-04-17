#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846f;

float deltaTime = 0;
float lastFrameTime = 0;

float radius = 0.09f;
float growRate = 0.1f;

float maxRadius = 0.2f;
float minRadius = 0.1f;

bool isGrowing = true;

    void drawCircle(float centerX, float centerY, float radius, int numSegments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = i * 2.0f * PI / numSegments;
        float x = centerX + radius * std::cos(angle);
        float y = centerY + radius * std::sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Name Window Here", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = (float)glfwGetTime();

        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        if (isGrowing)
        {
            radius += growRate * deltaTime;
        }
        else 
        {
            radius -= growRate * deltaTime;
        }


        if (radius > maxRadius)
        {
            isGrowing = false;
        }
        else if (radius < minRadius)
        {
            isGrowing = true;
        }
        
        //std::cout << radius;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        float aspectRatio = (float)width / (float)height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);


        glColor3f(1.0f, 1.0f, 1.0f);
        drawCircle(0.0f, 0.0f, radius, 32);

        glColor3f(1.0f, 0, 0);
        drawCircle(radius, 1.0f, 0.1f, 32);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}
