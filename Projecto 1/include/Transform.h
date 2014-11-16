#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "CGFapplication.h"

class Transform {
public:
	Transform();
	virtual void apply();
	~Transform();
};

class Translate:public Transform {
	float x, y , z;

public:
	Translate(float x, float y, float z);
	void apply();

	float getX();
	float getY();
	float getZ();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
};

class Rotate:public Transform {
	char axis;
	float angle;

public:
	Rotate(char axis, float angle);
	void apply();

	char getAxis();
	float getAngle();

	void setAxis(char axis);
	void setAngle(float angle);
};

class Scale:public Transform {
	float x, y, z;

public:
	Scale(float x, float y, float z);
	void apply();
	
	float getX();
	float getY();
	float getZ();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
};

#endif