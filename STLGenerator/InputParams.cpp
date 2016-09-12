#include "stdafx.h"
#include "InputParams.h"
#include <fstream>
#include <sstream>
#include <string>


using namespace std;


InputParams::InputParams(ifstream &in)
{
	string inLine;
	int indexInLine = 0;

	this->circle = *(new vector<pair<int, int>>);

	while (std::getline(in, inLine))
	{
		std::istringstream iss(inLine);
		if (indexInLine != 0)
		{
			pair<int, int> *pairXY = new pair<int, int>;
			if (!(iss >> pairXY->first >> pairXY->second))
			{
				break;
			}
			else
			{
				this->circle.push_back(*pairXY);
			}
		}
		else
		{
			if (!(iss >> this->RectX >> this->RectY) >> this->RectH >> this->CircH >> this->CircR)
			{
				break;
			}
		}
		indexInLine += 1;
	}
}



InputParams::~InputParams()
{

}

string InputParams::toString()
{
	string result = to_string(this->RectX) + " " + to_string(this->RectY) + " " + to_string(this->RectH) + " " + to_string(this->CircH) + " " + to_string(this->CircR) + "\n";
	for (int i = 0; i < this->circle.size(); i++)
	{
		result += to_string(this->circle[i].first) + " " + to_string(this->circle[i].second) + "\n";
	}
	return result;
}
