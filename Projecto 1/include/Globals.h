#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <string>
//#include <GL\glew.h>
#include <GL\glut.h>

class Globals {

	int dmode, shading, face, order;
	float background[4], ambient[4];
	bool dsided, local, enabled;

public:
	Globals(std::string dmode, std::string shading, float* background, std::string face, std::string order, bool dsided, bool local, bool enabled, float* ambient);
	~Globals();
	int setDmode(std::string val);
	int setShading(std::string val);
	int setFace(std::string val);
	int setOrder(std::string val);
	int getDmode();
	int getShading();
	float getBackground(int pos);
	int getFace();
	int getOrder();
	bool getDsided();
	bool getLocal();
	bool getEnabled();
	float getAmbient(int pos);
	float* getAmbient();
};

#endif