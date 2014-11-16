#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include <CGF/CGFlight.h>
#include "Light.h"

class SpotLight:public Light {
	float angle, exp;
	float direction[3];
	float id;

public:
	SpotLight(float angle, float exp, std::string id, float* ambi, float *diff,float* spec, bool enabled, unsigned int lightid, float *pos, float *dir);
	~SpotLight();
	float getAngle();
	float* getDirection();
	float getExponent();
	void setVariables();
	bool getEnabled();
};

#endif