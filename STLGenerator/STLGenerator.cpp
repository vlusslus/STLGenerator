// STLGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <string>

#include "Base.h"

using namespace std;

const int fullRad = 360;
const int countVer = 10;
const double radio = 20;

int main()
{
	double angleStep = fullRad/countVer;
	Base* base = new Base();
	for (int angle = 0; angle <= fullRad; angle += angleStep) {
		//double angle = fullRad / currVer;
		cout << "Angle ";
		cout << angle;
		Vertex* vertex = new Vertex(radio*cos(angle), radio*sin(angle), 0);
		base->AddVertex(vertex);
	}
	cout << "-------------------------------";
	cout << base->toString();
	cin.get();

    return 0;
}

