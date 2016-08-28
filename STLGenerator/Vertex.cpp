#include "stdafx.h"
#include "Vertex.h"
#include <string>

using namespace std;

Vertex::Vertex()
{

}

Vertex::Vertex(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;

}

Vertex::~Vertex()
{
}

const double Vertex::getX()
{
	return this->x;
}

const double Vertex::getY()
{
	return this->y;
}

const double Vertex::getZ()
{
	return this->z;
}

string Vertex::toString()
{
	return "X: " + to_string(this->x) + " " + "Y: " + to_string(this->y) + " " + "Z: " + to_string(this->z);
}

void Vertex::setZ(const double z)
{
	this->z = z;
}

const Vertex* operator-(const Vertex* right, const Vertex* left)
{
	return new Vertex(right->getX - left->getX, right->getY - left->getY, right->getZ - left->getZ);
	
}




