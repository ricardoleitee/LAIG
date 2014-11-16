/* 
 * G0_Base: projeto inicial de CGra
 * 
 */
//#include <GL\glew.h>
#include "XMLScene.h"
#include <iostream>
#include <exception>
#include <windows.h>
#include "tinyxml.h"
#include "tinystr.h"
#include "CGFapplication.h"
#include "Scene.h"
#include "DemoScene.h"
#include "Node.h"
#include "Interface.h"


using std::cout;
using std::exception;


int main(int argc, char* argv[]) {


	XMLScene xmlscene = XMLScene("../housescene.anf");
//	Sleep(1000000000);
	Scene* scene = new Scene(xmlscene.getGlobals(), xmlscene.getCameras(), xmlscene.getLights(), xmlscene.getRootId(), xmlscene.getScene(), xmlscene.getAppearances(), xmlscene.getTextures());

//	map<string, Node*> mteste = xmlscene.getScene();
/*	map<string, Appearance*> ateste = xmlscene.getAppearances();
//  map<string,Texture*> tteste = xmlscene.getTextures();
//	Node* nteste = mteste["leftbase"];
	typedef map<string, Appearance*>::const_iterator MapIterator;
	for (MapIterator iter = ateste.begin(); iter != ateste.end(); iter++) {
		cout << "Key: " << iter->first << endl;
		Appearance *aux = ateste[iter->first];
		cout << "APP SHINI: " << aux->getShininess() << endl;
		cout << "APP TEXTREF: " << aux->getTextureref() << endl;
		cout << "APP TEXTS: " << aux->getTextlS() << endl;
		cout << "APP TEXTT: " << aux->getTextlT() << endl;
	} */
	//appteste->apply();
//	std::string appref = nteste->getAppref();
	//Node* teste = new Node();
//	printf("Teste: %s", xmlscene.getRootId());
//	printf("Teste: %s", xmlscene.getRootId());
//	std::cout << "OUTPUT: " << nteste->getAppref();
//	Sleep(1000000000);

	CGFapplication app = CGFapplication();	

	try {
		app.init(&argc, argv);
		app.setScene(scene);
//		app.setScene(new DemoScene());
		app.setInterface(new Interface());
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	} 

	//Sleep(1000000000000000000);
	return 0; 
}