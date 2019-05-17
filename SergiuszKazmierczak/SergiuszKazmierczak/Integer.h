#pragma once
#include "Column.h"
class Integer :
	public Column
{
public:
	Integer(string name)
	{
		this->name = name;
		this->type = integer;
	};
	~Integer(){};
	vector<int> data;

	void addElement(string value)
	{
		int temp = atoi(value.c_str());
		data.push_back(temp);
	}
};

