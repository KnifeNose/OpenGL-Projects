#include <GLFW/glfw3.h>
#include <cmath>

const float PI = 3.14159265358979323846f;
float world_x = 0;
float world_y = 0;

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

// Draw line
void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}


// Detect cursor position
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int win_width, win_height;
    glfwGetWindowSize(window, &win_width, &win_height);

    // Convert cursor position to NDC coordinates [-1, 1]
    float ndc_x = (float)xpos / (float)win_width * 2.0f - 1.0f;
    float ndc_y = (float)ypos / (float)win_height * 2.0f - 1.0f;

    // Create the projection matrix
    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;
    float top = 1.0f;
    float near = -1.0f;
    float far = 1.0f;

    float proj_matrix[] = {
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / (far - near), 0.0f,
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0f
    };

    // Apply the projection matrix to the cursor position to get world coordinates
    world_x = proj_matrix[0] * ndc_x + proj_matrix[12];
    world_y = proj_matrix[5] * (-ndc_y) + proj_matrix[13];
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
    glfwSetCursorPosCallback(window, cursor_position_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        // Draw a line from the center of the screen to the cursor position
        glColor3f(1, 0, 0);
        drawCircle(0, 0, 0.01f, 32);
        drawLine(0, 0, world_x, world_y);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
