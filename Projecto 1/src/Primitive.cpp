#include "Primitive.h"

Primitive::Primitive() {
}

Primitive::~Primitive() {
}

void Primitive::draw() {
}

void Primitive::setS(float s){
	this->s = s;
}

void Primitive::setT(float t){
	this->t = t;
}

Rectangle::Rectangle(float x1, float y1, float x2, float y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

Rectangle::~Rectangle() {
}

void Rectangle::draw() {
	glPushMatrix();
	glNormal3d(0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3d(x1,y1,0);
		glTexCoord2f(s,0);
		glVertex3d(x2,y1,0);
		glTexCoord2f(s,t);
		glVertex3d(x2,y2,0);
		glTexCoord2f(0,t);
		glVertex3d(x1,y2,0);
	glEnd();
	glPopMatrix();
}

Triangle::Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	this->x1 = x1;
	this->y1 = y1;
	this->z1 = z1;
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	this->x3 = x3;
	this->y3 = y3;
	this->z3 = z3;

	calculateVertex();
}

Triangle::~Triangle() {
}

void Triangle::calculateNormal() {
	float x21, y21, z21, x31, y31, z31;

	x21 = x2 - x1; 
	y21 = y2 - y1; 
	z21 = z2 - z1; 

	x31 = x3 - x1; 
	y31 = y3 - y1; 
	z31 = z3 - z1; 

	n1 = (y21 * z31) - (z21 * y31);
	n2 = (x31 * z21) - (x21 * z31);
	n3 = (x21 * y31) - (x31 * y21);
}

void Triangle::calculateVertex(){
	float a = sqrtf( pow((x1 - x3),2) + pow((y1 - y3),2) + pow((z1 - z3),2));
	float b = sqrtf( pow((x2 - x1),2) + pow((y2 - y1),2) + pow((z2 - z1),2));
	float c = sqrtf( pow((x3 - x2),2) + pow((y3 - y2),2) + pow((z3 - z2),2));

	float cosy = (pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b);
	float cosa = (-pow(a,2)+pow(b,2)+pow(c,2))/(2*b*c);
	float cosb = (pow(a,2)-pow(b,2)+pow(c,2))/(2*a*c);

	p0[0] = c-a*cosb;
	p0[1] = a*sqrt(1-pow(cosb,2));
	p1[0] = 0;
	p1[1] = 0;
	p2[0] = c;
	p2[1] = 0;
	calculateNormal();
}

void Triangle::draw() {
	glPushMatrix();
	glNormal3d(n1,n2,n3);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(p0[0],p0[1]);
		glVertex3d(x1,y1,z1);
		glTexCoord2d(p1[0],p1[1]);
		glVertex3d(x2,y2,z2);
		glTexCoord2d(p2[0],p2[1]);
		glVertex3d(x3,y3,z3);
	glEnd();
	glPopMatrix();
}

Cylinder::Cylinder(float base, float top, float height, int slices, int stacks) {
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
}


Cylinder::~Cylinder(void) {
}

void Cylinder::drawCircle(float radius) {
	double delta = 2*PI/slices;

	glPushMatrix();
	glRotated(-90,1,0,0);
	glBegin(GL_POLYGON);
		for(int i=0 ; i <= slices; i++) {
			glTexCoord2d(0.5 + (cos(i*delta)/2), 0.5 + (sin(i*delta)/2));
			glNormal3d(sin(i*delta/2),0,cos(i*delta/2));
			glNormal3d(sin(i*delta),0,cos(i*delta));
			glVertex3d(radius*sin(i*delta),0,radius*cos(i*delta));
		}
	glEnd();
	glPopMatrix();
}

void Cylinder::draw() {
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	drawCircle(base);
	gluCylinder(qobj, base, top, height, slices, stacks);
	glPushMatrix();
	glTranslated(0,0,height);
	glRotated(180,1,0,0);
	drawCircle(top);
	glPopMatrix();
}

Sphere::Sphere(float radius, int slices, int stacks) {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}


Sphere::~Sphere(void) {
}

void Sphere::draw() {
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	gluSphere(qobj,radius,slices,stacks);
}

Torus::Torus(float inner, float outer, int slices, int loops) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

Torus::~Torus() {
}

void Torus::draw() {
	GLfloat vNormal[3];   
	double majorStep = 2.0f*3.14 / slices;   
	double minorStep = 2.0f*3.14 / loops;   
	int i, j;   

	for (i=0; i<slices; ++i) {   
		double a0 = i * majorStep;   
		double a1 = a0 + majorStep;   
		GLfloat x0 = (GLfloat) cos(a0);   
		GLfloat y0 = (GLfloat) sin(a0);   
		GLfloat x1 = (GLfloat) cos(a1);   
		GLfloat y1 = (GLfloat) sin(a1);

		glBegin(GL_TRIANGLE_STRIP);   
		for (j=0; j<=loops; ++j) {   
			double b = j * minorStep;   
			GLfloat c = (GLfloat) cos(b);   
			GLfloat r = outer * c + inner;   
			GLfloat z = outer * (GLfloat) sin(b);   

			// First point   
			glTexCoord2f((float)(i)/(float)(slices), (float)(j)/(float)(loops));   
			vNormal[0] = x0*c;
			vNormal[1] = y0*c;
			vNormal[2] = z/inner;
			///normalizar
			double magnitude2=sqrt(vNormal[0]*vNormal[0]+vNormal[1]*vNormal[1]+vNormal[2]*vNormal[2]);
			vNormal[0] /=magnitude2;
			vNormal[1] /=magnitude2;
			vNormal[2] /= magnitude2;

			glNormal3fv(vNormal);   
			glVertex3f(x0*r, y0*r, z);   

			glTexCoord2f((float)(i+1)/(float)(slices), (float)(j)/(float)(loops));   
			vNormal[0] = x1*c;   
			vNormal[1] = y1*c;   
			vNormal[2] = z/inner;   
			glNormal3fv(vNormal);   
			glVertex3f(x1*r, y1*r, z);   
		}   
		glEnd();   
	}
}