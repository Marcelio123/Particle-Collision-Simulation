#include "Circle.h"
#include <math.h>
#include <iostream>
#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 800
# define M_PI 3.14159265358979323846

Circle::Circle()
    : x0(0), y0(0), z0(0), radius(0), numberOfVertices(0), vx(0), vy(0)
{
    vertices = NULL;
    color = NULL;
    std::cout << "default constructer called!" << std::endl;
    Color[0] = 0; Color[1] = 0; Color[2] = 0;
}

Circle::Circle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLint numberOfSides, GLfloat colorA, GLfloat colorB, GLfloat colorC, GLfloat vx, GLfloat vy)
    : x0(x), y0(y), z0(z), radius(r), numberOfVertices(numberOfSides + 2), vx(vx), vy(vy) 
{
    vertices = NULL;
    color = NULL;
    std::cout << "constructor called!" << std::endl;
    Color[0] = colorA; Color[1] = colorB; Color[2] = colorC;
}

Circle::Circle(const Circle& c)
{
    std::cout << "copy constructor called!" << std::endl;
    x0 = c.x0; y0 = c.y0, z0 = c.z0;
    radius = c.radius;
    numberOfVertices = c.numberOfVertices;
    Color[0] = c.Color[0]; Color[1] = c.Color[1]; Color[2] = c.Color[2];
    vertices = c.vertices;
    color = c.color;
    vx = c.vx; vy = c.vy;
}

void Circle::Generate()
{

    GLfloat twicePi = 2.0f * M_PI;

    GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
    GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
    GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

    circleVerticesX[0] = x0;
    circleVerticesY[0] = y0;
    circleVerticesZ[0] = z0;

    for (int i = 1; i < numberOfVertices; i++)
    {
        circleVerticesX[i] = x0 + (radius * cos(i * twicePi / (numberOfVertices-2)));
        circleVerticesY[i] = y0 + (radius * sin(i * twicePi / (numberOfVertices-2)));
        circleVerticesZ[i] = z0;
    }

    vertices = new GLfloat[(numberOfVertices) * 3];

    for (int i = 0; i < numberOfVertices; i++)
    {
        vertices[i * 3] = circleVerticesX[i];
        vertices[(i * 3) + 1] = circleVerticesY[i];
        vertices[(i * 3) + 2] = circleVerticesZ[i];
    }

    color = new GLfloat[3 * numberOfVertices];

    for (int i = 0; i < 3 * numberOfVertices; i += 3)
    {
        color[i] = Color[0];
        color[i + 1] = Color[1];
        color[i + 2] = Color[2];
    }

    delete[] circleVerticesX;
    delete[] circleVerticesY;
    delete[] circleVerticesZ;

}

void Circle::drawCircle()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, color);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    move();
}

void Circle::set(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLint numberOfSides, GLfloat colorA, GLfloat colorB, GLfloat colorC, GLfloat Vx, GLfloat Vy)
{
    vertices = NULL;
    color = NULL;
    x0 = x; y0 = y; z0 = z; radius = r; numberOfVertices = numberOfSides + 2; vx = Vx; vy = Vy;
    Color[0] = colorA; Color[1] = colorB; Color[2] = colorC;
}

void Circle::move()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        vertices[i * 3] += vx;
        vertices[(i * 3) + 1] += vy;
    }

    x0 += vx;
    y0 += vy;

    if (y0 + radius >= SCREEN_HEIGHT)
        vy = -vy;
    if (x0 + radius >= SCREEN_WIDTH)
        vx = -vx;
    if (y0 - radius <= 0)
        vy = -vy;
    if (x0 - radius <= 0)
        vx = -vx;
}

Circle::~Circle()
{
    std::cout << "destructor called ! Radius = " << radius << std::endl;
    if (vertices)
        delete[] vertices;
    if (color)
        delete[] color;
}

void Collision(Circle& a, Circle& b)
{
    float d = sqrt(pow(a.x0 - b.x0, 2) + pow(a.y0 - b.y0, 2));
    if (d <= a.radius + b.radius)
    {
        float ma = pow(a.radius, 3);
        float mb = pow(b.radius, 3);
        float ca[2] = { a.x0, a.y0 };
        float cb[2] = { b.x0, b.y0 };
        float va[2] = { a.vx, a.vy };
        float vb[2] = { b.vx, b.vy };
        float* va_;
        float* vb_;
        float* vaSubvb = vectorSub(va, vb);
        float* vbSubva = vectorSub(vb, va);
        float* caSubcb = vectorSub(ca, cb);
        float* cbSubca = vectorSub(cb, ca);
        va_ = vectorSub(va, vectorMul(2 * mb / (ma + mb) * dot_product(vaSubvb, caSubcb) / (pow(caSubcb[0], 2) + pow(caSubcb[1], 2)), caSubcb));
        vb_ = vectorSub(vb, vectorMul(2 * ma / (ma + mb) * dot_product(vbSubva, cbSubca) / (pow(cbSubca[0], 2) + pow(cbSubca[1], 2)), cbSubca));
        a.vx = va_[0];
        a.vy = va_[1];
        b.vx = vb_[0];
        b.vy = vb_[1];
        delete[] va_;
        delete[] vb_;
        delete[] vaSubvb;
        delete[] vbSubva;
        delete[] caSubcb;
        delete[] cbSubca;
        a.move();
        b.move();
    }

}

float* Circle::GetCenterRad()
{
    float arr[] = { x0, y0, radius };
    return arr;
}

float* vectorMul(float x, float* vector)
{
    vector[0] = x * vector[0];
    vector[1] = x * vector[1];
    return vector;
}

float* vectorSub(float* vector_a, float* vector_b)
{
    float* vect = new float[2];
    vect[0] = vector_a[0] - vector_b[0];
    vect[1] = vector_a[1] - vector_b[1];
    return vect;
}

float dot_product(float* vector_a, float* vector_b) {
    float product = 0;
    for (int i = 0; i < 2; i++)
        product = product + vector_a[i] * vector_b[i];
    return product;
}