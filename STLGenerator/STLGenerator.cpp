// STLGenerator.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "iostream"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

#include "Base.h"
#include "Facet.h"
#include "InputParams.h"

#define PI 3.14159265  

using namespace std;

const int fullRad = 360;
const int countVer = 30;
const double radio = 5;
const double height = 30;

int main()
{
	string inLine;
	int indexInLine = 0;
	ifstream in;
	in.open("input.txt");

	InputParams *inputParams = new InputParams(in);
	cout << inputParams->toString();

	
	
	vector<Vertex> verticesRectDown;
	vector<Vertex> verticesRectUp;


	
	Vertex* vertex = new Vertex(0, 0 ,0);
	verticesRectDown.push_back(*vertex);
	vertex = new Vertex(50, 0, 0);
	verticesRectDown.push_back(*vertex);
	vertex = new Vertex(50, 50, 0);
	verticesRectDown.push_back(*vertex);
	vertex = new Vertex(0, 50, 0);
	verticesRectDown.push_back(*vertex);

	vertex = new Vertex(0, 0, 10);
	verticesRectUp.push_back(*vertex);
	vertex = new Vertex(50, 0, 10);
	verticesRectUp.push_back(*vertex);
	vertex = new Vertex(50, 50, 10);
	verticesRectUp.push_back(*vertex);
	vertex = new Vertex(0, 50, 10);
	verticesRectUp.push_back(*vertex);



	double angleStep = fullRad/countVer;
	Base* baseUp = new Base();
	Base* baseDown = new Base();

	for (int angle = 0; angle <= fullRad; angle += angleStep) 
	{
		//double angle = fullRad / currVer;
		cout << "Angle ";
		cout << angle;
		cout << "\n";
		Vertex* vertex = new Vertex(30 + radio*cos(angle * PI/180), 30 + radio*sin(angle * PI / 180), 10);
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

	//Треугольники площадки
	for (int indexDown = 0; indexDown < verticesRectDown.size()-1; indexDown++)
	{
		Facet* facet = new Facet(&verticesRectDown[indexDown], &verticesRectDown[indexDown + 1], &verticesRectUp[indexDown]);
		facets.push_back(facet);
	}

	for (int indexUp = verticesRectUp.size()-1; indexUp > 0; indexUp--)
	{
		Facet* facet = new Facet(&verticesRectUp[indexUp], &verticesRectUp[indexUp - 1], &verticesRectDown[indexUp]);
		facets.push_back(facet);
	}

	Facet* facet1 = new Facet(&verticesRectDown[0], &verticesRectDown[1], &verticesRectDown[2]);
	facets.push_back(facet1);

	Facet* facet2 = new Facet(&verticesRectDown[2], &verticesRectDown[3], &verticesRectDown[0]);
	facets.push_back(facet2);

	Facet* facet3 = new Facet(&verticesRectUp[0], &verticesRectUp[1], &verticesRectUp[2]);
	facets.push_back(facet3);

	Facet* facet4 = new Facet(&verticesRectUp[2], &verticesRectUp[3], &verticesRectUp[0]);
	facets.push_back(facet4);
	
	//Треугольники оснований
	for (int index = 0; index < countVer-2; index++)
	{
		Facet* facetDowm = new Facet(&verticesDown[0], &verticesDown[index + 1], &verticesDown[index + 2]);
		Facet* facetUp = new Facet(&verticesUp[0], &verticesUp[index + 1], &verticesUp[index + 2]);
		facets.push_back(facetDowm);
		facets.push_back(facetUp);
	}
	fstream out;
	out.open("out.stl");

	out << "solid OpenSCAD_Model\n";
	//Вычисленные нормали
	for (int index = 0; index < facets.size(); index++) {
		out << "  facet normal ";
		out << facets[index]->getN().toString();
		out << "\n";
		out << "    outer loop\n";
		out << "      vertex ";
		out << facets[index]->getA().toString();
		out << "\n";
		out << "      vertex ";
		out << facets[index]->getB().toString();
		out << "\n";
		out << "      vertex ";
		out << facets[index]->getC().toString();
		out << "\n";
		out << "    endloop\n";
		out << "  endfacet\n";
	}
	out << "endsolid OpenSCAD_Model";
	out.close();

	cin.get();

    return 0;
}

