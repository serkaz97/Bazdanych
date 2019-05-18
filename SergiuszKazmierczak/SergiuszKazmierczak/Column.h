#pragma once
#include <string>
#include <vector>
#include <iostream>

enum types { integer, floatVar, boolean, varchar};


using namespace  std;
class Column
{
public:
	Column(string name)
	{
		this->name = name;
	}

	Column(string name, int size)
	{
		this->name = name;
		this->size = size;

	}
	void addElement(string el)
	{
		data.push_back(el);
	}
	int getDataVectorSize() { return 0; }
	string getDataVal(int i) { return data[i]; }

	string name;
	types type;
	int size;
	vector<string> data;
};

