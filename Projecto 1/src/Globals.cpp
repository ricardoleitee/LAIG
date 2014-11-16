#include "Globals.h"

Globals::Globals(std::string dmode, std::string shading, float* background, std::string face, std::string order, bool dsided, bool local, bool enabled, float* ambient) {
	this->dmode = setDmode(dmode);
	this->shading = setShading(shading);
	this->face = setFace(face);
	this->order = setOrder(order);
	this->dsided = dsided;
	this->local = local;
	this->enabled = enabled;

	for (int i=0 ; i<4 ; i++) {
		this->background[i] = background[i];
		this->ambient[i] = ambient[i];
	}
}

Globals::~Globals(void)
{
/*	delete(dmode);
	delete(shading);
	delete(background);
	delete(face);
	delete(order);
	delete(dsided);
	delete(local);
	delete(enabled),
	delete(ambient); */
}

int Globals::setDmode(std::string val) {
	if (val == "line") {
		return GL_LINE;
	} else if (val == "point") {
		return GL_POINT;
	}
	return GL_FILL;
}

int Globals::setShading(std::string val) {
	if (val == "flat") {
		return GL_FLAT;
	}
	return GL_SMOOTH;
}

int Globals::setFace(std::string val) {
	if (val == "none") {
		return GL_NONE;
	} else if (val == "back") {
		return GL_BACK;
	} else if (val == "front") {
		return GL_FRONT;
	}
	return GL_FRONT_AND_BACK;
}

int Globals::setOrder(std::string val) {
	if (val == "cw") {
		return GL_CW;
	}
	return GL_CCW;
}

int Globals::getDmode() {
	return dmode;
}

int Globals::getShading() {
	return shading;
}

float Globals::getBackground(int pos) {
	return background[pos];
}

int Globals::getFace() {
	return face;
}

int Globals::getOrder() {
	return order;
}

bool Globals::getDsided() {
	return dsided;
}

bool Globals::getLocal() {
	return local;
}

bool Globals::getEnabled() {
	return enabled;
}

float Globals::getAmbient(int pos) {
	return ambient[pos];
}

float* Globals::getAmbient() {
	return ambient;
}