#include "Scene.h"
#include <CGF/CGFaxis.h>

Scene::Scene(Globals* globals, vector<Camera*> cameras,vector<Light*> lights, std::string id, map<string, Node*> scene, map<string, Appearance*> appearances, map<string,Texture*> textures) {
	this->globals = globals;
	this->lights = lights;

	this->cameras = cameras;
	for(unsigned int i=0 ; i<cameras.size() ; i++){
		scene_cameras.push_back(cameras[i]);
		if(cameras[0]->getInicial() == cameras[i]->getId()){
			camera=i;
		}
	}
	//scene_cameras.insert(scene_cameras.end(), cameras.begin(), cameras.end());

	this->id = id;
	this->scene = scene;
	this->app = 0;
	this->s = 1;
	this->t = 1;
	this->appChoose = true;
	this->appearances = appearances;
	this->textures = textures;
	this->drawmode = this->globals->getDmode()-GL_POINT;
}

void Scene::init() {
	//Init Globals

	glClearColor(globals->getBackground(0), globals->getBackground(1), globals->getBackground(2), globals->getBackground(3));
//	glClearColor(0.0,0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,globals->getDmode());
	glShadeModel(globals->getShading());
	glFrontFace(globals->getOrder());
	glCullFace(globals->getFace());

	//Init Lights
	if (globals->getEnabled()) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}

	cout << "GLOBAL LIGHTING: " << globals->getEnabled() << endl;
	cout << "GLOBAL DSIDED: " << globals->getDsided() << endl;
	cout << "GLOBAL LOCAL: " << globals->getLocal() << endl;
	cout << "GLOBAL AMBIENT: " << globals->getAmbient() << endl;
	
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, globals->getDsided());
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, globals->getLocal());
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globals->getAmbient());

	if(!lights.empty()){
		for(unsigned int i=0 ; i<lights.size() ; i++){
			lights[i]->setVariables();
			lightState.push_back(lights[i]->getEnabled());
		}
	}

	//Init Textures
	applyTextures(id);

	glEnable(GL_NORMALIZE);
}

void Scene::display() {
	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Apply transformations corresponding to the camera position relative to the origin
	//CGFscene::activeCamera->applyView();
	//cout << "CAMERA: " << camera << endl;

	for (int z=0 ; z<scene_cameras.size() ; z++) {
		cout << "CAMERAS: " << scene_cameras.at(z) << endl;
	}

	activateCamera(camera);
	//CGFscene::activeCamera->applyView();
 	activeCamera->applyView();
	//application->forceRefresh();
	//cameras[camera]->applyView();
	

	//Globals
	glPolygonMode(GL_FRONT_AND_BACK,GL_POINT+drawmode);

	// Draw (and update) lights
	for(int i=0;i<lightState.size();i++){
		if(lightState[i]==0){
			lights[i]->disable();
		}else{
			lights[i]->enable();
		}
		lights[i]->draw();
		lights[i]->update();
	}

	// Draw axis
	axis.draw();

	// ---- END Background, camera, lights and axis setup

	// ---- BEGIN feature demos

	drawPrimitives(id);

	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

void Scene::applyTextures(string id){
	Node* node = this->scene[id];
	float t, s;

	if(node->getAppref() != ""){
		std::string tempappref = node->getAppref();
		std::string temptref = appearances[tempappref]->getTextureref();
		Texture* temp= this->textures[temptref];
		s=appearances[node->getAppref()]->getTextlS();
		t=appearances[node->getAppref()]->getTextlT();
		appearances[node->getAppref()]->setTexture(temp->getFile());
		appearances[node->getAppref()]->setTextureWrap(s, t);
	}

	if(node->getPrimitives().size() != 0){
		for(unsigned int j=0 ; j<node->getPrimitives().size() ; j++){
			node->getPrimitives()[j]->setS(s);
			node->getPrimitives()[j]->setT(t);
		}
	}

	for(unsigned int k=0 ; k<node->getDescendants().size() ; k++){
		applyTextures(node->getDescendants()[k]);
	}

}

void Scene::drawPrimitives(string id){
	Node* node = scene[id];

	glPushMatrix();
	if(node->getTransforms().size() != 0){
		for(unsigned int j=0 ; j<node->getTransforms().size() ; j++){
			node->getTransforms()[j]->apply();
		}
	}

	if(node->getAppref() != ""){
		appearances[node->getAppref()]->apply();
	}	

	if(node->getPrimitives().size() != 0){
		for(unsigned int k=0 ; k<node->getPrimitives().size() ; k++){
			node->getPrimitives()[k]->draw();
		}
	}
	
	for(unsigned int l=0; l<node->getDescendants().size() ; l++){
			drawPrimitives(node->getDescendants()[l]);
	} 
	
	glPopMatrix();
}

Scene::~Scene() 
{
	for(unsigned int i=0;i<lights.size();i++){
		delete(lights[i]);
	}
}

void Scene::setLightState(int pos, int value){
	lightState[pos]=value;
}

int Scene::getLightState(int pos){
	return lightState[pos];
}