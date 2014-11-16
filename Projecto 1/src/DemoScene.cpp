#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "ExampleObject.h"
#include <math.h>

#include "CGFappearance.h"

#include "Primitive.h"
#include "Texture.h"
#include "Appearance.h"
#include <string>
#include "Camera.h"

void DemoScene::init() 
{
	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light
	
	// Declares and enables a light
	float light0_pos[4] = {10.0, 15.0, 20.0, 1.0};
	//float ambient_light[4] = {;
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	//light0->setAmbient();
	light0->enable();

	// Defines a default normal
	glNormal3f(0,0,1);

	//obj=new ExampleObject();
	materialAppearance=new CGFappearance();
	textureAppearance=new CGFappearance("../data/base.jpg",GL_REPEAT, GL_REPEAT);
	textureAppearance2=new CGFappearance("../data/stairs.jpg",GL_REPEAT, GL_REPEAT);
	textureAppearance3=new CGFappearance("../data/wall.jpg",1, 1);
	textureAppearance4=new CGFappearance("../data/roof.jpg",GL_REPEAT, GL_REPEAT);
	textureAppearance5=new CGFappearance("../data/door.jpg",GL_REPEAT, GL_REPEAT);
	textureAppearance6=new CGFappearance("../data/window.jpg",GL_REPEAT, GL_REPEAT);
	shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");

	setUpdatePeriod(30);
}

void DemoScene::update(unsigned long t)
{
	shader->bind();
	shader->update(t/400.0);
	shader->unbind();
	
}
	
void DemoScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	std::string id = "camera0";
	std::string direction = "y";
	float near = -20.0;
	float far = 20.0;
	float left = -5.0;
	float right = 25.0;
	float top = 20.0;
	float bottom = -5.0;

	OrthoCamera* cam = new OrthoCamera(id, direction,near,far,left,right,top,bottom,id);
	//cam->updateProjectionMatrix(1929,1080);
	//CGFscene::activeCamera->applyView();
	cam->applyView();

	// Draw (and update) light
	light0->draw();

	// Draw axis
	axis.draw();


	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos
/*	float shininess = 0.2;
	float ambi_val[4] = {0.5,0.5,0.5,0.5};
	float diff_val[4] = {0.5,0.5,0.5,0.5};
	float spec_val[4] = {0.5,0.5,0.5,0.5};
	std::string idtex = "wall";
	std::string filetex = "data/walls.jpg";
	std::string aid = "app";


	Texture* tex = new Texture(idtex,filetex,1.0,1.0);
	Appearance* a = new Appearance(aid,shininess,ambi_val,diff_val,spec_val,idtex,1.0,1.0);*/
//	Triangle* t = new Triangle(0.0,0.0,0.0, 15.0,0.0,0.0, 7.5,7.0,0.0);
//	textureAppearance3->apply();
/*	glBegin(GL_TRIANGLES);
	glTexCoord2d(0,0);
	glVertex3d(0,8,0);
	glTexCoord2d(0,1);
	glVertex3d(0,8,15);
	glTexCoord2d(0.5,0.5);
	glVertex3d(0,15,7.5);
	glEnd();*/
//	t->draw();

	textureAppearance->apply();	
	//FRONT BASE
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(0,0,0);
		glTexCoord2d(1,0);
		glVertex3d(0,0,15);
		glTexCoord2d(1,1);
		glVertex3d(0,1,15);
		glTexCoord2d(0,1);
		glVertex3d(0,1,0);		
	glEnd();

	//FIRST SIDE BASE
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(0,0,15);
		glTexCoord2d(1,0);
		glVertex3d(20,0,15);
		glTexCoord2d(1,1);
		glVertex3d(20,1,15);
		glTexCoord2d(0,1);
		glVertex3d(0,1,15);		
	glEnd();
	
		//BACK SIDE BASE
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(20,0,15);
		glTexCoord2d(1,0);
		glVertex3d(20,0,0);
		glTexCoord2d(1,1);
		glVertex3d(20,1,0);
		glTexCoord2d(0,1);
		glVertex3d(20,1,15);		
	glEnd();

		//SECOND SIDE BASE
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(20,0,0);
		glTexCoord2d(1,0);
		glVertex3d(0,0,0);
		glTexCoord2d(1,1);
		glVertex3d(0,1,0);
		glTexCoord2d(0,1);
		glVertex3d(20,1,0);		
	glEnd();

	textureAppearance2->apply();
		//FRONT FIRST PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(8,0,17);
		glTexCoord2d(1,0);
		glVertex3d(12,0,17);
		glTexCoord2d(1,1);
		glVertex3d(12,0.5,17);
		glTexCoord2d(0,1);
		glVertex3d(8,0.5,17);		
	glEnd();

		//FRONT SECOND PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(8,0.5,17);
		glTexCoord2d(1,0);
		glVertex3d(12,0.5,17);
		glTexCoord2d(1,1);
		glVertex3d(12,0.5,16);
		glTexCoord2d(0,1);
		glVertex3d(8,0.5,16);		
	glEnd();

		//FRONT THIRD PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(8,0.5,16);
		glTexCoord2d(1,0);
		glVertex3d(12,0.5,16);
		glTexCoord2d(1,1);
		glVertex3d(12,1,16);
		glTexCoord2d(0,1);
		glVertex3d(8,1,16);		
	glEnd();

		//FRONT FOUR PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(8,1,16);
		glTexCoord2d(1,0);
		glVertex3d(12,1,16);
		glTexCoord2d(1,1);
		glVertex3d(12,1,15);
		glTexCoord2d(0,1);
		glVertex3d(8,1,15);		
	glEnd();

		//FIRST SIDE FIRST PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(8,0,15);
		glTexCoord2d(1,0);
		glVertex3d(8,0,17);
		glTexCoord2d(1,1);
		glVertex3d(8,0.5,17);
		glTexCoord2d(0,1);
		glVertex3d(8,0.5,15);		
	glEnd();

		//FIRST SIDE SECOND PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(8,0.5,15);
		glTexCoord2d(1,0);
		glVertex3d(8,0.5,16);
		glTexCoord2d(1,1);
		glVertex3d(8,1,16);
		glTexCoord2d(0,1);
		glVertex3d(8,1,15);		
	glEnd();

		//SECOND SIDE FIRST PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(12,0,17);
		glTexCoord2d(1,0);
		glVertex3d(12,0,15);
		glTexCoord2d(1,1);
		glVertex3d(12,0.5,15);
		glTexCoord2d(0,1);
		glVertex3d(12,0.5,17);		
	glEnd();

		//SECOND SIDE SECOND PART STAIRS
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(12,0.5,16);
		glTexCoord2d(1,0);
		glVertex3d(12,0.5,15);
		glTexCoord2d(1,1);
		glVertex3d(12,1,15);
		glTexCoord2d(0,1);
		glVertex3d(12,1,16);		
	glEnd();

	textureAppearance3->apply();
		//FRONT WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(0,1,0);
		glTexCoord2d(1,0);
		glVertex3d(0,1,15);
		glTexCoord2d(1,1);
		glVertex3d(0,8,15);
		glTexCoord2d(0,1);
		glVertex3d(0,8,0);		
	glEnd();

		//FIRST SIDE WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(0,1,15);
		glTexCoord2d(1,0);
		glVertex3d(20,1,15);
		glTexCoord2d(1,1);
		glVertex3d(20,8,15);
		glTexCoord2d(0,1);
		glVertex3d(0,8,15);		
	glEnd();

		//BACK WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(20,1,15);
		glTexCoord2d(1,0);
		glVertex3d(20,1,0);
		glTexCoord2d(1,1);
		glVertex3d(20,8,0);
		glTexCoord2d(0,1);
		glVertex3d(20,8,15);		
	glEnd();
	
		//BACK WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(20,1,0);
		glTexCoord2d(1,0);
		glVertex3d(0,1,0);
		glTexCoord2d(1,1);
		glVertex3d(0,8,0);
		glTexCoord2d(0,1);
		glVertex3d(20,8,0);		
	glEnd();

		//FRONT TOP WALL
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0,0);
		glVertex3d(0,8,0);
		glTexCoord2d(0,1);
		glVertex3d(0,8,15);
		glTexCoord2d(0.5,0.5);
		glVertex3d(0,15,7.5);
	glEnd();

		//BACK TOP WALL
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0,0);
		glVertex3d(20,8,15);
		glTexCoord2d(0,1);
		glVertex3d(20,8,0);
		glTexCoord2d(0.5,0.5);
		glVertex3d(20,15,7.5);
	glEnd();
	
		textureAppearance4->apply();
		//FIRST ROOF
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(0,8,15);
		glTexCoord2d(1,0);
		glVertex3d(20,8,15);
		glTexCoord2d(1,1);
		glVertex3d(20,15,7.5);
		glTexCoord2d(0,1);
		glVertex3d(0,15,7.5);		
	glEnd();

		//SECOND ROOF
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(20,8,0);
		glTexCoord2d(1,0);
		glVertex3d(0,8,0);
		glTexCoord2d(1,1);
		glVertex3d(0,15,7.5);
		glTexCoord2d(0,1);
		glVertex3d(20,15,7.5);		
	glEnd();

	textureAppearance5->apply();
		//DOOR
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(8.5,1,15.1);
		glTexCoord2d(1,0);
		glVertex3d(11.5,1,15.1);
		glTexCoord2d(1,1);
		glVertex3d(11.5,7,15.1);
		glTexCoord2d(0,1);
		glVertex3d(8.5,7,15.1);		
	glEnd();

	textureAppearance6->apply();
		//FIRST WINDOW FRONT WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(-0.1,4,1);
		glTexCoord2d(1,0);
		glVertex3d(-0.1,4,6);
		glTexCoord2d(1,1);
		glVertex3d(-0.1,7,6);
		glTexCoord2d(0,1);
		glVertex3d(-0.1,7,1);		
	glEnd();

		//SECOND WINDOW FRONT WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(-0.1,4,9);
		glTexCoord2d(1,0);
		glVertex3d(-0.1,4,14);
		glTexCoord2d(1,1);
		glVertex3d(-0.1,7,14);
		glTexCoord2d(0,1);
		glVertex3d(-0.1,7,9);		
	glEnd();

		//TOP FRONT WALL WINDOW
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(-0.1,9,6);
		glTexCoord2d(1,0);
		glVertex3d(-0.1,9,9);
		glTexCoord2d(1,1);
		glVertex3d(-0.1,13,9);
		glTexCoord2d(0,1);
		glVertex3d(-0.1,13,6);		
	glEnd();

		//FIRST WINDOW SIDE WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(1.5,4,15.1);
		glTexCoord2d(1,0);
		glVertex3d(6.5,4,15.1);
		glTexCoord2d(1,1);
		glVertex3d(6.5,7,15.1);
		glTexCoord2d(0,1);
		glVertex3d(1.5,7,15.1);		
	glEnd();

		//SECOND WINDOW SIDE WALL
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(13.5,4,15.1);
		glTexCoord2d(1,0);
		glVertex3d(18.5,4,15.1);
		glTexCoord2d(1,1);
		glVertex3d(18.5,7,15.1);
		glTexCoord2d(0,1);
		glVertex3d(13.5,7,15.1);		
	glEnd(); 
	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(shader);
	delete(textureAppearance);
	delete(materialAppearance);
	delete(obj);
	delete(light0);
}
