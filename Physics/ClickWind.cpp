#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

float circleCenterX = 0;
float circleCenterY = 0;
float circleVelocityX = 0;
float circleVelocityY = 0;
float circleAccelerationX = 0;
float circleAccelerationY = 0;
float circleRadius = 0.1f;

// Add force function
void addForce(float forceX, float forceY)
{
    circleAccelerationX += forceX;
    circleAccelerationY += forceY;
}

// Draw circle
void drawCircle(float circleCenterX, float circleCenterY, float circleRadius, int numOfSegments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circleCenterX, circleCenterY);
    for (int i = 0; i <= numOfSegments; i++)
    {
        float angle = i * 2.0f * PI / numOfSegments;
        float x = circleCenterX + circleRadius * cos(angle);
        float y = circleCenterY + circleRadius * sin(angle);
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



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Using the add force function to simulate gravity 
        addForce(0, -0.0001f);

        // When window is clicked add a force on the x axis to simulate wind
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            addForce(0.0001f, 0);
        }

        // Draw circle
        drawCircle(circleCenterX, circleCenterY, circleRadius, 32);

        // Give the circle motion
        circleCenterX += circleVelocityX;
        circleCenterY += circleVelocityY;

        circleVelocityX += circleAccelerationX;
        circleVelocityY += circleAccelerationY;

        // If circle hits the screen reverse it's direction 
        if (circleCenterX + circleRadius > 1 || circleCenterX - circleRadius < -1)
        {
            circleVelocityX *= -1;
        }
        if (circleCenterY + circleRadius > 1 || circleCenterY - circleRadius < -1)
        {
            circleVelocityY *= -1;
        }

        // Reset it's acceleration 
        circleAccelerationX *= 0;
        circleAccelerationY *= 0;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
