#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <CGF/CGFtexture.h>
#include <string>

class Texture:public CGFtexture {
	std::string id, file;
	float textl_s, textl_t;

public:
	Texture(std::string id, std::string file, float textl_s, float textl_t);
	~Texture();
	std::string getId();
	std::string getFile();
	float getTextlS();
	float getTextlT();
};

#endif