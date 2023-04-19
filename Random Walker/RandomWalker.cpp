#include <GLFW/glfw3.h>
#include <cmath>
#include <ctime>
#include <random>
#include <vector>

const float PI = 3.14159265358979323846f;

void drawCircle(float circlePositonX, float circlePositionY, float circleRadius, int numSegments)
{
    glLineWidth(0.05f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circlePositonX, circlePositionY);
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = i * 2.0f * PI / numSegments;
        float x = circlePositonX + circleRadius * cos(angle);
        float y = circlePositionY + circleRadius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

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

    float circlePosX1 = 0.0f;
    float circlePosY1 = 0.0f;

    std::vector<std::pair<float, float>> circlePositions;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Generate a random number with a seed
        unsigned seed = static_cast<unsigned>(std::time(nullptr));
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dist(1, 4);

        int randomNumber = dist(gen);


        // random number is used to determine the direction the random walker will walk
        if (randomNumber == 1)
        {
            circlePosX1 += 0.0001f;
        }
        else if (randomNumber == 2)
        {
            circlePosX1 -= 0.0001f;
        }
        else if (randomNumber == 3)
        {
            circlePosY1 += 0.0001f;
        }
        else if (randomNumber == 4)
        {
            circlePosY1 -= 0.0001f;
        }

        // places the random walker has walked are stored in a vector
        circlePositions.push_back(std::make_pair(circlePosX1, circlePosY1));

        // stored positions are used to draw a line showing the path the random walker has walked 
        glColor3f(0, 1, 0);
        for (unsigned int i = 1; i < circlePositions.size(); i++)
        {
            drawLine(circlePositions[i].first, circlePositions[i].second, circlePositions[i - 1].first, circlePositions[i - 1].second);
        }

        // draw random walker 
        glColor3f(1, 0, 0);
        drawCircle(circlePosX1, circlePosY1, 0.01f, 32);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
