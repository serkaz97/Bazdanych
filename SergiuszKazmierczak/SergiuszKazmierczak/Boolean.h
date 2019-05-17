#pragma once
#include "Column.h"
class Boolean :
	public Column
{
public:
	Boolean(string name)
	{
		this->name = name;
		this->type = boolean;
	}
	~Boolean() {};
	vector<string> data;

	void addElement(string value)
	{
		if(value == "false" || value == "true")
			data.push_back(value);
	}
};

