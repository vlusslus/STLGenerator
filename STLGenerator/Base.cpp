#include "stdafx.h"
#include "Base.h"


Base::Base()
{
}


Base::~Base()
{
}

void Base::AddVertex(Vertex* vertex)
{
	vertices.push_back(*vertex);
}

string Base::toString()
{
	string result;
	for (int i = 0; i < vertices.size(); i++) {
		result += "X: " + &vertices[i].getX + " " + "Y: " + &vertices[i].getY + " " + "Z: " + &vertices[i].getZ;
		result += "/n";
	}
}
