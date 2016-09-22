// STLGenerator.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "iostream"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <utility>

#include "Base.h"
#include "Facet.h"
#include "InputParams.h"

#define PI 3.14159265  

using namespace std;

int main()
{
	string inLine;
	int indexInLine = 0;
	ifstream in;
	in.open("outparams.txt");

	InputParams *inputParams = new InputParams(in);
	cout << inputParams->toString();

	const int fullRad = 360;
	const int countVer = 30;
	const double radio = 5;
	const double height = 30;

	
	
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

	vector<Base> circlesDown;
	vector<Base> circlesUp;

	double angleStep = fullRad / countVer;

	for (int i = 0; i < inputParams->getCirclesPair().size(); i++)
	{
		Base* baseUp = new Base();
		Base* baseDown = new Base();
		pair<int, int> circle = inputParams->getCirclesPair()[i];
		for (int angle = 0; angle <= fullRad; angle += angleStep)
		{
			//double angle = fullRad / currVer;
			cout << "Angle ";
			cout << angle;
			cout << "\n";
			Vertex* vertex = new Vertex(circle.first + radio*cos(angle * PI / 180), circle.second + radio*sin(angle * PI / 180), 10);
			baseDown->AddVertex(*vertex);
			vertex->setZ(height + 10);
			baseUp->AddVertex(*vertex);
		}
		circlesDown.push_back(*baseDown);
		circlesUp.push_back(*baseUp);
	}

	vector<vector<Facet*>> facetCircles;

	for (int z = 0; z < circlesDown.size(); z++) {
		vector<Facet*> facets;
		//Треугольники боковой поверхности
		for (int indexDown = 0; indexDown < countVer; indexDown++)
		{
			Facet* facet = new Facet(&circlesDown[z].GetVertices()[indexDown], &circlesDown[z].GetVertices()[indexDown + 1], &circlesUp[z].GetVertices()[indexDown]);
			facets.push_back(facet);
		}

		for (int indexUp = countVer; indexUp > 0; indexUp--)
		{
			Facet* facet = new Facet(&circlesUp[z].GetVertices()[indexUp], &circlesUp[z].GetVertices()[indexUp - 1], &circlesDown[z].GetVertices()[indexUp]);
			facets.push_back(facet);
		}

		//Треугольники оснований
		for (int index = 0; index < countVer - 2; index++)
		{
			Facet* facetDowm = new Facet(&circlesDown[z].GetVertices()[0], &circlesDown[z].GetVertices()[index + 1], &circlesDown[z].GetVertices()[index + 2]);
			Facet* facetUp = new Facet(&circlesUp[z].GetVertices()[0], &circlesUp[z].GetVertices()[index + 1], &circlesUp[z].GetVertices()[index + 2]);
			facets.push_back(facetDowm);
			facets.push_back(facetUp);
		}

		facetCircles.push_back(facets);
	}


	vector<Facet*> rectFacets;

	

	//Треугольники площадки
	for (int indexDown = 0; indexDown < verticesRectDown.size()-1; indexDown++)
	{
		Facet* facet = new Facet(&verticesRectDown[indexDown], &verticesRectDown[indexDown + 1], &verticesRectUp[indexDown]);
		rectFacets.push_back(facet);
	}

	for (int indexUp = verticesRectUp.size()-1; indexUp > 0; indexUp--)
	{
		Facet* facet = new Facet(&verticesRectUp[indexUp], &verticesRectUp[indexUp - 1], &verticesRectDown[indexUp]);
		rectFacets.push_back(facet);
	}

	Facet* facet1 = new Facet(&verticesRectDown[0], &verticesRectDown[1], &verticesRectDown[2]);
	rectFacets.push_back(facet1);

	Facet* facet2 = new Facet(&verticesRectDown[2], &verticesRectDown[3], &verticesRectDown[0]);
	rectFacets.push_back(facet2);

	Facet* facet3 = new Facet(&verticesRectUp[0], &verticesRectUp[1], &verticesRectUp[2]);
	rectFacets.push_back(facet3);

	Facet* facet4 = new Facet(&verticesRectUp[2], &verticesRectUp[3], &verticesRectUp[0]);
	rectFacets.push_back(facet4);
	
	
	fstream out;
	out.open("out.stl");

	out << "solid OpenSCAD_Model\n";
	//Вычисленные нормали
	for (int v=0; v < facetCircles.size(); v++) 
	{
		for (int index = 0; index < facetCircles[v].size(); index++) {
			out << "  facet normal ";
			out << facetCircles[v][index]->getN().toString();
			out << "\n";
			out << "    outer loop\n";
			out << "      vertex ";
			out << facetCircles[v][index]->getA().toString();
			out << "\n";
			out << "      vertex ";
			out << facetCircles[v][index]->getB().toString();
			out << "\n";
			out << "      vertex ";
			out << facetCircles[v][index]->getC().toString();
			out << "\n";
			out << "    endloop\n";
			out << "  endfacet\n";
		}
	}
	
	out << "endsolid OpenSCAD_Model";
	out.close();

	cin.get();

    return 0;
}

