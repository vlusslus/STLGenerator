// STLGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <string>

#include "Base.h"
#include "Facet.h"

#define PI 3.14159265  

using namespace std;

const int fullRad = 360;
const int countVer = 10;
const double radio = 20;
const double height = 30;

int main()
{
	double angleStep = fullRad/countVer;
	Base* baseUp = new Base();
	Base* baseDown = new Base();
	for (int angle = 0; angle <= fullRad; angle += angleStep) 
	{
		//double angle = fullRad / currVer;
		cout << "Angle ";
		cout << angle;
		cout << "\n";
		Vertex* vertex = new Vertex(radio*cos(angle * PI/180), radio*sin(angle * PI / 180), 0);
		baseDown->AddVertex(*vertex);
		vertex->setZ(height);
		baseUp->AddVertex(*vertex);
	}
	cout << "-------------------------------";
	cout << "\n";
	vector<Vertex> verticesUp = baseUp->GetVertices();
	for (int i = 0; i < verticesUp.size(); i++)
	{
		cout << "# " + to_string(i) + "   ";
		cout << verticesUp[i].toString();
		cout << "\n";
	}

	cout << "-------------------------------";
	cout << "\n";
	vector<Vertex> verticesDown = baseDown->GetVertices();
	for (int i = 0; i < verticesDown.size(); i++)
	{
		cout << "# " + to_string(i) + "   ";
		cout << verticesDown[i].toString();
		cout << "\n";
	}

	vector<Facet*> facets;

	for (int indexDown = 0; indexDown < countVer-1; indexDown++)
	{
		Facet* facet = new Facet(&verticesDown[indexDown], &verticesDown[indexDown + 1], &verticesUp[indexDown]);
		facets.push_back(facet);
	}

	for (int indexUp = countVer; indexUp < 0; indexUp--)
	{
		Facet* facet = new Facet(&verticesUp[indexUp], &verticesUp[indexUp - 1], &verticesDown[indexUp]);
		facets.push_back(facet);
	}





	cin.get();

    return 0;
}

