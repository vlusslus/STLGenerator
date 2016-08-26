#include "stdafx.h"
#include "Vertex.h"


Vertex::Vertex(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;

}

Vertex::~Vertex()
{
}

double Vertex::getX()
{
	return this->x;
}

double Vertex::getY()
{
	return this->y;
}

double Vertex::getZ()
{
	return this->z;
}




