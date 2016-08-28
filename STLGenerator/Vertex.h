#pragma once

#include <string>


using namespace std;

class Vertex
{
	private:
		double x;
		double y;
		double z;

	public:
		Vertex();
		Vertex(double x, double y, double z);
		~Vertex();

		const double getX();
		const double getY();
		const double getZ();

		void setZ(const double z);

		string toString();

};

const Vertex* operator-(const Vertex* right, const Vertex* left);


