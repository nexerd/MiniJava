#include "Class.h"


struct Executor
{
	vector<MyClass>* myClasses;
	vector<Function*> FunStack;

	Executor(vector<MyClass>* Classes)
	{
		myClasses = Classes;		
	}

	Variable* getVariable(string& name, MyClass** Obj, Function* entryPoint)
	{
		Variable* A;
		if (!entryPoint->CurContext.getVariable(name, &A))
		{
			if (!entryPoint->Parametrs.getVariable(name, &A))
			{
				if (!(*Obj)->ClassContext.getVariable(name, &A))
				{
					for (int i = 0; i < myClasses->size(); i++)
					{
						if ((*myClasses)[i].name == name && (*myClasses)[i].is_static)
						{		
							A = new Variable();
							A->value.Obj = &(*myClasses)[i];
							A->type = "Obj";
							return A;
						}
					}
					throw exception("Name!");
				}
					
			}
		}
		return A;
	}

	void RunProgramm(MyClass** Obj, Function* entryPoint)
	{
		if (!(*Obj)->is_static && !(*Obj)->is_create)
			throw exception("Object!");
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
			if (entryPoint->Sequence[i] == "$function")
			{
				i += 3;
			}

			if (entryPoint->Sequence[i] == ".")
			{
				Function* nextFun;
				MyClass* Obj;
				string nameF = entryPoint->Sequence[i - 2];
				if (VarStack.back()->type != "Obj")
					throw exception("Object!");				
				Obj = VarStack.back()->value.Obj;
				Obj->getFunction(nameF, &nextFun);
				VarStack.pop_back();
				int countParams = atoi(entryPoint->Sequence[i - 3].c_str());
				for (int j = 0; j < countParams; j++)
				{
					nextFun->Parametrs.VarList[j] = VarStack.back();
					VarStack.pop_back();
				}
				RunProgramm(&Obj, nextFun);
				if (nextFun->returnValue.type != "void")
					VarStack.push_back(&nextFun->returnValue);
				continue;
			}
			if (entryPoint->Sequence[i] == "return")
			{
				A = VarStack.back();
				VarStack.pop_back();
				entryPoint->returnValue = A;
				return;
			}
			VarStack.push_back(getVariable( entryPoint->Sequence[i], Obj, entryPoint));
		}
	
	}



};