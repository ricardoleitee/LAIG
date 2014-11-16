#include <CGF/CGFlight.h>


class Light : public CGFlight
//class Light
{
	std::string id;
	bool enabled;
	float ambi[4], diff[4], spec[4];
	float pos[3];
	int lightid;

public:
	Light(std::string id, float *ambi, float *diff, float *spec, bool enabled, unsigned int lightid, float *pos, float *dir);
	~Light();
	std::string getID();
	int getLightId();
	virtual void setVariables();
	float* getAmbient();
	float* getSpecular();
	float* getDiffuse();
	bool getEnabled();
	float* getPosition();
};