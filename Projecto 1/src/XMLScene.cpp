#include "XMLScene.h"

XMLScene::XMLScene(char *filename)
{

	// Read XML from file

	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		exit( 1 );
	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		exit(1);
	}

	globalsElement = anfElement->FirstChildElement( "globals" );
	readGlobalsElement();
	camerasElement = anfElement->FirstChildElement( "cameras" );
	readCamerasElement();
	lightsElement =  anfElement->FirstChildElement( "lights" );
	readLightsElement();
	texturesElement =  anfElement->FirstChildElement( "textures" );
	readTexturesElement();
	appearancesElement =  anfElement->FirstChildElement( "appearances" );
	readAppearancesElement();
	graphElement =  anfElement->FirstChildElement( "graph" );	
	readGraphElement();
}

void XMLScene::readGlobalsElement(){
	std::string dmode, shading, face, order;
	float background[4], ambient[4];
	unsigned int dsided, local, enabled;

	if (globalsElement == NULL)
		printf("Globals block not found!\n");
	else {
		printf("Processing globals:\n");
		printf("\n");
		TiXmlElement* drawing=globalsElement->FirstChildElement("drawing");
		if (drawing) {
			printf("Processing drawing element:\n");
			dmode = readString("mode",drawing);
			shading = readString("shading",drawing);
			read4Float("background",drawing,background);			
		} else {
			printf("drawing element not found!\n");
		}
		TiXmlElement* culling=globalsElement->FirstChildElement("culling");
		if (culling) {
			printf("Processing culling element:\n");
				face = readString("face",culling);
				order = readString("order",culling);
		}else {
			printf("culling element not found!\n");
		}
		TiXmlElement* lighting=globalsElement->FirstChildElement("lighting");
		if (lighting) {
			printf("Processing lighting element:\n");
				dsided = readBool("doublesided",lighting);
				local = readBool("local",lighting);
				enabled = readBool("enabled",lighting);
				read4Float("ambient",lighting,ambient);
		}else {
			printf("lighting element not found!\n");
		}		
			globals = new Globals(dmode, shading, background, face, order, dsided, local, enabled, ambient);
			printf("\n");
			printf("\n");
	}	
}

void XMLScene::readCamerasElement(){
	std::string initial, id, direction;
	float near, far, angle, left, right, top, bottom;
	float pos[3], target[3];

	if (camerasElement == NULL)
		printf("Cameras block not found!\n");
	else {
		printf("Processing cameras:\n");
		printf("\n");
		initial = readString("initial", camerasElement);
		printf("\n");

		TiXmlElement* perspectiveElement = camerasElement->FirstChildElement( "perspective" );
		if(perspectiveElement != NULL){
			while (perspectiveElement) {
				id = readString("id", perspectiveElement);
				near = readFloat("near", perspectiveElement);
				far = readFloat("far", perspectiveElement);
				angle = readFloat("angle", perspectiveElement);
				read3Float("pos",perspectiveElement,pos);
				read3Float("target",perspectiveElement,target);

				cameras.push_back(new PerspectiveCamera(id, near, far, angle, pos, target,initial));
				perspectiveElement = perspectiveElement->NextSiblingElement("perspective");
				printf("\n");
			}
		} else {
			printf("perspective element not found!\n");
		}
		TiXmlElement* orthoElement = camerasElement->FirstChildElement( "ortho" );
		if(orthoElement != NULL){
			while (orthoElement) {
				id = readString("id", orthoElement);
				direction = readString("direction", orthoElement);
				near = readFloat("near", orthoElement);
				far = readFloat("far", orthoElement);
				left = readFloat("left", orthoElement);
				right = readFloat("right", orthoElement);
				top = readFloat("top", orthoElement);
				bottom = readFloat("bottom", orthoElement);

				cameras.push_back(new OrthoCamera(id, direction, near, far, left, right, top, bottom,initial));
				orthoElement = orthoElement->NextSiblingElement("ortho");
				printf("\n");
			}
		} else {
			printf("ortho element not found!\n");
		}
	}
	printf("\n");
	printf("\n");
}

void XMLScene::readLightsElement(){
	unsigned int idLight = GL_LIGHT0;
	std::string id, light_type, comp_type;
	float enabled, marker;
	float pos[3], ambi_val[4], diff_val[4], spec_val[4], target[4];

	if (lightsElement == NULL)
		printf("Lights block not found!\n");
	else {
		printf("Processing lights:\n");
		printf("\n");

		TiXmlElement* lightElement = lightsElement->FirstChildElement( "light" );
		if (lightElement != NULL) {
				while (lightElement) {
				id = readString("id", lightElement);
				light_type = readString("type", lightElement);
				enabled = readBool("enabled", lightElement);
				marker = readBool("marker", lightElement);
				read3Float("pos", lightElement, pos);

				TiXmlElement* componentElement = lightsElement->FirstChildElement( "component" );			
				TiXmlElement* compAmbiElement = findChildByAttribute(lightElement,"type","ambient");
				if (compAmbiElement) {
					comp_type = readString("type", compAmbiElement);
					read4Float("value",compAmbiElement,ambi_val);
				} else {
					printf("ambient component element not found!\n");
				}
				TiXmlElement* compDiffElement = findChildByAttribute(lightElement,"type","diffuse");
				if (compDiffElement) {
					comp_type = readString("type", compDiffElement);
					read4Float("value",compDiffElement,diff_val);
				} else {
					printf("diffuse component element not found!\n");
				}
				TiXmlElement* compSpecElement = findChildByAttribute(lightElement,"type","specular");
				if (compSpecElement) {
					comp_type = readString("type", compSpecElement);
					read4Float("value",compSpecElement,spec_val);
				} else {
					printf("specular component element not found!\n");
				}

				if(strcmp(lightElement->Attribute("type"),"spot")==0) {
					read3Float("target", lightElement, target);
					lights.push_back(new Light(id, ambi_val, diff_val, spec_val, enabled, idLight, pos, target));
					idLight++;
				} else if (strcmp(lightElement->Attribute("type"),"omni")==0){
					lights.push_back(new Light(id, ambi_val, diff_val, spec_val, enabled, idLight, pos, NULL));
					idLight++;
				} else {
					printf("wrong light element type!\n");
				}
				lightElement = lightElement->NextSiblingElement("light");
				printf("\n");
				}
			} else {
			printf("light element not found!\n");
		}		
	}
}

void XMLScene::readTexturesElement(){
	std::string id, file;
	float texlength_s, texlength_t;

	if (texturesElement == NULL)
		printf("Textures block not found!\n");
	else {
		printf("Processing textures:\n");
		printf("\n");

		TiXmlElement* textureElement = texturesElement->FirstChildElement( "texture" );
		if(textureElement != NULL) {
			while(textureElement) {				
				id = readString("id", textureElement);
				file = readString("file", textureElement);
				texlength_s = readFloat("texlength_s", textureElement);
				texlength_t = readFloat("texlength_t", textureElement);

				Texture* t = new Texture(id, file, texlength_s, texlength_t);
				textures[id] = t;
				textureElement = textureElement->NextSiblingElement("texture");
				printf("\n");
			} 
		} else {
			printf("texture element not found!\n");
		}
	}
}

void XMLScene::readAppearancesElement() {
	std::string id, textref, comp_type;
	float shininess;
	float ambi_val[4], diff_val[4], spec_val[4];
	Appearance* appearance;

	if (appearancesElement == NULL) {
		printf("Appearances block not found!\n");
	} else {
		printf("Processing appearances:\n");
		printf("\n");

		TiXmlElement* appearanceElement = appearancesElement->FirstChildElement( "appearance" );
		if (appearanceElement != NULL) {
			while (appearanceElement) {
				id = readString("id", appearanceElement);
				shininess = readFloat("shininess", appearanceElement);				

				//TiXmlElement* componentElement = lightsElement->FirstChildElement( "component" );			
				TiXmlElement* compAmbiElement = findChildByAttribute(appearanceElement,"type","ambient");
				if (compAmbiElement) {
					comp_type = readString("type", compAmbiElement);
					read4Float("value",compAmbiElement,ambi_val);
				} else {
					printf("ambient component element not found!\n");
				}
				TiXmlElement* compDiffElement = findChildByAttribute(appearanceElement,"type","diffuse");
				if (compDiffElement) {
					comp_type = readString("type", compDiffElement);
					read4Float("value",compDiffElement,diff_val);
				} else {
					printf("diffuse component element not found!\n");
				}
				TiXmlElement* compSpecElement = findChildByAttribute(appearanceElement,"type","specular");
				if (compSpecElement) {
					comp_type = readString("type", compSpecElement);
					read4Float("value",compSpecElement,spec_val);
				} else {
					printf("specular component element not found!\n");
				}

				if((char *) appearanceElement->Attribute("textureref") != NULL){
					textref = readString("textureref", appearanceElement);

					Texture* t = textures[textref];
					appearance = new Appearance(id, shininess, ambi_val, diff_val, spec_val, textref, t->getTextlS(), t->getTextlT());
					appearances[id] = appearance;
				}else{
					appearance = new Appearance(id, shininess, ambi_val, diff_val, spec_val);
					appearances[id] = appearance;
				} 

				appearanceElement = appearanceElement->NextSiblingElement("appearance");
				printf("\n");
			}
		} else {
			printf("appearance element not found\n");
		}
	}
}

void XMLScene::readGraphElement() {
	std::string nodeId, apprefId, noderefId, type;
	char axis;
	float to[3], factor[3], xy1[2], xy2[2], xyz1[3], xyz2[3], xyz3[3];
	float base, top, height, radius, inner, outer, angle;
	unsigned int slices, stacks, loops;
	bool displayList = false;

	if (graphElement == NULL) {
		printf("Graph block not found!\n");
	} else {
		printf("Processing graph:\n");
		printf("\n");

		rootId = readString("rootid",graphElement);
		TiXmlElement* nodeElement = graphElement->FirstChildElement("node");
		if (nodeElement != NULL) {
			while(nodeElement) {

				node = new Node();
				nodeId = readString("id", nodeElement);
				node->setRootId(nodeId);
//				printf("\n");
				displayList = readBool("displaylist", nodeElement);
				node->setDisplayList(displayList);

				TiXmlElement* transformsElement = nodeElement->FirstChildElement("transforms");
				if (transformsElement != NULL) {
					TiXmlElement* transformElement = transformsElement->FirstChildElement("transform");
					if (transformElement != NULL) {
						while (transformElement) {
							if (strcmp(transformElement->Attribute("type"), "translate") == 0) {
								type = readString("type", transformElement);
								read3Float("to", transformElement, to);
								//SAVE TRANSLATE TRANSFORM TO NODE
								node->addTransform(new Translate(to[0],to[1],to[2]));
							} else if (strcmp(transformElement->Attribute("type"), "rotate") == 0) {
								type = readString("type", transformElement);
								axis = readChar("axis", transformElement);
								angle = readFloat("angle", transformElement);
								//SAVE ROTATE TRANSFORM TO NODE
								node->addTransform(new Rotate(axis, angle));
							} else if (strcmp(transformElement->Attribute("type"), "scale") == 0) {
								type = readString("type", transformElement);
								read3Float("factor", transformElement, factor);
								//SAVE SCALE TRANSFORM TO NODE
								node->addTransform(new Scale(factor[0],factor[1],factor[2]));
							} else {
//								printf("wrong transform type\n");
							}

							transformElement = transformElement->NextSiblingElement("transform");
//							printf("\n");
						}
					} else {
//						printf("node without transforms\n");
					}
				} else {
//					printf("transforms element not found\n");
				}

				TiXmlElement* apprefElement = nodeElement->FirstChildElement("appearanceref");
				if (apprefElement != NULL) {
					apprefId = readString("id", apprefElement);
					node->setAppref(apprefId);
				} else {
//					printf("appearanceref element not found\n");
				}

				TiXmlElement* primitivesElement = nodeElement->FirstChildElement("primitives");
				if (primitivesElement != NULL) {
					TiXmlElement* rectangleElement = primitivesElement->FirstChildElement("rectangle");
					if (rectangleElement != NULL) {
						while (rectangleElement) {
							read2Float("xy1", rectangleElement, xy1);
							read2Float("xy2", rectangleElement, xy2);

							//ADD RECTANGLE
							node->addPrimitive(new Rectangle(xy1[0],xy1[1],xy2[0],xy2[1]));
							rectangleElement = rectangleElement->NextSiblingElement("rectangle");
						}
					} else {
//						printf("rectangle element not found\n");
					}
					TiXmlElement* triangleElement = primitivesElement->FirstChildElement("triangle");
					if (triangleElement != NULL) {
						while (triangleElement) {
							read3Float("xyz1", triangleElement, xyz1);
							read3Float("xyz2", triangleElement, xyz2);
							read3Float("xyz3", triangleElement, xyz3);

							//ADD TRIANGLE
							node->addPrimitive(new Triangle(xyz1[0],xyz1[1],xyz1[2],xyz2[0],xyz2[1],xyz2[2],xyz3[0],xyz3[1],xyz3[2]));
							triangleElement = triangleElement->NextSiblingElement("triangle");
						}
					} else {
//						printf("triangle element not found\n");
					}
					TiXmlElement* cylinderElement = primitivesElement->FirstChildElement("cylinder");
					if (cylinderElement != NULL) {
						while (cylinderElement) {
							base = readFloat("base", cylinderElement);
							top = readFloat("top", cylinderElement);
							height = readFloat("height", cylinderElement);
							slices = readInt("slices", cylinderElement);
							stacks = readInt("stacks", cylinderElement);

							//ADD CYLINDER
							node->addPrimitive(new Cylinder(base,top,height,slices,stacks));
							cylinderElement = cylinderElement->NextSiblingElement("cylinder");
						}
					} else {
//						printf("cylinder element not found\n");
					}
					TiXmlElement* sphereElement = primitivesElement->FirstChildElement("sphere");
					if (sphereElement != NULL) {
						while (sphereElement) {
							radius = readFloat("radius", sphereElement);
							slices = readInt("slices", sphereElement);
							stacks = readInt("stacks", sphereElement);

							//ADD SPHERE
							node->addPrimitive(new Sphere(radius,slices,stacks));
							sphereElement = sphereElement->NextSiblingElement("sphere");
						}
					} else {
//						printf("sphere element not found\n");
					}
					TiXmlElement* torusElement = primitivesElement->FirstChildElement("torus");
					if (torusElement != NULL) {
						while (torusElement) {
							inner = readFloat("inner", torusElement);
							outer = readFloat("outer", torusElement);
							slices = readInt("slices", torusElement);
							loops = readInt("loops", torusElement);

							//ADD TORUS
							node->addPrimitive(new Torus(inner,outer,slices,loops));
							torusElement = torusElement->NextSiblingElement("torus");
						}
					} else {
//						printf("torus element not found\n");
					}
				} else {
//					printf("primitives element not found\n");
				} 

				TiXmlElement* descendantsElement = nodeElement->FirstChildElement("descendants");
				if (descendantsElement != NULL) {
					TiXmlElement* noderefElement = descendantsElement->FirstChildElement("noderef");
					if (noderefElement != NULL) {
						while (noderefElement) {
							noderefId = readString("id", noderefElement);

							//ADD NODEREF ID
							node->addDescendant(noderefId);
							noderefElement = noderefElement->NextSiblingElement("noderef");
						}
					} else {
//							printf("noderef element not found\n");
					}
				} else {
//					printf("descendants element not found\n");
				}

				scene[nodeId] = node;
//				printf("Nó: %s\n", node);
//				printf("appearanceref: %s\n",node->getAppref());
				//printf("Nó: %s", node);
				//scene[nodeId] = node;
				//scene.insert(map<string,Node*>::value_type(nodeId,node));
				nodeElement = nodeElement->NextSiblingElement("node");
//				printf("\n");
//				printf("\n");
			}
		} else {
//			printf("node element not found\n");
		}
		//SET INHERIT APPEARANCES
		setAppNodes(scene, rootId);
	}
}

void XMLScene::setAppNodes(map<string,Node*> fscene,std::string id) {
	Node* aux = fscene[id];
	Node* aux2 = new Node();
	std::string apprefId = aux->getAppref();

	for(unsigned int l=0 ; l<aux->getDescendants().size() ; l++){
		aux2 = fscene[aux->getDescendants()[l]];
		if(aux2->getAppref() == "inherit"){
			aux2->setAppref(apprefId);
		}
		setAppNodes(fscene, aux->getDescendants()[l]);
	}
}

vector<Light*> XMLScene::getLights(){
	return lights;
}

Globals* XMLScene::getGlobals(){
	return globals;
}

vector<Camera*> XMLScene::getCameras(){
	return cameras;
}

string XMLScene::getRootId(){
	return rootId;
}

map<string,Texture*> XMLScene::getTextures(){
	return textures;
}

map<string, Node*> XMLScene::getScene(){
	return scene;
}

map<string, Appearance*> XMLScene::getAppearances(){
	return appearances;
}

unsigned int XMLScene::readInt(char* attribute,TiXmlElement* element){
	char *valString=NULL;
	unsigned int  i=0;

	valString=(char *) element->Attribute(attribute);

	if(valString && sscanf(valString,"%i",&i)==1){
//		printf("%s: %i\n", attribute, i);
	}else{
//		printf("%s attribute not found!\n", attribute);
	}
	return i;
}

char XMLScene::readChar(char* attribute,TiXmlElement* element){
	char *valString=NULL;
	char c=NULL;

	valString=(char *) element->Attribute(attribute);

	if(valString && sscanf(valString,"%c",&c)==1){
//		printf("%s: %c\n", attribute, c);
	}else{
//		printf("%s attribute not found!\n", attribute);
	}
	return c;
}

float XMLScene::readFloat(char* attribute,TiXmlElement* element){
	char *valString=NULL;
	float f=0;

	valString=(char *) element->Attribute(attribute);

	if(valString && sscanf(valString,"%f",&f)==1){
//		printf("%s: %f\n", attribute, f);
	}else{
//		printf("%s attribute not found!\n", attribute);
	}
	return f;
}

void XMLScene::read2Float(char* attribute,TiXmlElement* element, float* flt){
	char *valString=NULL;

	valString=(char *) element->Attribute(attribute);

	if(valString && sscanf(valString,"%f %f ",&flt[0], &flt[1])==2){
//		printf("%s: %f %f\n", attribute, flt[0], flt[1]);
	}else{
//		printf("%s attribute not found!\n", attribute);
	}
}

void XMLScene::read3Float(char* attribute,TiXmlElement* element, float* flt){
	char *valString=NULL;

	valString=(char *) element->Attribute(attribute);

	if(valString && sscanf(valString,"%f %f %f",&flt[0], &flt[1], &flt[2])==3){
//		printf("%s: %f %f %f\n", attribute, flt[0], flt[1], flt[2]);
	}else{
//		printf("%s attribute not found!\n", attribute);
	}
}

void XMLScene::read4Float(char* attribute,TiXmlElement* element, float* flt){
	char *valString=NULL;

	valString=(char *) element->Attribute(attribute);

	if(valString && sscanf(valString,"%f %f %f %f",&flt[0], &flt[1], &flt[2], &flt[3])==4){
//		printf("%s: %f %f %f %f\n", attribute, flt[0], flt[1], flt[2], flt[3]);
	}else{
//		printf("%s attribute not found!\n", attribute);
	}
}

std::string XMLScene::readString(char* attribute, TiXmlElement* element){
	char *valString=NULL;
	valString=(char *) element->Attribute(attribute);
//	std::string stg;
	char stg[100];

	if(valString && sscanf(valString,"%s",stg)==1){
//		printf("%s: %s\n",attribute,stg );
	}else{
//		printf("%s attribute not found!\n", attribute);
	}

	return std::string(stg);
}

int XMLScene::readBool(char* attribute, TiXmlElement* element){
	std::string stg = readString(attribute, element);

	if(stg.compare("true")==0){
		return 1;
	}
	return 0;
}

XMLScene::~XMLScene()
{
	delete(doc);
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


