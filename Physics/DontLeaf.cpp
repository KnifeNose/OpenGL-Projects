#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846f;

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

float circlePosX = 0;
float circlePosY = 0;
float circleRadius = 0.1f;
float circleXVelocity = 0;
float circleYVelocity = 0;
float circleXAcceleration = 0.00001f;
float circleYAcceleration = -0.000001f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Dont Leaf", NULL, NULL);
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
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Leaf
        glColor3f(0, 0.4f, 0);
        drawCircle(circlePosX, circlePosY, circleRadius, 32);

        // Circle X Velocity
        circlePosX += circleXVelocity;
        circleXVelocity += circleXAcceleration;
        
        // Circle Y Velocity 
        circlePosY += circleYVelocity;
        circleYVelocity += circleYAcceleration;

        // Leaf wraps around window
        if (circlePosX > 1)
        {
            circlePosX = -1;
        }
        else if (circlePosX < -1)
        {
            circlePosX = 1;
        }
        else if (circlePosY > 1)
        {
            circlePosY = -1;
        }
        else if (circlePosY < -1)
        {
            circlePosY = 1;
        }

        // Reverse velocity once it hits a certain speed
        if (circleXVelocity > 0.001f)
        {
            circleXAcceleration *= -1;
        }
        if (circleYVelocity >= 0.001f)
        {
            circleYAcceleration *= -1;
        }
        if (circleXVelocity <  -0.001f)
        {
            circleXAcceleration *= -1;
        }
        if (circleYVelocity < -0.001f)
        {
            circleYAcceleration *= -1;
        }

        //std::cout << circleXVelocity << "\n";

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
