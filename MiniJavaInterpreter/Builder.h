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


	MyClass* curClass = NULL;
	Function* curFunc = NULL;
	Context* curContext = NULL;
	Context* curParametrs = NULL;
	vector<string> curSequence;

	vector<Function> curFuncList; 

	vector<string> buffer;

	Builder()
	{
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
		if (leftSymbol == "�������������")
		{
			Names.push_back(Stack.back().str);
			return;
		}

		if (leftSymbol == "���������_������")
		{
			//Classes.push_back(MyClass));
			curClass = new MyClass(Stack[0].str == "static", Names.back());
			curContext = new Context();
			Names.pop_back();
			return;
		}

		if (leftSymbol == "���������")
		{
			if (curParametrs == NULL)
				curParametrs = new Context();
			for (int i = 0; i < Stack.size(); i++)
			{
				if (Stack[i].str_type == "type")
				{
					curParametrs->VarList.push_back(Variable(Stack[i].str, Names.back()));
					Names.pop_back();
				}
			}
			return;
		}

		if (leftSymbol == "��������_1" || leftSymbol == "��������_2" || leftSymbol == "������������"
			|| leftSymbol == "���_���1" || leftSymbol == "���_���2" || leftSymbol == "���_���4"
			|| leftSymbol == "���_���5" || leftSymbol == "���_���6")
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
		if (leftSymbol == "��������_3")
		{
			if (Stack.size() == 1)
			{
				Names.push_back(Stack[0].str);
			}
			return;
		}
		if (leftSymbol == "���_���3")
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
		if (leftSymbol == "����_�������")
		{
			//curFunc->Sequence = curSequence;
			//curSequence.clear();
			return;
		}
		if (leftSymbol == "�������")
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
			curFunc = NULL;
			return;
		}
		if (leftSymbol == "�����")
		{
			curClass->ClassContext = *curContext;
			curContext = new Context();
			Classes.push_back(*curClass);
			curClass = NULL;
			return;
		}
		if (leftSymbol == "����������_����������_������")
		{
			while (Names.back() == "$S")
			{
				Names.pop_back();
			}
			curContext->VarList.push_back(Variable(Stack[0].str, Names.back()));
			Names.pop_back();
			return;
		}
	
	};

	void makeProgramm(vector<vector<lexem>>& ListOfStack, vector<int>& ListOfNumbers)
	{
		for (int i = 0; i < ListOfStack.size(); i++)
		{
			makePart(ListOfStack[i], ListOfNumbers[i]);
		}
	}


};