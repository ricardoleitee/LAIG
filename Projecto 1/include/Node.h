#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <vector>
#include "Transform.h"
#include "Primitive.h"

class Node {
	string rootId, appref;
	vector<Transform*> transforms;
	vector<Primitive*> primitives;
	vector<string> descendants;
	bool displayList;

public:
	Node();
	~Node();

	void setRootId(string id);

	void addTransform(Transform* t);
	void addPrimitive(Primitive* p);
	void addDescendant(string d);

	string getAppref();
	void setAppref(string appref);

	vector<Transform*> getTransforms();
	vector<Primitive*> getPrimitives();
	vector<string> getDescendants();
	string getRootId();

	void setDisplayList(bool dt);
};

#endif