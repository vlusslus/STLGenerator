#pragma once
#include "Vertex.h"
#include <vector>

using namespace std;

class Base
{
private:

	vector <Vertex> vertices;
	
public:
	Base();
	~Base();

	void AddVertex(Vertex* vertex);
	string toString();

};

