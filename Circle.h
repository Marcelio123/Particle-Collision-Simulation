#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Circle
{
private:
	int numberOfVertices;
	GLfloat Color[3];
	GLfloat* vertices;
	GLfloat* color;
	GLfloat vx, vy;
	GLfloat x0, y0, z0;
	GLfloat radius;
public:
	Circle();
	Circle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLint numberOfSides, GLfloat colorA, GLfloat colorB, GLfloat colorC, GLfloat vx, GLfloat vy);
	Circle(const Circle& circle);
	void set(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLint numberOfSides, GLfloat colorA, GLfloat colorB, GLfloat colorC, GLfloat vx, GLfloat vy);
	void Generate();
	void drawCircle();
	void move();
	float* GetCenterRad();

	friend void Collision(Circle& a, Circle& b);
	~Circle();
};


void Collision(Circle& a, Circle& b);

float* vectorMul(float x, float* vector);
float* vectorSub(float* vector_a, float* vector_b);
float dot_product(float vector_a[], float vector_b[]);

#endif