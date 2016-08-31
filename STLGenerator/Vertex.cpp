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
	return to_string(this->x) + " " + to_string(this->y) + " " + to_string(this->z);
}

void Vertex::setZ(const double z)
{
	this->z = z;
}

Vertex& Vertex::operator-(const Vertex& right)
{
	Vertex* result = new Vertex(this->x - right.x, this->y - right.y, this->z - right.z);
	return *result;
}

Vertex& Vertex::operator*(const Vertex& right)
{
	Vertex* result = new Vertex(
		this->y * right.z - this->z * right.y,
		this->z * right.x - this->x * right.z,
		this->x * right.y - this->y * right.x
	);
	return *result;
}




