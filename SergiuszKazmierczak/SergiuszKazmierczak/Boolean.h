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


	int getDataVectorSize()
	{
		return data.size();
	}

	string getDataVal(int i)
	{
		return data[i];
	}

	int getColumnSize()
	{
		return data.size();
	}

	void clearData()
	{
		data.erase(data.begin(), data.end());
	}
};

