#include "Appearance.h"


Appearance::Appearance(std::string id, float shininess, float* ambi, float* diff, float* spec, std::string textureref, float textl_s, float textl_t):CGFappearance(ambi, diff, spec, shininess) {
	this->id = id;
	this->shininess = shininess;
	this->textureref = textureref;
	this->textl_s = textl_s;
	this->textl_t = textl_t;
	//setTexture(textureref);
}

Appearance::Appearance(std::string id, float shininess, float* ambi, float* diff, float* spec):CGFappearance(ambi, diff, spec, shininess) {
	this->id = id;
	this->shininess = shininess;
}

Appearance::~Appearance(){
}

std::string Appearance::getId() {
	return id;
}

float Appearance::getShininess() {
	return shininess;
}

std::string Appearance::getTextureref() {
	return textureref;
}

float Appearance::getTextlS() {
	return textl_s;
}

float Appearance::getTextlT() {
	return textl_t;
}
