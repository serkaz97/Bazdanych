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
		cout << "DataBase Sergiusz Kazmierczak" << endl;
		while (true)
		{
			cout << "\n Please enter file with list of commands" << endl;
			string filename;
			cin >> filename;
			fstream file;
			file.open(filename);
			if (file)
			{
				ProcesQuerry(filename.c_str());
				break;
			}
		}
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
				INSERT(QuarryList[i]);
			}
			else if (KeyWord == "SELECT")
			{
				SELECT(QuarryList[i]);
			}

			else if (KeyWord=="DELETE")
			{
				cout << "Delete Row to  Table" << endl;
				DELETE(QuarryList[i]);
			}
			else if(KeyWord=="DROP")
			{
				DROP(QuarryList[i]);
			}
			else
			{
				cout << "wrong command" << endl;
			}
			

		}
	}

	void SELECT(QuarryStruct x)
	{
		string name = x.names[x.names.size()-1];
		fstream file;
		string fname = name + ".txt";
		Table table;
		file.open(fname.c_str());
		if(!file)
		{
			cout << "SELECT: Table doesn't exist";
			return;
		}
		if (tables.size() == 0)
		{
			loadTable(name, table);
			tables.push_back(table);
		}
		else
		{
			bool isTable = false;
			for (int i = 0; i < tables.size(); i++)
			{
				if (tables[i].name == name)
				{
					isTable = true;
					table = tables[i];
					break;
				}
			}
			if (x.names[0] == "*")
			{
				table.printTable();
			}

			else //Print selected columns
			{
				bool isAColumn = false;
				for (int i = 0; i < x.names.size(); i++)
				{
					string SQLcolname = x.names[i];
					for (int j = 0; j < table.columns.size(); j++)
					{
						string columname = table.columns[j]->name;
						if (SQLcolname == columname)
						{
							isAColumn = true;
							cout << columname << ", ";
						}
					}

				}
				if (isAColumn == false)
				{
					cout << "SELECT: Column doesn't exist" << endl;
					return;
				}
				cout << endl;

				for (int j = 0; j < table.columns[0]->getColumnSize(); j++)
				{
					for (int i = 0; i < x.names.size(); i++)
					{
						string SQLcolname = x.names[i];
						for (int k = 0; k < table.columns.size(); k++)
						{
							string columname = table.columns[k]->name;
							if (SQLcolname == columname)
							{
								cout << table.columns[k]->getDataVal(j) << ", ";
							}
						}

					}
					cout << endl;
				}
			}
		}

	}

	void CREATE(QuarryStruct x)
	{
		fstream file;
		string name = x.names[0];
		string fname = name + ".txt";
		file.open(fname.c_str());
		if (!file)
		{
			file.open(fname.c_str(), ios::app);
			x.names.erase(x.names.begin());
			Table T(name, x.ColumnTypes, x.VarCharSizes, x.names);
			for(int i=0; i<x.names.size(); i++)
			{
				file << x.names[i] << ", ";
			}
			file << endl;
			tables.push_back(T);

			file.close();
		}
		else
			cout << "CREATE: Table exists" << endl;
	}

	void DELETE(QuarryStruct x)
	{

		//Deleting without conditions
		Table table;
		fstream file;
		string fname = x.names[0] + ".txt";
		if (tables.size() == 0)
		{
			loadTable(x.names[0], table);
			tables.push_back(table);
		}
		else
		{
			bool isTable = false;
			for (int i = 0; i < tables.size(); i++)
			{
				if (tables[i].name == table.name)
				{
					isTable = true;
					break;
				}
			}
			if (isTable == false)
			{
				tables.push_back(table);
			}
			for(int i=0; i<tables.size(); i++)
			{
				if(x.names[0] == tables[i].name)
				{
					for(int j=0; j<tables[i].columns.size(); j++)
					{
						tables[i].columns[j]->clearData();
					}
				}
			}
			
			file.open(fname);
			if (file)
			{
				file.close();
				remove(fname.c_str());
				file.open(fname, ios::out | ios::app);
				for (int j = 0; j < tables.size(); j++)
				{if(tables[j].name== x.names[0])
					for (int i = 0; i < tables[j].columns.size(); i++)
					{
						file << tables[j].columns[i]->name << ", ";
					}
				}
				file << endl;

			}
			file.close();
			
		}
		
	}

	void DROP(QuarryStruct x)
	{
		fstream file;
		string fname = x.names[0] + ".txt";
		file.open(fname);
		if (file)
		{
			file.close();
			remove(fname.c_str());
		}
		else
		{
			cout << "DROP: file is not exists" << endl;
		}
		
	}
	void INSERT(QuarryStruct x)
	{
		Table table;
		fstream file;
		string fname =  x.names[0] + ".txt";
		
		if(tables.size()==0)
		{
			loadTable(x.names[0], table);
			tables.push_back(table);
		}
		else
		{
			bool isTable = false;
			for(int i=0; i<tables.size(); i++)
			{
				if(tables[i].name==table.name)
				{
					isTable = true;
					break;
				}
			}
			if(isTable==false)
			{
				tables.push_back(table);
			}
		}

		file.open(fname.c_str(), ios::out | ios::app);
		if (file)
		{
			for (int i = 0; i < tables.size(); i++)
			{
				if (tables[i].name == x.names[0])
				{
					if(tables[i].columns.size()!=x.QuarryParam.size())
					{
						cout << "Uncorrect Data" << endl;
						return;
					}
					for (int j = 0; j < tables[i].columns.size() ; j++)
					{
						bool goodtype = false;
						if (parser.isInt(x.QuarryParam[j]) && tables[i].columns[j]->type == integer)
						{
							tables[i].columns[j]->addElement(x.QuarryParam[j]);
							file << x.QuarryParam[j] << ", ";
							goodtype = true;
							continue;
						}
						else if (parser.isFloat(x.QuarryParam[j]) && tables[i].columns[j]->type == floatVar)
						{
							tables[i].columns[j]->addElement(x.QuarryParam[j]);
							file << x.QuarryParam[j] << ", ";
							goodtype = true;
							continue;
						}
						else if ((x.QuarryParam[j] == "false" || x.QuarryParam[j] == "true" || x.QuarryParam[j] == "null") && tables[i].columns[j]->type == boolean)
						{
							tables[i].columns[j]->addElement(x.QuarryParam[j]);
							file << x.QuarryParam[j] << ", ";
							goodtype = true;
							continue;
						}
						else if(tables[i].columns[j]->type == varchar && !parser.isInt(x.QuarryParam[j]) && !parser.isFloat(x.QuarryParam[j]) && 
							!(x.QuarryParam[j] == "false" || x.QuarryParam[j] == "true" || x.QuarryParam[j] == "null"))
						{
							tables[i].columns[j]->addElement(x.QuarryParam[j]);
							file << x.QuarryParam[j] << ", ";
							goodtype = true;
							continue;
						}
						else
						{
							goodtype = false;
						}

						if(goodtype==false)
						{
							cout << "wrong type of data" << endl;
							return;
						}
					}
					file << endl;
				}
			}
			file.close();
		}
		else
		{
			cout << "Tabela nie istnieje";
		}
	}


	void printTables()
	{
		for(int i = 0; i< tables.size(); i++)
		{
			tables[i].printTable();
		}
	}


private:
	
	void loadTable(string name, Table &table)
	{
		vector<string> lines;
		fstream file;
		string filename = name + ".txt";
		file.open(filename);
		while(!file.eof())
		{
			string line;
			getline(file, line);
			if(line.size()!=0)
			lines.push_back(line);
		}

		table.name = name;
		for(int i=0; i<lines.size(); i++)
		{
			string line = lines[i];
			vector<string> linevec;
			linevec.push_back(line);
			parser.eliminatecommas(linevec);
			vector<string> testlines;
			if(i==0)
				parser.cleanSpecialChars(linevec, " ");
			if(i==0)
			{
				
				for(int j=0; j<linevec.size(); j++)
				{
					vector<string> testlines;
					testlines.push_back(lines[1]);
					parser.eliminatecommas(testlines);
					Column *column;
					if (parser.isInt(testlines[j]))
						column = new Integer(linevec[j]);
					else if (parser.isFloat(testlines[j]))
						column = new Float(linevec[j]);
					else if (testlines[j] == "false" || testlines[j] == "true" || testlines[j] == "null")
						column = new Boolean(linevec[j]);
					else
						column = new Varchar(linevec[j], 100);
					table.columns.push_back(column);
				}
			}
			else
			{
				for(int j=0; j<table.columns.size(); j++)
				{
					bool goodtype = false;
					if(parser.isInt(linevec[j]) && table.columns[j]->type==integer)
					{
						table.columns[j]->addElement(linevec[j]);
						goodtype = true;
						continue;
					}
					else if (parser.isFloat(linevec[j]) && table.columns[j]->type == floatVar)
					{
						table.columns[j]->addElement(linevec[j]);
						goodtype = true;
						continue;
					}
					else if((linevec[j + 1] == "false" || linevec[j + 1] == "true" || linevec[j + 1] == "null") && table.columns[j]->type==boolean)
					{
						table.columns[j]->addElement(linevec[j]);
						goodtype = true;
						continue;
					}
					else
					{
						table.columns[j]->addElement(linevec[j]);
						goodtype = true;
						continue;
					}

					if(goodtype = false)
					{
						cout << "wrong type of data" << endl;
						return;
					}
					
				}
			}
		}
		bool isTableOnName=false;
		for(int i=0; i<tables.size(); i++)
		{
			if (table.name == tables[i].name)
			{
				isTableOnName = true;
				break;
			}
			else
				isTableOnName = false;
		}
		if(isTableOnName==false)
		{
			tables.push_back(table);
		}
	}

	

};

