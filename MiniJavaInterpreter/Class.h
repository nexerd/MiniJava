#pragma once
#include <string>
#include <vector>
using namespace std;

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

	void operator=(Variable& a)
	{
		if (type == "double" && a.type == "int")
		{
			value.Real = double(0.0) + a.value.Integer;
			return;
		}
		if (type == "boolean" && a.type == "int")
		{
			value.Boolean = a.value.Integer != 0;
			return;
		}
		if (type == "int" && a.type == "boolean")
		{
			value.Integer = 0 + a.value.Boolean;
			return;
		}
		if (type == a.type)
		{
			value =  a.value;
			return;
		}
		throw exception("Type");
	}

	Variable operator+(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez(type, string(), Value(value.Integer + a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Real + a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Boolean + a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Integer + a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez(type, string(), Value(value.Integer + a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez(type, string(), Value(value.Real + a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Boolean + a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator-(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez(type, string(), Value(value.Integer - a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Real - a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Boolean - a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Integer - a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez(type, string(), Value(value.Integer - a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez(type, string(), Value(value.Real - a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Boolean - a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator*(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez(type, string(), Value(value.Integer * a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Real * a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Boolean * a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Integer * a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez(type, string(), Value(value.Integer * a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez(type, string(), Value(value.Real * a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Boolean * a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator/(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez(type, string(), Value(value.Integer / a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Real / a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Boolean / a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Integer / a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez(type, string(), Value(value.Integer / a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez(type, string(), Value(value.Real / a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Boolean / a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator%(Variable& a)
	{
		if (type == "int" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Integer % a.value.Integer));
			return rez;
		}		
		throw exception("Type");
	}

	Variable operator%(Variable& a)
	{
		if (type == "int" && a.type == "int")
		{
			Variable rez(type, string(), Value(value.Integer % a.value.Real));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator&&(Variable& a)
	{
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Boolean && a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator||(Variable& a)
	{
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez(type, string(), Value(value.Boolean || a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator!()
	{
		if (type == "boolean")
		{
			Variable rez(type, string(), Value(!value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator<(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez("boolean", string(), Value(value.Integer < a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Real < a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Boolean < a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Integer < a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez("boolean", string(), Value(value.Integer < a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez("boolean", string(), Value(value.Real < a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Boolean < a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator==(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez("boolean", string(), Value(value.Integer == a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Real == a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Boolean == a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Integer == a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez("boolean", string(), Value(value.Integer == a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez("boolean", string(), Value(value.Real == a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Boolean == a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator>(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez("boolean", string(), Value(value.Integer > a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Real > a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Boolean > a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Integer > a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez("boolean", string(), Value(value.Integer > a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez("boolean", string(), Value(value.Real > a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Boolean > a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator<=(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez("boolean", string(), Value(value.Integer <= a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Real <= a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Boolean <= a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Integer <= a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez("boolean", string(), Value(value.Integer <= a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez("boolean", string(), Value(value.Real <= a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Boolean <= a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator!=(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez("boolean", string(), Value(value.Integer != a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Real != a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Boolean != a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Integer != a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez("boolean", string(), Value(value.Integer != a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez("boolean", string(), Value(value.Real != a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Boolean != a.value.Boolean));
			return rez;
		}
		throw exception("Type");
	}

	Variable operator>=(Variable& a)
	{
		if (type == "int" && a.type == "double")
		{
			Variable rez("boolean", string(), Value(value.Integer >= a.value.Real));
			return rez;
		}
		if (type == "double" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Real >= a.value.Integer));
			return rez;
		}
		if (type == "boolean" && a.type == "int")
		{
			Variable rez("boolean", string(), Value(value.Boolean >= a.value.Integer));
			return rez;
		}
		if (type == "int" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Integer >= a.value.Boolean));
			return rez;
		}
		if (type == a.type && type == "int")
		{
			Variable rez("boolean", string(), Value(value.Integer >= a.value.Integer));
			return rez;
		}
		if (type == a.type && type == "double")
		{
			Variable rez("boolean", string(), Value(value.Real >= a.value.Real));
			return rez;
		}
		if (type == "boolean" && a.type == "boolean")
		{
			Variable rez("boolean", string(), Value(value.Boolean >= a.value.Boolean));
			return rez;
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

	bool getVariable(string& name, vector<Variable>::iterator* v)
	{
		vector<Variable>::iterator iter = find(VarList.begin(), VarList.end(), name);
		if (iter != VarList.end())
		{
			*v = iter;
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