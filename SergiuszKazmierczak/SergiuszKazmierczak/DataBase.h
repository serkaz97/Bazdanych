#pragma once
#include <vector>
#include "Table.h"
#include "SQLparser.h"

class DataBase
{
public:


	vector<QuarryStruct> QuarryList;
	vector<Table> tables;
	SQLparser parser;
	DataBase()
	{
		cout << "DataBase Initialized" << endl;
	};
	~DataBase();

	void ProcesQuerry(const char* filename)
	{
		QuarryList = parser.parseQuary(filename);
		for(int i=0; i<QuarryList.size(); i++)
		{
			string KeyWord = QuarryList[i].KeyWords[0];
			if(KeyWord == "CREATE")
			{
				cout << "Creating Table" << endl;
				CREATE(QuarryList[i]);
			}
			else if(KeyWord == "INSERT")
			{
				cout << "Insert Row to  Table" << endl;
				INSERT(QuarryList[i]);
			}
			else if (KeyWord=="SELECT")
			{
				cout << "Insert Row to  Table" << endl;
			}
			else if (KeyWord=="DELETE")
			{
				cout << "Insert Row to  Table" << endl;
			}
			else if(KeyWord=="DROP")
			{
				cout << "Drop Table" << endl;
			}
			else
			{
				cout << "wrong command" << endl;
			}
			

		}
		printTables();
	}

	void SELECT(QuarryStruct x)
	{
	
	}

	void CREATE(QuarryStruct x)
	{
		string name = x.names[0];
		x.names.erase(x.names.begin());
		Table T(name, x.ColumnTypes, x.VarCharSizes, x.names);
		tables.push_back(T);
	}

	void DELETE()
	{
		
	}

	void DROP()
	{
		
	}
	void INSERT(QuarryStruct x)
	{
		for(int i=0; i<tables.size(); i++)
		{
			if(tables[i].name== x.names[0])
			{
				for(int j=0; j<tables[i].columns.size(); j++)
				{
					tables[i].columns[j].addElement(x.QuarryParam[j]);
				}
			}
		}
	}


	void printTables()
	{
		for(int i = 0; i< tables.size(); i++)
		{
			tables[i].printTable();
		}
	}


};

