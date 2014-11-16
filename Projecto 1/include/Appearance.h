#ifndef _APPEARANCE_H_
#define _APPEARANCE_H_

#include <string>
#include <CGF/CGFappearance.h>
#include "Texture.h"

class Appearance:public CGFappearance {
	std::string id, textureref;
	float shininess, textl_s, textl_t;

public:
	Appearance(std::string id, float shininess, float* ambi, float* diff, float* spec, std::string textureref, float textl_s, float textl_t);
	Appearance(std::string id, float shininess, float* ambi, float* diff, float* spec);
	virtual ~Appearance();
	std::string getId();
	float getShininess();
	std::string getTextureref();
	float getTextlS();
	float getTextlT();
};

#endif