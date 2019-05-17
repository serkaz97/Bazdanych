#pragma once
#include <tuple>
#include <vector>
#include "Column.h"
#include "Integer.h"
#include "Float.h"
#include "Boolean.h"
#include "Varchar.h"
#include <iostream>
#include <deque>
#include "SQLparser.h"
using namespace std;
class Table
{
public:
	string name;
	vector<Column> columns;
	Table() {}
	Table(string name, vector<string> columnTypes, vector<int> sizes, vector<string> columnNames)
	{
		this->name = name;
		if (columnTypes.size() == columnNames.size())
		{
			//Initialization of table with empty Vectors 
			for (int i = 0; i < columnTypes.size(); i++)
			{
				if (columnTypes[i] == "Varchar")
				{
					Varchar v(columnNames[i], sizes[0]);
					sizes.erase(sizes.begin());
					columns.push_back(v);
				}
				if(columnTypes[i] == "Integer")
				{
					Integer I(columnNames[i]);
					columns.push_back(I);
				}
				if(columnTypes[i] == "Boolean")
				{
					Boolean B(columnNames[i]);
					columns.push_back(B);
				}
				if(columnTypes[i]=="Float")
				{
					Float F(columnNames[i]);
					columns.push_back(F);
				}
			}
		}
	}

	void addRow();

	void printTable()
	{
		for (int i = 0; i < columns.size(); i++)
			cout << columns[i].name << ", ";
		cout << endl;

		for(int i=0; i<columns.size(); i++)
		{
			for(int j=0; j<columns[0].getDataVectorSize(); j++)
			{
				columns[i].getDataVal(j);
			}
		}
		
		cout << endl;
	}


};

