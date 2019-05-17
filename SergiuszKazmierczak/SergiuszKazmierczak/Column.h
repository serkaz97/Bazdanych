#pragma once
#include <string>
#include <vector>
#include <iostream>

enum types { integer, floatVar, boolean, varchar};


using namespace  std;
class Column
{
public:
	Column()
	{
		cout << "Column Constructor" << endl;
	};
	~Column(){};
	string name;
	types type;
	virtual void addElement(string)
	{
		
	}
	virtual void addElement(string, string)
	{
		
	}
	virtual int getDataVectorSize()
	{
		return 0;
	}

	virtual string getDataVal(int i)
	{
		return string();
	}
};

