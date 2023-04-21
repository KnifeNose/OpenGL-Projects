#include <GLFW/glfw3.h>
#include <chrono>
#include <random>
#include <iostream>
#include <array>
#include <cmath>

const float PI = 3.14159265358979323846f;

void drawBellCurve(float mu, float sigma, float minX, float maxX)
{
    const int numPoints = 100;
    float yValues[numPoints] = { 0 };

    // Calculate the y values for the bell curve
    for (int i = 0; i < numPoints; i++)
    {
        float x = i * (maxX - minX) / numPoints + minX;
        float y = exp(-(pow(x - mu, 2.0f) / (2.0f * pow(sigma, 2.0f)))) / (sigma * sqrt(2.0f * PI));
        yValues[i] = y;
    }

    // Draw the bell curve using lines
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numPoints; i++)
    {
        float x = i * (maxX - minX) / numPoints + minX;
        float y = (yValues[i] * 2) - 1;
        glVertex2f(x, y);
    }
    glEnd();
}

// draw a rectangle
void drawRectangle(float rectX, float rectY, float rectWidth, float rectHeight)
{
    glBegin(GL_QUADS);
    glVertex2f(rectX, rectY);
    glVertex2f(rectX + rectWidth, rectY);
    glVertex2f(rectX + rectWidth, rectY + rectHeight);
    glVertex2f(rectX, rectY + rectHeight);
    glEnd();
}

// random number is chosen with a normal distribution 
float randomGaussian(float mean, float stddev)
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
    std::normal_distribution<float> dist(mean, stddev);
    return dist(gen);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Gaussian Distribution", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    const int totalChangeMax = 900;
    int totalChange = 0;
    const int numberOfRects = 100;
    std::array <float, 100> heightsArray = { 0 };


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // 1 random number is chosen
        int randomNumber1 = std::lround(randomGaussian(50.0f, 20.0f));


        // random number is used to change height of the rectangle if it is within range
        if (totalChange < totalChangeMax && randomNumber1 >= 0 && randomNumber1 < 100)
        {
            heightsArray[randomNumber1] += 0.1f;
            totalChange++;
        }


        float rectXPos = -1;
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // the array is used to calculate the heights of the rectangles
        glColor3f(0, 0.5f, 0);
        for (int i = 0; i < numberOfRects; i++)
        {
            drawRectangle(rectXPos, -1, 0.01f, heightsArray[i]);
            rectXPos += 0.02f;
        }

        glColor3f(1, 0, 0);
        drawBellCurve(0.0f, 0.5f, -1.0f, 1.0f);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
