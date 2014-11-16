#include "Interface.h"

void Interface::initGUI()
{
	GLUI_Panel *lightPanel= addPanel("Lights",1);
	for(unsigned int i=0;i<((Scene*) scene)->lightState.size();i++){
		char name[30]="";
		std::string s = ((Scene*) scene)->lights[i]->getID();
		sprintf(name, "%s", s.c_str());
		addCheckboxToPanel(lightPanel,name,&(((Scene*) scene)->lightState[i]),0);
	}

	addColumn();

	GLUI_Panel *cameraPanel= addPanel("Cameras",1);
	if(((Scene*) scene)->cameras.size()<5){
		GLUI_RadioGroup *radioCameras=addRadioGroupToPanel(cameraPanel,&((Scene*) scene)->camera,1);
		for(unsigned int i=0;i<((Scene*) scene)->cameras.size();i++){
			char name[30]="";
			std::string s =((Scene*) scene)->cameras[i]->getId();
			sprintf(name, "%s", s.c_str());
			addRadioButtonToGroup(radioCameras,name);
		}
	}
	else{
		GLUI_Listbox *listbox = addListboxToPanel(cameraPanel,"Cameras",&((Scene*) scene)->camera,2);

		for(unsigned int i=0;i<2;i++){
			char name[30]="";
			std::string s =((Scene*) scene)->cameras[i]->getId();
			sprintf(name, "%s", s.c_str());
			listbox->add_item(i,name);
			((Scene*) scene)->camera= listbox->get_int_val();
		}
	}

	addColumn();

	GLUI_Panel *drawmodePanel= addPanel("Drawmode",1);
	GLUI_RadioGroup *radioDrawmode=addRadioGroupToPanel(drawmodePanel,&((Scene*) scene)->drawmode,3);
	addRadioButtonToGroup(radioDrawmode,"Point");
	addRadioButtonToGroup(radioDrawmode,"Line");
	addRadioButtonToGroup(radioDrawmode,"Fill");

	addColumn();
}

void Interface::processGUI(GLUI_Control *ctrl)
{
	printf ("GUI control id: %d\n  ",ctrl->user_id);
	switch (ctrl->user_id)
	{
	case 0:
		for(unsigned int i=0;i<((Scene*) scene)->lightState.size();i++){
			printf ("New Light %d: %d\n",i,((Scene*) scene)->lightState[i]);
		}
		break;
	case 4:
		((Scene*) scene)->appChoose=false;
		break;
	};
}

void Interface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
}