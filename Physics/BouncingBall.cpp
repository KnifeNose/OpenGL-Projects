#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846f;
const float gravity = -4.18f;

float radius = 0.1f;

float deltaTime = 0;
float lastFrameTime = 0;


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

void drawSquare(float rectX, float rectY, float rectWidth, float rectHeight)
{
    glBegin(GL_QUADS);
    glVertex2f(rectX, rectY);
    glVertex2f(rectX + rectWidth, rectY);
    glVertex2f(rectX + rectWidth, rectY + rectHeight);
    glVertex2f(rectX, rectY + rectHeight);
    glEnd();
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Get the primary monitor and its video mode */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    /* Calculate the window size as 90% of the screen size */
    int width = static_cast<int>(mode->width * 0.8f);
    int height = static_cast<int>(mode->height * 0.8f);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float positionX = 0;
    float positionY = 0;
    float velocityX = 0;
    float velocityY = 0;
    float circleDamping = 0.91;
    float velocityThreshold = 0.7;

    float rectX = -2;
    float rectY = -1;
    float rectWidth = 4;
    float rectHeight = 0.1;




        bool clicked = false;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
    
        float currentTime = (float) glfwGetTime();
        int width, height;

        if (clicked)
        {
            velocityY += gravity * deltaTime;
        }

        // Click to reset the ball
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            clicked = true;
            positionY = 1;
            velocityY = 0;

        }

        positionX += velocityX * deltaTime;
        positionY += velocityY * deltaTime;

        
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        float aspectRatio = (float)width / (float)height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        glColor3f(0, 1.0f, 0);
        drawCircle(positionX, positionY, radius, 36);

        if (positionX - radius < rectX + rectWidth && positionX + radius > rectX &&
            positionY - radius < rectY + rectHeight && positionY + radius > rectY)
        {
            // If there is a collision, update the circle velocity
            if (positionX - radius < rectX || positionX + radius > rectX + rectWidth)
            {
                velocityX = -velocityX * circleDamping;
            }
            if (positionY - radius < rectY || positionY + radius > rectY + rectHeight)
            {
                velocityY = -velocityY * circleDamping;
            }
        }

        // Check if the circle is close enough to the rectangle
        float distanceX = positionX - rectX - rectWidth / 2.0f;
        float distanceY = positionY - rectY - rectHeight / 2.0f;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;
        if (distanceSquared < radius * radius)
        {
            // Move the circle just above the rectangle's surface
            positionY = rectY + rectHeight / 2.0f + radius;
            velocityY = 0.0f;
        }

        std::cout << rectX + rectWidth << "\n";

        glColor3f(0, 0, 1);

        drawSquare(rectX, rectY, rectWidth, rectHeight);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
