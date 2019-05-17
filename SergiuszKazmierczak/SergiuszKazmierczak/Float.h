#pragma once
#include "Column.h"
class Float :
	public Column
{
public:
	Float(string name)
	{
		this->name = name;
		this->type = floatVar;
	}
	~Float(){};
	vector<float> data;

	void addElement(string value)
	{
		int temp = atof(value.c_str());
		data.push_back(temp);
	}
};

