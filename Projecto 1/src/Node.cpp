#include "Node.h"

Node::Node() {
	appref = "lol";
}

Node::~Node() {
}

void Node::setRootId(string id) {
	rootId = id;
}
	
void Node::addTransform(Transform* t){
	transforms.push_back(t);
}
	
void Node::addPrimitive(Primitive* p){
	primitives.push_back(p);
}
	
void Node::addDescendant(string d){
	descendants.push_back(d);
}

void Node::setAppref(std::string appref){
	this->appref = appref;
}

vector<Transform*> Node::getTransforms(){
	return transforms;
}
	
vector<Primitive*> Node::getPrimitives(){
	return primitives;
}
	
vector<string> Node::getDescendants(){
	return descendants;
}
	
string Node::getAppref(){
	return appref;
}

string Node::getRootId(){
	return rootId;
}

void Node::setDisplayList(bool dt) {
	displayList = dt;
}