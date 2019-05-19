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
	vector<Column*> columns;
	Table() {}
	Table(string name, vector<string> columnTypes, vector<int> sizes, vector<string> columnNames)
	{
		Column *x;
		this->name = name;
		if (columnTypes.size() == columnNames.size())
		{
			//Initialization of table with empty Vectors 
			for (int i = 0; i < columnTypes.size(); i++)
			{
				if (columnTypes[i] == "Varchar")
				{
					x = new Varchar(columnNames[i], sizes[0]);
					sizes.erase(sizes.begin());
					columns.push_back(x);
				}
				if(columnTypes[i] == "Integer")
				{
					x = new Integer(columnNames[i]);
					columns.push_back(x);
				}
				if(columnTypes[i] == "Boolean")
				{
					x=new Boolean(columnNames[i]);
					columns.push_back(x);
				}
				if(columnTypes[i]=="Float")
				{
					x= new Float(columnNames[i]);
					columns.push_back(x);
				}
			}
		}
	}

	void addRow();

	void printTable()
	{
		for (int i = 0; i < columns.size(); i++)
			cout << columns[i]->name << ", ";
		cout << endl;

		for(int i=0; i<columns[0]->getColumnSize(); i++)
		{
			for(int j=0; j<columns.size(); j++)
			{
				cout << columns[j]->getDataVal(i)<<", ";
			}
			cout << endl;
		}
		
		cout << endl;
	}


};

