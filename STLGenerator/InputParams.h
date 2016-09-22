#pragma once
#include <vector>
#include <utility>

using namespace std;

class InputParams
{
private:

	int RectX;
	int RectY;
	int CircR;
	int RectH;
	int CircH;

	vector<pair<int, int>> circle;

public:
	InputParams(ifstream &in);
	~InputParams();

	string toString();
	vector<pair<int, int>> getCirclesPair();

};

