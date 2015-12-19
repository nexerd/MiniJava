#pragma once
#include <string>
#include <vector>
using namespace std;

struct Variable
{
	string type;
	string name;
	void* value;

	Variable() {};

	Variable(string& t, string& n, void* v)
	{
		type = t;
		name = n;
		value = v;
	}

	Variable(string& t, string& n)
	{
		type = t;
		name = n;
	}
};

struct Context
{
	vector<Variable> VarList;
	bool is_static;

	Context() {};

	void addVariable(Variable& a)
	{
		VarList.push_back(a);
	}
};

struct Function
{
	string name;
	bool is_static;
	Context CurContext;
	Context Parametrs;
	vector<string> Sequence;
	Variable returnValue;
	Function() {};
};

struct MyClass
{
	string name;
	bool is_static;
	vector<Function> FuncList;
	Context ClassContext;

	MyClass(bool _static, string& n) 
	{
		is_static = _static;
		name = n;
	};

	MyClass();
};