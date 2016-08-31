// STLGenerator.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "iostream"
#include <fstream>
#include <string>
#include <cstdio>

#include "Base.h"
#include "Facet.h"

#define PI 3.14159265  



using namespace std;

const int fullRad = 360;
const int countVer = 30;
const double radio = 20;
const double height = 30;

int main()
{

	fstream myfile;
	myfile.open("out.stl");
	//myfile << "Writing this to a file.\n";
	



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

	//Треугольники боковой поверхности
	for (int indexDown = 0; indexDown < countVer; indexDown++)
	{
		Facet* facet = new Facet(&verticesDown[indexDown], &verticesDown[indexDown + 1], &verticesUp[indexDown]);
		facets.push_back(facet);
	}

	for (int indexUp = countVer; indexUp > 0; indexUp--)
	{
		Facet* facet = new Facet(&verticesUp[indexUp], &verticesUp[indexUp - 1], &verticesDown[indexUp]);
		facets.push_back(facet);
	}

	//Треугольники оснований
	for (int index = 0; index < countVer-2; index++)
	{
		Facet* facetDowm = new Facet(&verticesDown[0], &verticesDown[index + 1], &verticesDown[index + 2]);
		Facet* facetUp = new Facet(&verticesUp[0], &verticesUp[index + 1], &verticesUp[index + 2]);
		facets.push_back(facetDowm);
		facets.push_back(facetUp);
	}

	myfile << "solid OpenSCAD_Model\n";
	//Вычисленные нормали
	for (int index = 0; index < facets.size(); index++) {
		myfile << "  facet normal ";
		myfile << facets[index]->getN().toString();
		myfile << "\n";
		myfile << "    outer loop\n";
		myfile << "      vertex ";
		myfile << facets[index]->getA().toString();
		myfile << "\n";
		myfile << "      vertex ";
		myfile << facets[index]->getB().toString();
		myfile << "\n";
		myfile << "      vertex ";
		myfile << facets[index]->getC().toString();
		myfile << "\n";
		myfile << "    endloop\n";
		myfile << "  endfacet\n";
	}
	myfile << "endsolid OpenSCAD_Model";
	myfile.close();

	cin.get();

    return 0;
}

