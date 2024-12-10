#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Circle.h"
#include "Ugp.h"

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 800
# define M_PI 3.14159265358979323846

void randCirc(int n, Circle*& c);

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    // Number of circles
    int n = 1000;

    // create circle
    Circle* circle = new Circle[n];

    randCirc(n, circle);
 
    // Generate circle
    for (int i = 0; i < n; i++)
        circle[i].Generate();


    // Initialize grid
    ugp A(7, circle, n);
    A.InitDrawGrid();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

        A.DrawGrid();

        // collision detection using uniform grid
        A.InsertToGrid();
        A.IterCircleInGrid();
        A.ClearCircleInGrid();

        // collsion detection by iterating each circle
        /*
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                Collision(circle[i], circle[j]);
        */

        // Draw Circle
        for (int i = 0; i < n; i++)
            circle[i].drawCircle();


        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    A.DeleteGrid();
    A.DeleteDrawGrid();
    delete[] circle;

    glfwTerminate();

    return 0;
}

void randCirc(int n, Circle*& c)
{
    srand(time(0));
    float x = 100, y = 100;
    float r = 255, g = 0, b = 0;
    int clr = 0;
    for (int i = 0; i < n; i++) {
        if (y >= SCREEN_HEIGHT - 100) {
            x += 30;
            y = 100;
        }
        if (x >= SCREEN_WIDTH - 100)
            x = 100;
        if (clr==0)
            c[i].set(x, y, 0, rand() % (10 - 5 + 1) + 5, 100, 255, 0, 0, (rand() % (20 + 20 + 1) - 20) * 0.002, (rand() % (20 + 20 + 1) - 20) * 0.002);
        else if (clr==1)                                 
            c[i].set(x, y, 0, rand() % (10 - 5 + 1) + 5, 100, 0, 255, 0, (rand() % (20 + 20 + 1) - 20) * 0.002, (rand() % (20 + 20 + 1) - 20) * 0.002);
        else if (clr==2)                                 
            c[i].set(x, y, 0, rand() % (10 - 5 + 1) + 5, 100, 0, 0, 255, (rand() % (20 + 20 + 1) - 20) * 0.002, (rand() % (20 + 20 + 1) - 20) * 0.002);
        clr++;
        if (clr == 3)
            clr = 0;
        
        y += 30;
    }
}


