#pragma once

#include "Vertex.h"

class Facet
{
private:

	Vertex* A;
	Vertex* B;
	Vertex* C;
	Vertex N;

public:
	Facet(Vertex* A, Vertex* B, Vertex* C);
	~Facet();
};

