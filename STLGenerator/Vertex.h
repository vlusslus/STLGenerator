#pragma once
class Vertex
{
	private:
		double x;
		double y;
		double z;
	public:
		Vertex(double x, double y, double z);
		~Vertex();

		double getX();
		double getY();
		double getZ();

};

