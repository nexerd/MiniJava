#include "Class.h"


struct Executor
{
	vector<MyClass> myClasses;
	vector<Function*> FunStack;

	Executor(vector<MyClass>& Classes)
	{
		myClasses = Classes;		
	}

	Variable* getVariable(string& name, Function* entryPoint)
	{
		Variable* A;
		if (!entryPoint->CurContext.getVariable(name, &A))
		{
			if (!entryPoint->Parametrs.getVariable(name, &A))
			{
				if (!entryPoint->Obj->ClassContext.getVariable(name, &A))
					throw exception("Name!");
			}
		}
		return A;
	}

	void RunProgramm(Function* entryPoint)
	{
		FunStack.push_back(entryPoint);
		vector<Variable*> VarStack;
		Variable* A;
		Variable* B;
		for (int i = 0; i <  entryPoint->Sequence.size(); i++)
		{
			if ( entryPoint->Sequence[i] == "+")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A + B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "-")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A - B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "*")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A * B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "/")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A / B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "%")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A % B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "&&")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A && B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "||")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A || B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "!")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(!*A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "<")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A < B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "==")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A == B);
				continue;
			}
			if ( entryPoint->Sequence[i] == ">")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A > B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "<=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A < B);
				continue;
			}
			if ( entryPoint->Sequence[i] == "!=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A == B);
				continue;
			}
			if ( entryPoint->Sequence[i] == ">=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*A > B);
				continue;
			}
			if (entryPoint->Sequence[i] == "=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				*A = B;
				continue;
			}
			if (i + 2 < entryPoint->Sequence.size() && 
				entryPoint->Sequence[i + 2] == "$create")
			{
				string type;
				if (entryPoint->Sequence[i + 1] == "integer")
				{
					type = "int";
					VarStack.push_back(new Variable(type,
						Value(atoi(entryPoint->Sequence[i].c_str()))));
				}
				if (entryPoint->Sequence[i + 1] == "real")
				{				
					type = "double";
					VarStack.push_back(new Variable(type,
						Value(atof(entryPoint->Sequence[i].c_str()))));
				}
				if (entryPoint->Sequence[i + 1] == "boolean")
				{
					VarStack.push_back(new Variable(entryPoint->Sequence[i],
						Value("true" == entryPoint->Sequence[i + 1])));
				}
				i += 2;
				continue;
			}
			
			VarStack.push_back(getVariable( entryPoint->Sequence[i], entryPoint));
		}
	
	}



};