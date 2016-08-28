#include "stdafx.h"
#include "Facet.h"



Facet::Facet(Vertex* A, Vertex* B, Vertex* C)
{
	this->A = A;
	this->B = B;
	this->C = C;

	Vertex* ba = A - B;
}


Facet::~Facet()
{
}
