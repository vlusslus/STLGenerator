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

void buildGlif() {

	string inLine;
	int indexInLine = 0;
	ifstream in;
	in.open("C:\outparams.txt");

	InputParams *inputParams = new InputParams(in);
	//cout << inputParams->toString();

	const int fullRad = 360;
	const int countVer = 20;
	const double radio = 5;
	const double height = 30;



	vector<Vertex> verticesRectDown;
	vector<Vertex> verticesRectUp;

	int rectX = 450;
	int rectY = 630;



	Vertex* vertex = new Vertex(0, 0, 0);
	verticesRectDown.push_back(*vertex);
	vertex = new Vertex(rectX, 0, 0);
	verticesRectDown.push_back(*vertex);
	vertex = new Vertex(rectX, rectY, 0);
	verticesRectDown.push_back(*vertex);
	vertex = new Vertex(0, rectY, 0);
	verticesRectDown.push_back(*vertex);

	vertex = new Vertex(0, 0, 10);
	verticesRectUp.push_back(*vertex);
	vertex = new Vertex(rectX, 0, 10);
	verticesRectUp.push_back(*vertex);
	vertex = new Vertex(rectX, rectY, 10);
	verticesRectUp.push_back(*vertex);
	vertex = new Vertex(0, rectY, 10);
	verticesRectUp.push_back(*vertex);

	vector<Base> circlesDown;
	vector<Base> circlesUp;

	double angleStep = fullRad / countVer;
	int h = 15;
	for (int i = 0; i < inputParams->getCirclesPair().size(); i++)
	{
		Base* baseUp = new Base();
		Base* baseDown = new Base();
		pair<int, int> circle = inputParams->getCirclesPair()[i];
		for (int angle = 0; angle <= fullRad; angle += angleStep)
		{
			//double angle = fullRad / currVer;
			//cout << "Angle ";
			//cout << angle;
			//cout << "\n";
			Vertex* vertex = new Vertex(rectX - circle.first + radio*cos(angle * PI / 180), circle.second + radio*sin(angle * PI / 180), 10);
			baseDown->AddVertex(*vertex);
			vertex->setZ(h);
			baseUp->AddVertex(*vertex);
		}
		circlesDown.push_back(*baseDown);
		circlesUp.push_back(*baseUp);
		//-------------------------------
		vector<Base> sphericals;
		for (int j = 0; j <= 3; j++) {
			Vertex* vertex = new Vertex();
		}

	}

	for (int i = 0; i < circlesDown.size(); i++) {
		cout << "Circle #" + to_string(i);
		cout << endl;
		for (int j = 0; j < circlesDown[i].GetVertices().size(); j++) {
			vector<Vertex> vertices = circlesDown[i].GetVertices();
			cout << "  Vertex #" + to_string(j);
			cout << endl;
			cout << "   " + vertices[j].toString();
			cout << endl;
		}
	}

	vector<vector<Facet*>> facetCircles;

	for (int z = 0; z < circlesDown.size(); z++) {
		vector<Facet*> facets;
		//Треугольники боковой поверхности
		for (int indexDown = 0; indexDown < countVer; indexDown++)
		{
			Facet* facet = new Facet(circlesDown[z].GetVertices()[indexDown], circlesDown[z].GetVertices()[indexDown + 1], circlesUp[z].GetVertices()[indexDown]);
			facets.push_back(facet);
		}

		for (int indexUp = countVer; indexUp > 0; indexUp--)
		{
			Facet* facet = new Facet(circlesUp[z].GetVertices()[indexUp], circlesUp[z].GetVertices()[indexUp - 1], circlesDown[z].GetVertices()[indexUp]);
			facets.push_back(facet);
		}

		//Треугольники оснований
		for (int index = 0; index < countVer - 2; index++)
		{
			Facet* facetDowm = new Facet(circlesDown[z].GetVertices()[0], circlesDown[z].GetVertices()[index + 1], circlesDown[z].GetVertices()[index + 2]);
			Facet* facetUp = new Facet(circlesUp[z].GetVertices()[0], circlesUp[z].GetVertices()[index + 1], circlesUp[z].GetVertices()[index + 2]);
			facets.push_back(facetDowm);
			facets.push_back(facetUp);
		}

		facetCircles.push_back(facets);
	}

	//cout << (facetCircles[0][0]->getA()).toString();


	vector<Facet*> rectFacets;



	//Треугольники площадки
	for (int indexDown = 0; indexDown < verticesRectDown.size() - 1; indexDown++)
	{
		Facet* facet = new Facet(verticesRectDown[indexDown], verticesRectDown[indexDown + 1], verticesRectUp[indexDown]);
		rectFacets.push_back(facet);
	}

	for (int indexUp = verticesRectUp.size()-1; indexUp > 0; indexUp--)
	{
		Facet* facet = new Facet(verticesRectUp[indexUp], verticesRectUp[indexUp - 1], verticesRectDown[indexUp]);
		rectFacets.push_back(facet);
	}

	Facet* facet5 = new Facet(verticesRectUp[0], verticesRectUp[3], verticesRectDown[0]);
	rectFacets.push_back(facet5);

	Facet* facet6 = new Facet(verticesRectDown[0], verticesRectDown[3], verticesRectUp[3]);
	rectFacets.push_back(facet6);

	Facet* facet1 = new Facet(verticesRectDown[0], verticesRectDown[1], verticesRectDown[2]);
	rectFacets.push_back(facet1);

	Facet* facet2 = new Facet(verticesRectDown[2], verticesRectDown[3], verticesRectDown[0]);
	rectFacets.push_back(facet2);

	Facet* facet3 = new Facet(verticesRectUp[0], verticesRectUp[1], verticesRectUp[2]);
	rectFacets.push_back(facet3);

	Facet* facet4 = new Facet(verticesRectUp[2], verticesRectUp[3], verticesRectUp[0]);
	rectFacets.push_back(facet4);


	fstream out;
	out.open("out.stl");

	out << "solid OpenSCAD_Model\n";
	//Вычисленные нормали
	for (int v = 0; v < facetCircles.size(); v++)
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
	for (int v = 0; v < rectFacets.size(); v++)
	{
		out << "  facet normal ";
		out << rectFacets[v]->getN().toString();
		out << "\n";
		out << "    outer loop\n";
		out << "      vertex ";
		out << rectFacets[v]->getA().toString();
		out << "\n";
		out << "      vertex ";
		out << rectFacets[v]->getB().toString();
		out << "\n";
		out << "      vertex ";
		out << rectFacets[v]->getC().toString();
		out << "\n";
		out << "    endloop\n";
		out << "  endfacet\n";
	}

	out << "endsolid OpenSCAD_Model";
	out.close();

	cin.get();

}

void buildSpherical() {

	pair<int, int>* center = new pair<int, int>(100, 100);
	int radio = 50;
	int height = 25;
	int heightStep = 5;
	int fullRad = 360;
	int angleStep = 10;

	vector<Base> bases;
	for (int h = 0; h <= height; h += heightStep) {

		Base* base = new  Base();
		for (int angle = 0; angle <= fullRad; angle += angleStep)
		{
			Vertex* vertex = new Vertex(center->first + radio*cos(angle * PI / 180), center->second + radio*sin(angle * PI / 180), h);
			base->AddVertex(*vertex);
			if (radio == 0) {
				break;
			}
		}
		radio -= 50 / (height / heightStep);
		bases.push_back(*base);
	}

	vector<vector<Facet*>> facetsAll;
	vector<Facet*> facetOne;
	for (int indBase = 0; indBase < bases.size()-1; indBase++) {
		vector<Vertex> verticesDown = bases[indBase].GetVertices();
		vector<Vertex> verticesUp = bases[indBase+1].GetVertices();

		int vertCountDown = verticesDown.size();
		int vertCountUp = verticesUp.size();

		if (vertCountUp != 1) {
			for (int indexDown = 0; indexDown < vertCountDown - 1; indexDown++)
			{
				Facet* facet = new Facet(verticesDown[indexDown], verticesDown[indexDown + 1], verticesUp[indexDown]);
				facetOne.push_back(facet);
			}

			for (int indexUp = vertCountDown - 1; indexUp > 0; indexUp--)
			{
				Facet* facet = new Facet(verticesUp[indexUp], verticesUp[indexUp - 1], verticesDown[indexUp]);
				facetOne.push_back(facet);
			}

			facetsAll.push_back(facetOne);
		}
		else {
			for (int indexDown = 0; indexDown < vertCountDown - 1; indexDown++)
			{
				Facet* facet = new Facet(verticesDown[indexDown], verticesDown[indexDown + 1], verticesUp[0]);
				facetOne.push_back(facet);
			}
		}
		
	}

	fstream out;
	out.open("out.stl");

	out << "solid OpenSCAD_Model\n";
	//Вычисленные нормали
	for (int v = 0; v < facetsAll.size(); v++)
	{
		for (int index = 0; index < facetsAll[v].size(); index++) {
			out << "  facet normal ";
			out << facetsAll[v][index]->getN().toString();
			out << "\n";
			out << "    outer loop\n";
			out << "      vertex ";
			out << facetsAll[v][index]->getA().toString();
			out << "\n";
			out << "      vertex ";
			out << facetsAll[v][index]->getB().toString();
			out << "\n";
			out << "      vertex ";
			out << facetsAll[v][index]->getC().toString();
			out << "\n";
			out << "    endloop\n";
			out << "  endfacet\n";
		}
	}

	out << "endsolid OpenSCAD_Model";
	out.close();

	std:cout << "End!";


	cin.get();

}

int main()
{
	buildGlif();

	//buildSpherical();

	return 0;

}