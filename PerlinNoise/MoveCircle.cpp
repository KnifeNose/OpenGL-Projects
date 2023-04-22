#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include <iostream>

const float PI = 3.14159265358979323846f;

// Draw circle
void drawCircle(float x, float y, float radius, int seg)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= seg; i++)
    {
        float angle = i * (PI * 2) / seg;
        glVertex2f(x + radius * sin(angle), y + radius * cos(angle));
    }
    glEnd();
}

// Linear interpolation
float lerp(float a, float b, float t) 
{
    return a + t * (b - a);
}

// Smoothing function
float smoothstep(float t) 
{
    return t * t * (3 - 2 * t);
}

// Perlin noise function
// Need to finesse the formula
float perlin1D(float x) 
{
    int xi = (int)std::floor(x);
    float xf = x - xi;

    // Generate gradients
    std::mt19937 gen(xi);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    float g0 = dist(gen);
    float g1 = dist(gen);

    // Calculate dot products
    float dot0 = g0 * xf;
    float dot1 = g1 * (xf - 1.0f);

    // Interpolate using smoothstep function
    float t = smoothstep(xf);
    return lerp(dot0, dot1, t);
}

//int main()
//{
//    float p = 0;
//
//    while (true)
//    {
//        std::cout << perlin1D(p) << std::endl;
//        p += 0.0001f;
//    }
//
//}

float p = 0;

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

        // Draw circle attatching perlin noise to X value
        drawCircle(perlin1D(p), 0.0f, 0.1f, 32);

        // moving through time to get different perlin noise numbers
        p += 0.007f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
