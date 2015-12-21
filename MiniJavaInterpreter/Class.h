#pragma once
#include <string>
#include <vector>
using namespace std;

struct MyClass;

union Value
{
	int Integer;
	double Real;
	bool Boolean;
	MyClass* Obj;
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
	Value(MyClass* v)
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
		if (type == a->type)
		{
			value =  a->value;
			return;
		}
		throw exception("Type");
	}

	Variable* operator+(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable(type, string(), Value(value.Integer + a->value.Real));

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
		throw exception("Type");
	}

	Variable* operator-(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable(type, string(), Value(value.Integer - a->value.Real));
			 
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
		throw exception("Type");
	}

	Variable* operator*(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable(type, string(), Value(value.Integer * a->value.Real));
			 
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
		throw exception("Type");
	}

	Variable* operator/(Variable* a)
	{
		if (type == "int" && a->type == "double")
		{
			return new Variable(type, string(), Value(value.Integer / a->value.Real));
			 
		}
		if (type == "double" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Real / a->value.Integer));
			 
		}
		if (type == "boolean" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Boolean / a->value.Integer));
			 
		}
		if (type == "int" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Integer / a->value.Boolean));
			 
		}
		if (type == a->type && type == "int")
		{
			return new Variable(type, string(), Value(value.Integer / a->value.Integer));
			 
		}
		if (type == a->type && type == "double")
		{
			return new Variable(type, string(), Value(value.Real / a->value.Real));
			 
		}
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean / a->value.Boolean));
			 
		}
		throw exception("Type");
	}

	Variable* operator%(Variable* a)
	{
		if (type == "int" && a->type == "int")
		{
			return new Variable(type, string(), Value(value.Integer % a->value.Integer));
			 
		}		
		throw exception("Type");
	}

	Variable* operator&&(Variable* a)
	{
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean && a->value.Boolean));
			 
		}
		throw exception("Type");
	}

	Variable* operator||(Variable* a)
	{
		if (type == "boolean" && a->type == "boolean")
		{
			return new Variable(type, string(), Value(value.Boolean || a->value.Boolean));
			 
		}
		throw exception("Type");
	}

	Variable* operator!()
	{
		if (type == "boolean")
		{
			return new Variable(type, string(), Value(!value.Boolean));
			 
		}
		throw exception("Type");
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
		throw exception("Type");
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
		throw exception("Type");
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
		throw exception("Type");
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
		throw exception("Type");
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
		throw exception("Type");
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
		throw exception("Type");
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
};

struct Function
{
	string name;
	bool is_static;
	Context CurContext;
	Context Parametrs;
	vector<string> Sequence;
	Variable returnValue;
	MyClass* Obj;
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