#pragma once
#include <tuple>
#include <vector>
#include "Column.h"
#include "Float.h"
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
					Column v(columnNames[i], sizes[0]);
					sizes.erase(sizes.begin());
					columns.push_back(v);
				}
				if(columnTypes[i] == "Integer")
				{
					Column I(columnNames[i]);
					columns.push_back(I);
				}
				if(columnTypes[i] == "Boolean")
				{
					Column B(columnNames[i]);
					columns.push_back(B);
				}
				if(columnTypes[i]=="Float")
				{
					Column F(columnNames[i]);
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

		for(int i=0; i<columns[0].data.size(); i++)
		{
			for(int j=0; j<columns.size(); j++)
			{
				cout << columns[j].data[i] << ", ";
			}
			cout << endl;
		}
		
		cout << endl;
	}


};

