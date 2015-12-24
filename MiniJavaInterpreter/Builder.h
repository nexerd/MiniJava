#pragma once
#include "Class.h"
#include "Rule.h"
#include "Lexem.h"
#include <fstream>

struct Builder
{
	string RuleFile;
	vector<rule> P;

	vector<string> Names;

	vector<MyClass> Classes;

	Function* entryPoint;
	MyClass* mainObj;

	bool is_mainObj;

	MyClass* curClass = NULL;
	Function* curFunc = NULL;
	Context* curContext = NULL;
	Context* curParametrs = NULL;
	vector<string> curSequence;
	vector<string> curArgumetLuist;
	vector<Function> curFuncList; 

	vector<string> buffer;

	Builder()
	{
		Classes.reserve(200);
		RuleFile = "RuleFile.txt";
		readRule();
	};

	void readRule()
	{
		ifstream fin(RuleFile);
		string buf;
		int size;
		if (!fin.is_open())
			throw exception("File is not open!");
		while (!fin.eof())
		{
			P.push_back(rule());
			fin >> P.back().left;
			fin >> size;
			if (size == -1 || P.back().left == " " || P.back().left == "")
			{
				P.pop_back();
				break;
			}
			P.back().right.reserve(size);
			while (size-- != 0)
			{
				fin >> buf;
				P.back().right.push_back(buf);
			}
		}
		fin.close();
	}

	void makePart(vector<lexem>& Stack, int& numberOfRule)
	{
		string leftSymbol = P[numberOfRule].left;
		if (leftSymbol == "идентификатор")
		{
			Names.push_back(Stack.back().str);
			return;
		}

		if (leftSymbol == "заголовок_класса")
		{
			//Classes.push_back(MyClass));
			curClass = new MyClass(Stack[0].str == "static", Names.back());
			curContext = new Context();
			Names.pop_back();
			return;
		}

		if (leftSymbol == "параметры")
		{
			if (curParametrs == NULL)
				curParametrs = new Context();
			if (Stack[0].str_type == "type")
			{
				curParametrs->VarList.insert(curParametrs->VarList.begin(),
					Variable(Stack[0].str, Names.back()));
				Names.pop_back();
			}
			return;
		}

		if (leftSymbol == "операци€_1" || leftSymbol == "операци€_2"
			|| leftSymbol == "лог_выр1" || leftSymbol == "лог_выр2" || leftSymbol == "лог_выр4"
			|| leftSymbol == "лог_выр5" || leftSymbol == "лог_выр6")
		{

			if (Names.size() != 0)
			{
				if (Names.back() != "$S")
					buffer.push_back(Names.back());
				Names.pop_back();
			}
			if (Names.size() != 0)
			{
				if (Names.back() != "$S")
					buffer.push_back(Names.back());
				Names.pop_back();
			}
			curSequence.insert(curSequence.end(), buffer.rbegin(), buffer.rend());
			Names.push_back("$S");
			buffer.clear();
			curSequence.push_back(Stack[1].str);
			return;
		}
		if (leftSymbol == "присваивание")
		{
			if (Stack.size() > 3)
			{
				curSequence.push_back(".");
				if (Stack[0].str == "S")
				{
					curSequence.push_back(Names.back());
					Names.pop_back();
				}
				else
					curSequence.push_back(Stack[0].str);
				string buf = Names.back();
				Names.pop_back();
				curSequence.push_back(Names.back());
				Names.pop_back();
				Names.push_back(buf);
				Names.push_back("$S");
			}
			if (Names.size() != 0)
			{
				if (Names.back() != "$S")
					buffer.push_back(Names.back());
				Names.pop_back();
			}
			if (Names.size() != 0)
			{
				if (Names.back() != "$S")
					buffer.push_back(Names.back());
				Names.pop_back();
			}
			curSequence.insert(curSequence.end(), buffer.rbegin(), buffer.rend());
			Names.push_back("$S");
			buffer.clear();
			curSequence.push_back("=");
			return;
		}
		if (leftSymbol == "операци€_3")
		{
			if (Stack.size() == 1)
			{
				//Names.push_back(Stack[0].str);
				Names.push_back("$S");
				curSequence.push_back(Stack[0].str);
				curSequence.push_back(Stack[0].str_type);
				curSequence.push_back("$create");
			}
			else
			{
				//if (Stack[0].str != "(" && Stack[2].str != ")")
				//{
					
				//}
				if (Stack.size() == 3 && Stack[1].str == ".")
				{
					curSequence.push_back(".");
					if (Stack[0].str == "S")
					{
						curSequence.push_back(Names.back());
						Names.pop_back();
					}
					else 
						curSequence.push_back(Stack[0].str);					
					curSequence.push_back(Names.back());
					Names.pop_back();
					Names.push_back("$S");
				}
				else
				{
					if (Stack[1].str == ".")
					{
						if (Stack[4].str == "S")
						{
							curArgumetLuist.insert(curArgumetLuist.begin(), Names.back());
							Names.pop_back();
						}
						for (int i = curArgumetLuist.size() - 1; i >= 0; i--)
							curSequence.push_back(curArgumetLuist[i]);
						char *SizeArgList = new char[1024];
						_itoa(curArgumetLuist.size(), SizeArgList, 10);
						curSequence.push_back("$function");
						curSequence.push_back(SizeArgList);
						curSequence.push_back(Names.back());
						Names.pop_back();
						if (Stack[0].str == "S")
						{
							curSequence.push_back(Names.back());
							Names.pop_back();
						}
						else
							curSequence.push_back(Stack[0].str);
						//curSequence.push_back(Stack[1].str);
						Names.push_back("$S");
					}
					else
					{
						if (Stack[2].str == "S")
						{
							curArgumetLuist.insert(curArgumetLuist.begin(), Names.back());
							Names.pop_back();
						}
						for (int i = curArgumetLuist.size() - 1; i >= 0; i--)
							curSequence.push_back(curArgumetLuist[i]);
						char *SizeArgList = new char[1024];
						_itoa(curArgumetLuist.size(), SizeArgList, 10);
						curSequence.push_back("$own_function");
						curSequence.push_back(SizeArgList);
						curSequence.push_back(Names.back());
						Names.pop_back();
						Names.push_back("$S");
					}
				}
			}
			return;
		}
		if (leftSymbol == "лог_выр3")
		{
			if (Stack.size() == 2)
			{
				if (Names.size() != 0)
				{
					if (Names.back() != "$S")
						curSequence.push_back(Names.back());
					Names.pop_back();
					Names.push_back("$S");

				}
				curSequence.push_back(Stack[0].str);
			}
			return;
		}
		if (leftSymbol == "блок_функции")
		{
			//curFunc->Sequence = curSequence;
			//curSequence.clear();
			return;
		}
		if (leftSymbol == "функци€")
		{
			curFunc = new Function();

			curFunc->Sequence = curSequence;
			curSequence.clear();

			if (curContext != NULL)
			{
				curFunc->CurContext = *curContext;				
			}
			curContext = new Context();

			if (curParametrs != NULL)
			{
				curFunc->Parametrs = *curParametrs;
				curParametrs = NULL;
			}

			while (Names.back() == "$S")
			{
				Names.pop_back();
			} 
			curFunc->name = Names.back();
			Names.pop_back();

			curFunc->returnValue.type = Stack[0].str;
			curClass->FuncList.push_back(*curFunc);
			if (curFunc->name == "main")
			{
				entryPoint = &curClass->FuncList.back();
				is_mainObj = true;				
			}

			curFunc = NULL;
			return;
		}
		if (leftSymbol == "класс")
		{
			curClass->ClassContext = *curContext;			
			curContext = new Context();
			Classes.push_back(*curClass);			
			if (is_mainObj)
			{
				is_mainObj = false;
				mainObj = &Classes.back();
			}
			curClass = NULL;
			return;
		}
		if (leftSymbol == "объ€вление_переменной_класса")
		{
			while ( Names.back() == "$S")
			{
				Names.pop_back();
			}
			if (Stack[0].str != "int" && Stack[0].str != "double" && Stack[0].str != "boolean")
			{
				for (int j = 0; j < Classes.size(); j++)
				if (Stack[0].str == Classes[j].name)
				{
					curContext->VarList.push_back(Variable(Stack[0].str, Names.back(),
						Classes[j].makeObject(Names.back())));
					break;
				}
			}
			else 
				curContext->VarList.push_back(Variable(Stack[0].str, Names.back()));
			Names.pop_back();
			return;
		}

		if (leftSymbol == "выражение")
		{
			/*while (Names.back() == "$S")
			{
				Names.pop_back();
			}*/
			if (Stack[1].str_type == "S")
			{
				if (Names.back() != "$S")
				{
					curSequence.push_back(Names.back());
					Names.pop_back();
				}
			}
			else 
				curSequence.push_back(Stack[1].str);
			curSequence.push_back(Stack[0].str);
		
			return;
		}

		if (leftSymbol == "список_аргументов")
		{
			curArgumetLuist.insert(curArgumetLuist.begin(), Names.back());
			Names.pop_back();
			return;
		}
		/*if (leftSymbol == "вызов_функции")
		{
			curArgumetLuist.insert(curArgumetLuist.begin(), Names.back());
			Names.pop_back();
			return;
		}*/
	
	};

};