#pragma once
#include <vector>
#include <string>

using namespace std;

class Bestiary
{
	vector <string> bestiaryData;

public:
	Bestiary();
	void print();
	void load(string fileName);
};

