#include "stdafx.h"
#include "Facet.h"

#include <limits>



Facet::Facet(Vertex* A, Vertex* B, Vertex* C)
{
	this->A = A;
	this->B = B;
	this->C = C;

	Vertex ba = *B - *A;
	Vertex ca = *C - *A;

	this->N = ba * ca;
	//this->O = this->N;

	double max = abs(this->N.getX());
	if (abs(this->N.getY()) > max)
	{
		max = abs(this->N.getY());
	}
	if (abs(this->N.getZ()) > max)
	{
		max = abs(this->N.getZ());
	}

	Vertex* N = new Vertex(this->N.getX() / max, this->N.getY() / max, this->N.getZ() / max);
	this->N = *N;
}


Facet::~Facet()
{
}

Vertex Facet::getN() {
	return N;
}

Vertex Facet::getA() {
	return *A;
}

Vertex Facet::getB() {
	return *B;
}

Vertex Facet::getC() {
	return *C;
}