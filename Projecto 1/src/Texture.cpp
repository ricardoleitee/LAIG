#include "Texture.h"

Texture::Texture(std::string id, std::string file, float textl_s, float textl_t):CGFtexture(file) {
	this->id = id;
	this->file = file;
	this->textl_s = textl_s;
	this->textl_t = textl_t;
}

Texture::~Texture() {
}

std::string Texture::getId() {
	return id;
}

std::string Texture::getFile() {
	return file;
}

float Texture::getTextlS() {
	return textl_s;
}

float Texture::getTextlT() {
	return textl_t;
}