#include "Camera.h"

std::string Camera::initial;
Camera::Camera(std::string id, float n, float f,std::string initial)
{	this->initial=initial;
	this->id=id;
	this->n=n;
	this->f=f;
}
std::string Camera::getInicial(){
	return initial;
}

Camera::~Camera(void)
{
}

std::string Camera::getId(){
	return id;
}
	
float Camera::getNear(){
	return n;
}
	
float Camera::getFar(){
	return f;
}

OrthoCamera::OrthoCamera(std::string id,std::string direction, float n, float f, float left, float right, float top , float bottom, std::string initial):Camera(id, n, f,initial){
	this->direction = direction;
	this->left=left;
	this->right=right;
	this->top=top;
	this->bottom=bottom;
}

std::string OrthoCamera::getDirection() {
	return direction;
}

float OrthoCamera::getLeft(){
	return left;
}
	
float OrthoCamera::getRight(){
	return right;
}
	
float OrthoCamera::getTop(){
	return top;
}
	
float OrthoCamera::getBottom(){
	return bottom;
}

void OrthoCamera::applyView(){
/*	if (this->getDirection() == "x") {
		glRotatef(90.f, 0.f, 1.f, 0.f);
	} else if (this->getDirection() == "y") {
		glRotatef(90, 1.f, 0.f, 0.f);
	}
	//updateProjectionMatrix(1920,1080);*/
}

PerspectiveCamera::PerspectiveCamera(std::string id, float n, float f, float angle, float* pos, float* tar, std::string initial):Camera(id, n, f, initial){
	this->angle=angle;
	for(int i=0 ; i<3 ; i++){
		//this->pos[i]=pos[i];
		position[i] = pos[i];
		target[i] = tar[i];
		//this->tar[i]=tar[i];
	}
}

float PerspectiveCamera::getAngle(){
	return angle;
}
	
float* PerspectiveCamera::getPos(){
	return pos;
}
	
float* PerspectiveCamera::getTarget(){
	return tar;
}

void PerspectiveCamera::applyView(){
	if (mode==EXAMINE_MODE)
	{
		glTranslatef(position[0],position[1], position[2]);
		// glTranslatef(0, 0, position[2]); // or this, if we ignore panning

		glRotatef(rotation[0], 1.f, 0.f, 0.f);
		glRotatef(rotation[1], 0.f, 1.f, 0.f);
		glRotatef(rotation[2], 0.f, 0.f, 1.f);

	}
	else
	{
		glRotatef(rotation[0], 1.f, 0.f, 0.f);
		glRotatef(rotation[1], 0.f, 1.f, 0.f);
		glRotatef(rotation[2], 0.f, 0.f, 1.f);

		glTranslatef(position[0], position[1], position[2]);
	}
	//gluLookAt(getPos()[0],getPos()[1],getPos()[2],getTarget()[0],getTarget()[1],getTarget()[2],0.0,1.0,0.0);
	gluLookAt(position[0],position[1],position[2],target[0],target[1],target[2],0.0,1.0,0.0);

}

void PerspectiveCamera::updateProjectionMatrix(int width, int height){
	float aspect = (float) width / (float) height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(getAngle(),aspect,getNear(), getFar());
}


void OrthoCamera::updateProjectionMatrix(int width, int height){
	float aspect = (float) width / (float) height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(getLeft(),getRight(),getBottom(),getTop(),getNear(),getFar());
}
