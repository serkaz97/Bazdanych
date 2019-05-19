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
		if (value.length() > size)
		{
			//What to do?
			return;

		}
		else {
			data.push_back(value);
			return;
		}
	}

	int getDataVectorSize()
	{
		return data.size();
	}

	string getDataVal(int i)
	{
		string temp = data[i];
		if(temp[0]==' ')
		{
			temp.erase(temp.begin());
		}
		return temp;
	}

	int getColumnSize()
	{
		return data.size();
	}

	void clearData()
	{
		data.erase(data.begin(), data.end());
	}

private:
	int size;
};

