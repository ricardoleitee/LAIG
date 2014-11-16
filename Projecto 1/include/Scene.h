#ifndef _SCENE_H_
#define _SCENE_H_

#include <CGF\CGFscene.h>
#include "XMLScene.h"
#include "CGFappearance.h"
#include "XMLScene.h"
#include "Primitive.h"
#include "Node.h"
#include <iostream>
#include <string>

class Scene:public CGFscene {
public:
	void init();
	void display();

	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;
	//GLOBALS
	Globals* globals;
	int drawmode;
	//CAMERAS
	vector<Camera*> cameras;
	int camera;
	//LIGHTS
	vector<int> lightState;
	vector<Light*> lights;
	//GRAPH
	std::string id;
	map<string, Node*> scene;
	//APPEARANCES
	int app;
	bool appChoose;
	float s, t;
	map<string, Appearance*> appearances;
	//TEXTURES
	map<string,Texture*> textures;

	CGFapplication * application;

	Globals* getGlobals(){return globals;}
	vector<Camera*> getCameras(){return cameras;}
	vector<Light*> getLights(){return lights;}
	std::string getId(){return id;}
	map<string, Node*> getScene(){return scene;}
	map<string, Appearance*> getAppearances(){return appearances;}
	map<string, Texture*> getTextures(){return textures;}

	Scene(Globals* globals, vector<Camera*> cameras,vector<Light*> lights, std::string id, map<string, Node*> scene, map<string, Appearance*> appearances, map<string,Texture*> textures);
	~Scene();
	void setLightState(int pos, int value);
	int getLightState(int pos);

	void drawPrimitives(string id);
	void applyTextures(string id);
};

#endif