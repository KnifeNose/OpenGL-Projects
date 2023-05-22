#include <GLFW/glfw3.h>
#include <cmath>
#include <random>

int width = 640;
int height = 480;

float xPos = 0.003125;

float inc = 0.01f;
float start = 0;

void drawSquare(float x1, float y1, float width, float height)
{
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x1 + width, y1);
    glVertex2f(x1 + width, y1 + height);
    glVertex2f(x1, y1 + height);
    glEnd();
}

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

int main(void)
{

    //xPos = 2.0f / width;


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
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

        float x = -1.0f;
        float y = start;

        for (int i = 0; i < width; i++)
        {
            drawSquare(x, perlin1D(y), 0.007f, 0.007f);
            x += xPos;
            y += inc;
        }

        start += inc;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
