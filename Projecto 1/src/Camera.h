//#include <GL\glew.h>
#include <stdlib.h>
#include <GL\glut.h>
#include <CGF/CGFcamera.h>
#include <string>



class Camera:public CGFcamera
{	static std::string initial;
	std::string id;
	float n, f;

public:
	Camera(std::string id, float n, float f,std::string initial);
	~Camera(void);
	std::string getId();
	std::string getInicial();
	float getNear();
	float getFar();
};

class OrthoCamera:public Camera{
	std::string direction;
	float left,  right,  top ,  bottom;
public:
	OrthoCamera(std::string id, std::string direction, float n, float f, float left, float right, float top , float bottom, std::string initial);
	std::string getDirection();
	float getLeft();
	float getRight();
	float getTop();
	void updateProjectionMatrix(int width, int height);
	float getBottom();
	void applyView();
};

class PerspectiveCamera: public Camera{

	float angle;
	float pos[3], tar[3];

public:
	PerspectiveCamera(std::string id, float n, float f, float angle, float* pos, float* tar, std::string initial);
	float getAngle();
	void updateProjectionMatrix(int width, int height);
	float* getPos();
	float* getTarget();
	void applyView();
};