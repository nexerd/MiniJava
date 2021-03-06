#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct MyClass;
struct Object;

class execute_exception : exception
{
public:
	const char* str;
	execute_exception(string cause) : exception()
	{
		char* buff = new char[100];
		strcpy(buff, cause.c_str());
		str = buff;
	}
	virtual const char* what() const throw() { return str; }
};

union Value
{
	int Integer;
	double Real;
	bool Boolean;
	Object* Obj;
	Value()	{};
	Value(int v)
	{
		Integer = v;
	}
	Value(double v)
	{
		Real = v;
	}
	Value(bool v)
	{
		Boolean = v;
	}
	Value(Object* v)
	{
		Obj = v;
	}

};

struct Variable
{
	string type;
	string name;
	Value value;

	Variable() {};

	Variable(string& t,  Value v)
	{
		type = t;
		value = v;
	}

	Variable(string& t, string& n)
	{
		type = t;
		name = n;
	}

	Variable(string t, string n, Value v)
	{
		type = t;
		name = n;
		value = v;
	}

	bool operator==(const string& n) const
	{
		return name == n;
	}

	void operator=(Variable* a)
	{
		if (type == "double" && a->type == "int")
		{
			value.Real = double(0.0) + a->value.Integer;
			return;
		}
		if (type == "boolean" && a->type == "int")
		{
			value.Boolean = a->value.Integer != 0;
			return;
		}
		if (type == "int" && a->type == "boolean")
		{
			value.Integer = 0 + a->value.Boolean;
			return;
		}
		if (type == a->type || a->type == "NULL")
		{
			value =  a->value;
			return;
		}
		throw execute_exception("Inconsistency type in operation '='");
	}

	Variable* operator+(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable(a->type, string(), Value(value.Integer + a->value.Real));

		}
		if (type == "double" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Real + a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Boolean + a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Integer + a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable(type, string(), Value(value.Integer + a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable(type, string(), Value(value.Real + a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean + a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '+'");
	}

	Variable* operator-(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable(a->type, string(), Value(value.Integer - a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Real - a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Boolean - a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Integer - a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable(type, string(), Value(value.Integer - a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable(type, string(), Value(value.Real - a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean - a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '-'");
	}

	Variable* operator*(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable(a->type, string(), Value(value.Integer * a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Real * a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Boolean * a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Integer * a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable(type, string(), Value(value.Integer * a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable(type, string(), Value(value.Real * a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean * a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '*'");
	}

	Variable* operator/(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			if (a->value.Real == 0)
				throw execute_exception("Division by zero");
			return new Variable(a->type, string(), Value(value.Integer / a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			if (a->value.Integer == 0)
				throw execute_exception("Division by zero");
			return new Variable(type, string(), Value(value.Real / a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			if (a->value.Integer == 0)
				throw execute_exception("Division by zero");
			return new Variable(type, string(), Value(value.Boolean / a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			if (a->value.Boolean == 0)
				throw execute_exception("Division by zero");
			return new Variable(type, string(), Value(value.Integer / a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			if (a->value.Integer == 0)
				throw execute_exception("Division by zero");
			return new Variable(type, string(), Value(value.Integer / a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			if (a->value.Real == 0)
				throw execute_exception("Division by zero");
			return new Variable(type, string(), Value(value.Real / a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			if (a->value.Boolean == 0)
				throw execute_exception("Division by zero");
			return new Variable(type, string(), Value(value.Boolean / a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '/'");
	}

	Variable* operator%(Variable* a)
	{
		if (type == "int" && a->type == "int")
		{
			if (a->value.Integer == 0)
				throw execute_exception("Division by zero");
			return new Variable(type, string(), Value(value.Integer % a->value.Integer));
			 
		}		
		throw execute_exception("Inconsistency type in operation '%'");
	}

	Variable* operator&&(Variable* a)
	{
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean && a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '&&'");
	}

	Variable* operator||(Variable* a)
	{
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean || a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '||'");
	}

	Variable* operator!()
	{
		if (type == "boolean")
		{
			return new Variable(type, string(), Value(!value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '!'");
	}

	Variable* operator<(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable("boolean", string(), Value(value.Integer < a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Real < a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Boolean < a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Integer < a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable("boolean", string(), Value(value.Integer < a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable("boolean", string(), Value(value.Real < a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Boolean < a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '<'");
	}

	Variable* operator==(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable("boolean", string(), Value(value.Integer == a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Real == a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Boolean == a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Integer == a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable("boolean", string(), Value(value.Integer == a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable("boolean", string(), Value(value.Real == a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Boolean == a->value.Boolean));
			 
		}
		if (a->type == "NULL")
		{
			return new Variable("boolean", string(), Value(value.Obj == a->value.Obj));

		}
		throw execute_exception("Inconsistency type in operation '=='");
	}

	Variable* operator>(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable("boolean", string(), Value(value.Integer > a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Real > a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Boolean > a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Integer > a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable("boolean", string(), Value(value.Integer > a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable("boolean", string(), Value(value.Real > a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Boolean > a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '>'");
	}

	Variable* operator<=(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable("boolean", string(), Value(value.Integer <= a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Real <= a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Boolean <= a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Integer <= a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable("boolean", string(), Value(value.Integer <= a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable("boolean", string(), Value(value.Real <= a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Boolean <= a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '<='");
	}

	Variable* operator!=(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable("boolean", string(), Value(value.Integer != a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Real != a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Boolean != a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Integer != a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable("boolean", string(), Value(value.Integer != a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable("boolean", string(), Value(value.Real != a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Boolean != a->value.Boolean));
			 
		}
		if (a->type == "NULL")
		{
			return new Variable("boolean", string(), Value(value.Obj != a->value.Obj));

		}
		throw execute_exception("Inconsistency type in operation '!='");
	}

	Variable* operator>=(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable("boolean", string(), Value(value.Integer >= a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Real >= a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable("boolean", string(), Value(value.Boolean >= a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Integer >= a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable("boolean", string(), Value(value.Integer >= a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable("boolean", string(), Value(value.Real >= a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable("boolean", string(), Value(value.Boolean >= a->value.Boolean));
			 
		}
		throw execute_exception("Inconsistency type in operation '>='");
	}

	void input()
	{
		cout << "Input value of " << name << " : ";
		if (type == "int")
		{
			cin >> value.Integer;
			return;
		}
		if (type == "boolean")
		{
			cin >> value.Boolean;
			return;
		}
		if (type == "double")
		{
			cin >> value.Real;
			return;
		}
		throw execute_exception("Inconsistency type in operation 'Input'");		
	}

	void output()
	{
		cout << "Output value of " << name << " : ";
		if (type == "int")
		{
			cout << value.Integer << endl;
			return;
		}
		if (type == "boolean")
		{
			cout << value.Boolean << endl;
			return;
		}
		if (type == "double")
		{
			cout << value.Real << endl;
			return;
		}
		throw execute_exception("Inconsistency type in operation 'Output'");
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

	bool getVariable(string& name, Variable** v)
	{
		vector<Variable>::iterator iter = find(VarList.begin(), VarList.end(), name);
		if (iter != VarList.end())
		{
			*v = &(*iter);
			return true;
		}
		return false;
	}

	void operator =(Context* classContext)
	{
		VarList = vector<Variable>(classContext->VarList.begin(), classContext->VarList.end());
	}
};

struct Function
{
	string name;
	bool is_static;
	bool is_returned = false;
	Context CurContext;
	Context Parametrs;
	vector<string> Sequence;
	Variable returnValue;

	bool operator==(const string& n) const
	{
		return name == n;
	}

	Function() {};
};

struct Behavior
{
	vector<Function> FuncList;

	bool getFunction(string& name, Function** f)
	{
		vector<Function>::iterator iter = find(FuncList.begin(), FuncList.end(), name);
		if (iter != FuncList.end())
		{
			*f = &(*iter);
			return true;
		}
		return false;
	}

	void addFunction(Function& f)
	{
		FuncList.push_back(f);
	}
};

struct Object
{
	MyClass*  objType;
	Context objContext;
	Behavior* objBehavior;
	Object(){};
	Object(MyClass& mClass);
	Context* getContext()
	{
		return &objContext;
	}

};

struct MyClass
{
	string name;
	//string type;
	bool is_static;
	Behavior ClassBehavior;
	Context ClassContext;
	

	Value* makeObject()
	{
		if (is_static)
			throw execute_exception("'" + name + "' is static class!");

		Value* A = new Value(new  Object(*this));
		return A;
	}

	MyClass(bool _static, string& n) 
	{
		ClassBehavior.FuncList.reserve(30);
		is_static = _static;		
		name = n;
	};

	Context* getContext()
	{
		if (!is_static)
			throw execute_exception("'" + name + "' is not static class!");
		return &ClassContext;
	}

	MyClass();
};




Object::Object(MyClass& mClass)
{
	objType = &mClass;
	objContext = mClass.ClassContext;
	objBehavior = &mClass.ClassBehavior;
}