#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"

class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();
private:
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFappearance* textureAppearance2;
	CGFappearance* textureAppearance3;
	CGFappearance* textureAppearance4;
	CGFappearance* textureAppearance5;
	CGFappearance* textureAppearance6;
	CGFshader* shader;
};

#endif