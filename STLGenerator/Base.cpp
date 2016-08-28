#include "stdafx.h"
#include "Base.h"


Base::Base()
{
}


Base::~Base()
{
}

void Base::AddVertex(Vertex vertex)
{
	vertices.push_back(vertex);
}

vector<Vertex> Base::GetVertices()
{
	return this->vertices;
}

