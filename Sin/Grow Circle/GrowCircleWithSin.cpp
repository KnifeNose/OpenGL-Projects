#include <GLFW/glfw3.h>
#include <cmath>

// Pi float 
const float PI = 3.14159265358979323846f;

// Draw a circle to the window
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

    float time = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Set aspect ratio
        float aspectRatio = (float)width / (float)height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        // Adjust the radius of the circle with sin
        float radius = 0.5f + 0.2f * sin(time);

        // Adjust the circle X position with sin
        float moveX = 0.0f + 0.2f + sin(time);

        // Draw circle setting the radius to sin
        glColor3f(1.0f, 1.0f, 1.0f);
        drawCircle(0.0f, 0.0f, radius, 32);

        // Draw another circle adjusting its X value with sin
        glColor3f(1.0f, 0, 0);
        drawCircle(moveX, 1.0f, 0.1f, 32);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        time += 0.01f;
    }

    glfwTerminate();
    return 0;
}
