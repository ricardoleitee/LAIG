#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "CGFinterface.h"
#include "Scene.h"

class Interface: public CGFinterface {
public:
	virtual void initGUI();
	virtual void processGUI(GLUI_Control * ctrl);

	virtual void processMouse(int button, int state, int x, int y);
};

#endif
