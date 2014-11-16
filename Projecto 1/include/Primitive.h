#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

//#include <GL\glew.h>
#include <GL\glut.h>
#include <math.h>

#define PI 3.1415926535898

class Primitive {
public:
	float s, t;

	Primitive();
	~Primitive();

	virtual void draw();
	void setS(float s);
	void setT(float t);
};

class Rectangle:public Primitive {
	float x1, x2, y1, y2;
	unsigned int rectangle;

public:
	Rectangle(float x1, float y1, float x2, float y2);
	~Rectangle();
	void draw();
};

class Triangle:public Primitive {
	float n1, n2, n3, p0[2], p1[2], p2[2];
	float x1, y1, z1, x2, y2, z2, x3, y3, z3;
	unsigned int triangle;

public:
	Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	~Triangle();
	void calculateNormal();
	void calculateVertex();
	void draw();
};

class Cylinder:public Primitive {
	float base, top, height;
	int slices, stacks;
	unsigned int cylinder;

public:
	Cylinder(float base, float top, float height, int slices, int stacks);
	~Cylinder(void);
	void drawCircle(float radius);
	void draw();
};

class Sphere:public Primitive {
	float radius;
	int slices, stacks;
	unsigned int sphere;

public:
	Sphere(float radius, int slices, int stacks);
	~Sphere(void);
	void draw();
};

class Torus:public Primitive {
	float inner, outer;
	int slices, loops;
	unsigned int torus;

public:
	Torus(float inner, float outer, int slices, int loops);
	~Torus();
	void draw();
};

#endif