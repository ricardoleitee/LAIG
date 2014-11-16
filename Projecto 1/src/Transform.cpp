#include "Transform.h"

Transform::Transform() {
}

Transform::~Transform() {
}

void::Transform::apply() {
}

Translate::Translate(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Translate::apply(){
	glTranslated(x,y,z);
}

float Translate::getX(){
	return x;
}
	
float Translate::getY(){
	return y;
}
	
float Translate::getZ(){
	return z;
}

void Translate::setX(float x){
	this->x = x;
}
	
void Translate::setY(float y){
	this->y = y;
}
	
void Translate::setZ(float z){
	this->z = z;
}

Rotate::Rotate(char axis, float angle){
	this->axis = axis;
	this->angle = angle;
}
	
void Rotate::apply(){
	if(axis == 'x'){
		glRotated(angle,1,0,0);
	}else if(axis == 'y'){
		glRotated(angle,0,1,0);
	}else if(axis == 'z'){
		glRotated(angle,0,0,1);
	}
}

char Rotate::getAxis(){
	return axis;
}

float Rotate::getAngle(){
	return angle;
}

void Rotate::setAxis(char axis){
	this->axis = axis;
}

void Rotate::setAngle(float angle){
	this->angle = angle;
}

Scale::Scale(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Scale::apply(){
	glScaled(x,y,z);
}

float Scale::getX(){
	return x;
}
	
float Scale::getY(){
	return y;
}
	
float Scale::getZ(){
	return z;
}

void Scale::setX(float x){
	this->x = x;
}
	
void Scale::setY(float y){
	this->y = y;
}
	
void Scale::setZ(float z){
	this->z = z;
}