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

	bool is_mainObj = false;

	MyClass* curClass = NULL;
	Function* curFunc = NULL;
	Context* curContext = NULL;
	Context* curParametrs = NULL;
	vector<string> curSequence;
	vector<string> curArgumetLuist;
	vector<Function> curFuncList; 

	vector<string> buffer;

	vector<int> curPoint;
	int countPoint = 0;
	vector<pair<int, int>> curJumps;

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

	void correctSequence2(int p)
	{
		int num;
		char *PositionToJump = new char[1024];
		for (int i = 0; i < curSequence.size(); i++)
		{
			if (curSequence[i] == "$JMP" || curSequence[i] == "$JMP_true")
			{
				num = atoi(curSequence[i + 1].c_str());
				if (num >= p && curSequence[i] == "$JMP" || num > p && curSequence[i] == "$JMP_true")
				{					
					num += 2;
					_itoa(num, PositionToJump, 10);					
					curSequence[i + 1] = PositionToJump;
				}
			}
		}
		for (int i = 0; i < curPoint.size(); i++)
		{
			if (curPoint[i] > p)
				curPoint[i] += 2;
		}
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
			countPoint = 0;
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
			int dif = curSequence.size();
			if (Names.size() != 0)
			{
				if (Names.back() != "$S")
					buffer.push_back(Names.back());
				else
				{					
					curPoint.pop_back();
					dif = curPoint.size() ? curPoint.back() : 0;
				}
				Names.pop_back();
				
			}
			if (Names.size() != 0)
			{
				if (Names.back() != "$S")
					buffer.push_back(Names.back());
				else
				{
					curPoint.pop_back();
				/*	buffer.insert(buffer.begin(),
						curSequence.begin() + curPoint.back(),
						curSequence.begin() + dif);
					curSequence.erase(curSequence.begin() + curPoint.back(), curSequence.begin() + dif);*/
					dif = 0;
					
				}
				Names.pop_back();
					
			}
			
			curSequence.insert(curSequence.begin() + dif, buffer.begin(), buffer.end());
			Names.push_back("$S");
		
			buffer.clear();
			curSequence.push_back(Stack[1].str);
			curPoint.push_back(curSequence.size());			
			return;
		}
		if (leftSymbol == "присваивание")
		{
			if (Stack.size() > 3)
			{			
				int dif = curSequence.size();
				vector<string> bufS;
				if (Names.back() == "$S")
				{
					bufS.push_back("$S");		
					curPoint.pop_back();
					dif = curPoint.size() ? curPoint.back() : 0;

					while (Names.back() == "$S")
					{
						Names.pop_back();
					} 
					
				}
				else
				{
					bufS.push_back(Names.back());
					Names.pop_back();
				}
				string buf = Names.back();
				Names.pop_back();

				vector<string> toInsert;
				toInsert.push_back(".");
				
				if (Stack[0].str == "S")
				{
					toInsert.push_back(Names.back());
					Names.pop_back();
				}
				else
					toInsert.push_back(Stack[0].str);

				toInsert.push_back(buf);
				
				curSequence.insert(curSequence.begin() + dif, toInsert.begin(), toInsert.end());

				//Names.insert(Names.end(), bufS.begin(), bufS.end());
				if (bufS.front() != "$S")
					curSequence.push_back(bufS.front());
				//Names.push_back("$S");
				//curPoint.push_back(curSequence.size());
			}
			else
			{
				int dif = curSequence.size();
				if (Names.size() != 0)
				{
					if (Names.back() != "$S")
						buffer.push_back(Names.back());
					else
					{
						curPoint.pop_back();
						dif = curPoint.size() ? curPoint.back() : 0;
					}
					Names.pop_back();

				}
				if (Names.size() != 0)
				{
					if (Names.back() != "$S")
						buffer.insert(buffer.begin(), Names.back());
					else
					{
						curPoint.pop_back();
						dif = 0;

					}
					Names.pop_back();
				}

				curSequence.insert(curSequence.begin() + dif, buffer.begin(), buffer.end());
			}
			Names.push_back("$S");

			buffer.clear();
			curSequence.push_back("=");
			curPoint.push_back(curSequence.size());
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
				curPoint.push_back(curSequence.size());
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
						string buf = Names.back();
						Names.pop_back();
						curSequence.push_back(Names.back());
						Names.pop_back();
						Names.push_back(buf);
					}
					else 
						curSequence.push_back(Stack[0].str);	
					curSequence.push_back(Names.back());
					Names.pop_back();
					Names.push_back("$S");
					curPoint.push_back(curSequence.size());
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
						curPoint.push_back(curSequence.size());
					}
					else
					{
						if (Stack[0].str != "(")
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
							curPoint.push_back(curSequence.size());
						}
					}
					curArgumetLuist.clear();
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
					else
						curPoint.pop_back();
					Names.pop_back();
					Names.push_back("$S");
					curPoint.push_back(curSequence.size());
				}
				curSequence.push_back(Stack[0].str);
			}
			return;
		}
		
		if (leftSymbol == "функци€")
		{
			curFunc = new Function();

			//correctSequence();			

			curFunc->Sequence = curSequence;
			curSequence.clear();
			curPoint.clear();
			curJumps.clear();

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
			curClass->ClassBehavior.addFunction(*curFunc);
			if (curFunc->name == "main")
			{
				entryPoint = &curClass->ClassBehavior.FuncList.back();
				is_mainObj = true;				
			}
			else 
				is_mainObj = false;

			curFunc = NULL;
			curPoint.clear();
			countPoint = 0;
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
			while (Names.size() > 0 && Names.back() == "$S")
			{
				Names.pop_back();
			}
			if (Stack[0].str != "int" && Stack[0].str != "double" && Stack[0].str != "boolean")
			{
				if (Stack[0].str == curClass->name)
				{
					curContext->VarList.push_back(Variable(Stack[0].str, Names.back(), NULL));					
				}
				else
				{
					for (int j = 0; j < Classes.size(); j++)
					if (Stack[0].str == Classes[j].name)
					{
						curContext->VarList.push_back(Variable(Stack[0].str, Names.back(), NULL));
						//Classes[j].makeObject(Names.back())));
						break;
					}
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

		if (leftSymbol == "ввод")
		{			
			if (Stack.size() == 2)
			{
				curSequence.push_back(Names.back());
				Names.pop_back();				
			}	
			else
			{
				curSequence.push_back(".");
				if (Stack[1].str == "S")
				{
					string buf = Names.back();
					Names.pop_back();
					curSequence.push_back(Names.back());
					Names.pop_back();
					Names.push_back(buf);

				}
				else
					curSequence.push_back(Stack[1].str);
				curSequence.push_back(Names.back());
				Names.pop_back();
				
			}			
			curSequence.push_back("$input");
			Names.push_back("$S");
			curPoint.push_back(curSequence.size());
			return;
		}
		if (leftSymbol == "вывод")
		{
			if (Stack.size() == 2)
			{
				curSequence.push_back(Names.back());
				Names.pop_back();
			}
			else
			{
				curSequence.push_back(".");
				if (Stack[1].str == "S")
				{
					string buf = Names.back();
					Names.pop_back();
					curSequence.push_back(Names.back());
					Names.pop_back();
					Names.push_back(buf);

				}
				else
					curSequence.push_back(Stack[1].str);
				curSequence.push_back(Names.back());
				Names.pop_back();
				
			}			
			curSequence.push_back("$output");
			Names.push_back("$S");
			curPoint.push_back(curSequence.size());
			return;
		}

		if (leftSymbol == "оператор_услови€")
		{
			//curPoint.push_back(curSequence.size());
			//countPoint = 0;
			//Names.push_back("$if");
			//countPoint.push_back(0);
			countPoint = 1;
			return;


		}

		if (leftSymbol == "условие")
		{
			//++countPoint;
			int num = curPoint.size() - countPoint, posInsert = curPoint[num];
			curSequence.insert(curSequence.begin() + posInsert, "$JMP");
			char *PositionToJump = new char[1024];
			_itoa(curPoint.back() , PositionToJump, 10);
			curSequence.insert(curSequence.begin() + posInsert + 1, PositionToJump);
			
			//curJumps.push_back(make_pair(posInsert, curPoint.back()));
			correctSequence2(posInsert);
			countPoint = 0;			
			curPoint.erase(curPoint.begin() + num, curPoint.end());

			curPoint.push_back(curSequence.size());
			++countPoint;
			return;
		}

		if (leftSymbol == "полное_условие")
		{
			//countPoint = 3;
			int num = curPoint.size() - countPoint, posInsert = curPoint[num];
			curSequence.insert(curSequence.begin() + posInsert, "$JMP_true");
			char *PositionToJump = new char[1024];
			_itoa(curPoint.back() , PositionToJump, 10);
			curSequence.insert(curSequence.begin() + posInsert + 1, PositionToJump);
			//countPoint.pop_back();
			//curJumps.back().second += 2;
			//curJumps.push_back(make_pair(posInsert, curPoint.back()));
			correctSequence2(posInsert);
			countPoint = 0;
			curPoint.erase(curPoint.begin() + num, curPoint.end());
			curPoint.push_back(curSequence.size());
			++countPoint;
			return;
		}

		if (leftSymbol == "программа")
		{
			countPoint++;
			return;
		}

		if (leftSymbol == "блок_функции")
		{
		//	--countPoint;
			//curFunc->Sequence = curSequence;
			//curSequence.clear();
			return;
		}

		if (leftSymbol == "создание_объекта")
		{			
			curSequence.push_back(Stack[1].str);
			curSequence.push_back("$create_obj");
			Names.push_back("$S");
			curPoint.push_back(curSequence.size());
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