#pragma once

#include "Vertex.h"

class Facet
{
private:

	Vertex A;
	Vertex B;
	Vertex C;
	//Vertex O;
	Vertex N;

public:
	Facet(Vertex A, Vertex B, Vertex C);
	~Facet();

	Vertex getA();
	Vertex getB();
	Vertex getC();
	Vertex getN();

	//friend ostream& operator<<(const ostream& os);

};