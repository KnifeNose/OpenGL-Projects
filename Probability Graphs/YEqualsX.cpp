#include <GLFW/glfw3.h>
#include <ctime>
#include <random>
#include <iostream>
#include <array>

// draw a line
void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
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


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Y = X", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    const int totalChangeMax = 1000;
    int totalChange = 0;
    const int numberOfRects = 100;
    std::array <float, 100> heightsArray = { 0 };
    int randomNumber3 = 0;

    bool hasChanged = false;

    // using a seed to generate a different set of random numbers depending on the time
    unsigned seed = static_cast<unsigned>(std::time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(0, 99);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // 2 random numbers are chosen
        int randomNumber1 = dist(gen);
        int randomNumber2 = dist(gen);

        // if the first random number is bigger than the second number it is used to change 
        // the height of that numbers rectangle.
        if (randomNumber1 > randomNumber2)
        {
            randomNumber3 = randomNumber1;
            hasChanged = true;
        }

        // this adds the number to the array
        if (hasChanged && totalChange < totalChangeMax)
        {
            heightsArray[randomNumber3] += 0.1f;
            hasChanged = false;
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
        drawLine(-1, -1, 1, 1);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
