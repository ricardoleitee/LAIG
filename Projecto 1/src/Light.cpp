#include "Light.h"

Light::Light(std::string id,float* ambi, float *diff, float *spec, bool enabled, unsigned int lightid, float *pos,float*dir=NULL):CGFlight(lightid, pos,dir){
//	Light::Light(std::string id,float* ambi, float *diff, float *spec, bool enabled, unsigned int lightid, float *pos,float*dir=NULL){
	this->id = id;
	for (int i=0 ; i<4 ; i++){
		this->ambi[i] = ambi[i];
		this->diff[i] = diff[i];
		this->spec[i] = spec[i];
	}
	this->enabled = enabled;
//	this->setVariables();

	for (int j=0 ; j<3 ; j++) {
		this->pos[j] = pos[j];
	}
	this->lightid = lightid;
/*	if (enabled) {
		this->enable();
	} else{
		this->disable();
	} */
}

Light::~Light(){

}


std::string Light::getID(){
	return id;
}

int Light::getLightId() {
	return lightid;
}
float* Light::getAmbient(){
	return ambi;
}

float* Light::getSpecular(){
	return spec;
}
	
float* Light::getDiffuse(){
	return diff;
}

bool Light::getEnabled() {
	return enabled;
}

void Light::setVariables(){
	this->setAmbient(ambi);
	this->setSpecular(spec);
	this->setDiffuse(diff);
}

float* Light::getPosition() {
	return pos;
}
