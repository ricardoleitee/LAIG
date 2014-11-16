#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "Globals.h"
#include "Camera.h"
#include "Light.h"
#include <map>
#include "Texture.h"
#include "Appearance.h"
#include "Transform.h"
#include "Primitive.h"
#include "Node.h"

class XMLScene
{
public:
	Globals* globals;
	Globals* getGlobals();
	vector<Camera*> cameras;
	vector<Camera*> getCameras();
	vector<Light*> lights;
	vector<Light*> getLights();
	map<string,Texture*> textures;
	map<string,Texture*> getTextures();
	map<string,Appearance*> appearances;
	map<string, Appearance*> getAppearances();
	std::string rootId;
	std::string getRootId();
	Node* node;
	map<string, Node*> scene;
	map<string, Node*> getScene();

	XMLScene(char *filename);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

	void setAppNodes(map<string,Node*> fscene, std::string rootId);

	unsigned int readInt(char* attribute, TiXmlElement* element);
	char readChar(char* attribute, TiXmlElement* element);
	float readFloat(char* attribute,TiXmlElement* element);
	void read2Float(char* attribute,TiXmlElement* element, float* flt);
	void read3Float(char* attribute,TiXmlElement* element, float* flt);
	void read4Float(char* attribute,TiXmlElement* element, float* flt);
	std::string readString(char* attribute,TiXmlElement* element);
	int readBool(char* attribute, TiXmlElement* element);

	void readGlobalsElement();
	void readCamerasElement();
	void readLightsElement();
	void readTexturesElement();
	void readAppearancesElement();
	void readGraphElement();
	
protected:

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement;
	TiXmlElement* lightsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;


};

#endif