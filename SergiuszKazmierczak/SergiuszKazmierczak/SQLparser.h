#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

struct QuarryStruct
{
	vector<string> KeyWords;
	vector<string> QuarryParam;
	vector<string> ColumnTypes;
	vector<int> VarCharSizes;
	vector<string> names;
	vector<string> conditions;
};


class SQLparser
{
public:

	SQLparser(){}
	SQLparser(const char* filename)
	{
		parseQuary(filename);
		
	}
	~SQLparser(){};


	vector<QuarryStruct> parseQuary(const char* filename)
	{
		getrawcommand(filename);
		getRawQuarryList();
		getQuarriesList();
		return  QuarryList;
	}


	void eliminatecommas(vector<string> &names)
	{
		vector<string> newNames;
		string temp2;
		bool found = false;
		for (int i = 0; i < names.size(); i++)
		{
			found = false;
			string temp = names[i];
			for (int j = 0; j < temp.size(); j++)
			{
				if (temp[j] == ',')
				{
					temp2 = temp.substr(0, j);
					newNames.push_back(temp2);
					temp.erase(temp.begin(), temp.begin() + j + 1);
					names[i].erase(names[i].begin(), names[i].begin() + j + 1);
					i = -1;
					found = true;
					break;
				}

			}
			if (found == false)
			{
				newNames.push_back(temp);
			}
		}

		names = newNames;
	}

	void cleanSpecialChars(vector<string> &rawcommand, string specialchars)
	{

		for (int i = 0; i < rawcommand.size(); i++)
		{
			string temp = rawcommand[i];
			for (int j = 0; j < temp.length(); j++)
			{
				for (int k = 0; k < specialchars.length(); k++)
				{
					if (temp[j] == specialchars[k])
					{
						temp.erase(j, 1);
						j--;
						break;
					}
				}
			}
			if (temp.size() > 0)
				if (temp[temp.size() - 1] == ' ' || temp[temp.size() - 1] == '\0')
				{
					temp.erase(temp.end() - 1);
				}
			rawcommand[i] = temp;
		}
		for (int i = 0; i < rawcommand.size(); i++)
		{
			if (rawcommand[i].size() == 0)
				rawcommand.erase(rawcommand.begin() + i);
		}
	}

	bool isInt(string temp)
	{
		bool digital = false;
		for (int i = 0; i < temp.length(); i++)
		{
			if (int(temp[i]) >= 48 && int(temp[i]) <= 57)
			{
				digital = true;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	bool isFloat(string temp)
	{
		bool digital = false;
		for (int i = 0; i < temp.length(); i++)
		{
			if (int(temp[i]) >= 48 && int(temp[i]) <= 57 || int(temp[i]) == 46)
			{
				digital = true;
			}
			else
			{
				return false;
			}
		}
		return true;

	}



private:
	string rawData;
	vector<QuarryStruct> QuarryList;
	vector<vector<string>> Rawquarylist;
	QuarryStruct quary;
	vector<string> rawcommand;


	void getrawcommand(const char * filename)
	{
		ifstream file(filename);
		string word;
		if (file)
		{
			while (file >> word)
			{
				rawcommand.push_back(word);
			}
		}
		else
		{
			cout << "file doesnt exist" << endl;
		}
	}


	void getRawQuarryList()
	{
		vector<string> rawQuarry;
		for(int i=0; i<rawcommand.size(); i++)
		{
			string temp = rawcommand[i];
			rawQuarry.push_back(temp);
			for(int j=0; j<temp.length(); j++)
			{
				if(temp[j]==';')
				{
					Rawquarylist.push_back(rawQuarry);
					rawQuarry.clear();
				}
			}
		}
	}




	void findKeyWords(vector<string> &rawcommand, QuarryStruct &q)
	{
		vector<string> keywords;
		for (int i = 0; i < rawcommand.size(); i++)
		{
			string temp = rawcommand[i];
			bool upper = true;
			for (int j = 0; j < temp.length(); j++)
			{
				if (!isupper(temp[j]))
				{
					upper = false;
					break;

				}
				else
					upper = true;
			}
			if (upper)
			{
				keywords.push_back(temp);
				rawcommand.erase(rawcommand.begin() + i);
				i--;
			}
		}
		q.KeyWords = keywords;

	}


	
	void findStrings(vector<string> &QuarryParam, vector<string> &names, vector<string>& rawcommand)
	{
		string words;
		for (int i = 0; i < rawcommand.size(); i++)
		{
			string temp = rawcommand[i];

			//Checking if prameter has only one word
			if (temp[0] == '\"' && temp[temp.length() - 1] == '\"')
			{
				temp.erase(temp.begin());
				temp[temp.length() - 1] = 0;
				cout << "temp" << endl;
				QuarryParam.push_back(temp);
				rawcommand.erase(rawcommand.begin() + i);
				temp = rawcommand[i];
			}
			//Searching for a string with " on last index
			if (temp[0] == '\"' && temp[temp.length() - 1] != '\"')
			{
				words = words + temp + " ";
				while (temp[temp.length() - 1] != '\"')
				{
					rawcommand.erase(rawcommand.begin() + i);
					temp = rawcommand[i];
					words = words + temp + " ";
				}
				rawcommand.erase(rawcommand.begin() + i);
				QuarryParam.push_back(words);
				i--;
			}
			words.clear();
			rawcommand[i].c_str();
			if (isInt(temp))
			{
				QuarryParam.push_back(temp);
			}
			else if (isFloat(temp))
			{
				QuarryParam.push_back(temp);
			}

			if (temp[0] != '\"' && temp[temp.length() - 1] != '\"' && !isFloat(temp) && !isInt(temp))
			{
				names.push_back(temp);
			}
		}
	}
	


	void findTypes(vector<string> &types, vector<int> &varcharsizes, vector<string> &rawcommand)
	{   
		string temp;
		for(int i=0; i<rawcommand.size(); i++)
		{
			temp = rawcommand[i];
			if (temp==":")
			{
				rawcommand.erase(rawcommand.begin() + i);
				temp = rawcommand[i];
			}
			if(temp.find("Integer")!=temp.npos)
			{
				types.push_back("Integer");
				rawcommand.erase(rawcommand.begin() + i);
				temp = rawcommand[i];
			}
			if(temp.find("Float") != temp.npos)
			{
				types.push_back("Float");
				rawcommand.erase(rawcommand.begin() + i);
				temp = rawcommand[i];
			}
			if (temp.find("Boolean") != temp.npos)
			{
				types.push_back("Boolean");
				rawcommand.erase(rawcommand.begin() + i);
				temp = rawcommand[i];
			}
			std::size_t found = temp.find("Varchar");
			if(found!=temp.npos)
			{	
				types.push_back("Varchar");
				while(temp[0] !='(')
				{
					temp.erase(temp.begin());
				}
				string numb;
				while(temp[0]!=')')
				{
					if(temp[0]=='(')
					{
						temp.erase(temp.begin());
					}
					numb.push_back(temp[0]);
					temp.erase(temp.begin());
				}
				varcharsizes.push_back(atoi(numb.c_str()));
				rawcommand.erase(rawcommand.begin() + i);
				i--;
			}

		}
	}


	void printQuarry()
	{

	}

	bool hascomma(string s)
	{
		for(int i=0; i< s.length(); i++)
		{
			if (s[i] == ';')
				return true;
		}
		return false;
	}


	void getQuarriesList()
	{
		for(int i=0; i<Rawquarylist.size(); i++)
		{
			vector<string>rawquarry = Rawquarylist[i];
			QuarryStruct tempQ;
			findKeyWords(rawquarry, tempQ);
			findTypes(tempQ.ColumnTypes, tempQ.VarCharSizes, rawquarry);
			if (tempQ.KeyWords[0] != "SELECT")
			{
				cleanSpecialChars(rawquarry, specialChars);
			}
			findStrings(tempQ.QuarryParam, tempQ.names, rawquarry);
			if (tempQ.KeyWords[0] == "SELECT")
				eliminatecommas(tempQ.names);
			string x = "\"";
			cleanSpecialChars(tempQ.QuarryParam, x);
			cleanSpecialChars(tempQ.names, ";");
			QuarryList.push_back(tempQ);
		}
	}

	string specialChars = "()\\,;:";

	/*void FindConditions(vector<string> &rawcom, QuarryStruct &q)
	{
		for(int i=1; i<rawcom.size(); i++)
		{
			string temp = rawcom[i];
			string condition;
			for(int j=0; j<temp.size(); j++)
			{
				
				if (temp[j] == '=' ||
					temp[j] == '>' ||
					temp[j] == '<' || temp[j] == '!')
				{
					condition.push_back(temp[j]);
				}
				
			       

			}
			q.conditions.push_back(condition);
		}
		return;
	}*/

	
};

