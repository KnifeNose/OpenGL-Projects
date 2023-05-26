#include <GLFW/glfw3.h>
#include "Particle.h"
#include <vector>
#include <cmath>

// PI
const float PI = 3.14159265358979323846f;

// Mouse location
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

// Draw a circle
void drawCircle(float x, float y, float r, int seg)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= seg; i++)
    {
        float angle = i * (2.0f * PI) / seg;
        glVertex2f(x + r * std::cos(angle), y + r * std::sin(angle));
    }
    glEnd();
}

// Draw a line
void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
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

    // Enable alpha blending
    glEnable(GL_BLEND);

    // Set the blend function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Vector of paricles 
    std::vector<Particle> p;

    // Variables 
    float circleX = 0.0f;
    float circleXForce = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        // Wind force 
        float wind[2] = { circleXForce, 0.0f };
        
        // Spawn particles 
        for (int i = 0; i < 6; i++) 
        {
        p.push_back(Particle());

        }
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Update partcles 
        for (Particle& part : p)
        {
            part.color();
            if (part.isFirstFrame)
            {
                part.startPos(0.0f, -0.6f);
                part.startForce();
            }
            part.forces();
            part.addForce(wind);
            part.draw();
            part.motion();

        }
        glfwSetCursorPosCallback(window, cursor_position_callback);



        // Move the slider with a click
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if (worldX < 0.5f && worldX > -0.5f)
            {
            circleX = worldX;

            }
        }

        circleXForce = circleX / 100000;
        
        // Draw
        glColor3f(0.8f, 0.1f, 0.1f);
        drawLine(-0.5f, 0.7f, 0.5f, 0.7f);

        glColor3f(0.1f, 0.6f, 0.5f);
        drawCircle(circleX, 0.7f, 0.05f, 32);

        glColor3f(0.75f, 0.1f, 0.1f);
        drawCircle(0.0f, -0.6f, 0.03f, 32);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
