#pragma once
#include "Column.h"
class Varchar :
	public Column
{
public:
	Varchar(string name, int size)
	{
		this->name = name;
		this->type = varchar;
		this->size = size;
		
	}
	~Varchar() {};
	vector<string> data;
	void addElement(string value)
	{
		if (value.length() > 255)
		{
			//Throw Error: VarChar is to long
			return;

		}		
		data.push_back(value);
		return;
	}

private:
	int size;
};

