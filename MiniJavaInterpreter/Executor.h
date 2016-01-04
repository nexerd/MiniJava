#pragma once
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

	Variable* createObj(string& type)
	{
		for (int i = 0; i < myClasses->size(); i++)
		{
			if ((*myClasses)[i].name == type)
			{
				return new Variable(type, *((*myClasses)[i].makeObject()));
			}
		}
		throw exception("Name!");
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
				VarStack.push_back(*B + A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "-")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B - A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "*")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B * A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "/")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B / A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "%")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B % A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "&&")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B && A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "||")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B || A);
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
				VarStack.push_back(*B < A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "==")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B == A);
				continue;
			}
			if ( entryPoint->Sequence[i] == ">")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B > A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "<=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B < A);
				continue;
			}
			if ( entryPoint->Sequence[i] == "!=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B == A);
				continue;
			}
			if ( entryPoint->Sequence[i] == ">=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(*B > A);
				continue;
			}
			if (entryPoint->Sequence[i] == "=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				*B = A;
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
					type = "boolean";
					VarStack.push_back(new Variable(type,
						Value("true" == entryPoint->Sequence[i])));
				}
				i += 2;
				continue;
			}
			if (entryPoint->Sequence[i] == "$create")
			{
				string type;
				if (entryPoint->Sequence[i - 1] == "integer")
				{
					type = "int";
					VarStack.push_back(new Variable(type,
						Value(atoi(entryPoint->Sequence[i - 2].c_str()))));
				}
				if (entryPoint->Sequence[i - 1] == "real")
				{
					type = "double";
					VarStack.push_back(new Variable(type,
						Value(atof(entryPoint->Sequence[i - 2].c_str()))));
				}
				if (entryPoint->Sequence[i - 1] == "boolean")
				{
					type = "boolean";
					VarStack.push_back(new Variable(type,
						Value("true" == entryPoint->Sequence[i - 2])));
				}
				//i += 2;
				continue;
			}
			if (entryPoint->Sequence[i] == "$function")
			{
				Function* nextFun;
				
				string nameF = entryPoint->Sequence[i + 2];
				VarStack.push_back(getVariable(entryPoint->Sequence[i + 3], Obj, entryPoint));
				
				MyClass* ObjF;
				ObjF = VarStack.back()->value.Obj;
				ObjF->getFunction(nameF, &nextFun);
				VarStack.pop_back();
				int countParams = atoi(entryPoint->Sequence[i + 1].c_str());
				for (int j = 0; j < countParams; j++)
				{
					nextFun->Parametrs.VarList[j] = VarStack.back();
					VarStack.pop_back();
				}
				RunProgramm(&ObjF, nextFun);
				if (nextFun->returnValue.type != "void")
					VarStack.push_back(&nextFun->returnValue);
				i += 3;
				continue;
			}

			if (entryPoint->Sequence[i] == "$own_function")
			{
				Function* nextFun;
				string nameF = entryPoint->Sequence[i + 2];
				(*Obj)->getFunction(nameF, &nextFun);				
				
				int countParams = atoi(entryPoint->Sequence[i + 1].c_str());
				for (int j = 0; j < countParams; j++)
				{
					nextFun->Parametrs.VarList[j] = VarStack.back();
					VarStack.pop_back();
				}
				RunProgramm(Obj, nextFun);
				if (nextFun->returnValue.type != "void")
					VarStack.push_back(&nextFun->returnValue);
				i += 2;
				continue;
			}


			if (entryPoint->Sequence[i] == ".")
			{
				VarStack.push_back(getVariable(entryPoint->Sequence[i + 1], Obj, entryPoint));
				VarStack.back()->value.Obj->ClassContext.getVariable(entryPoint->Sequence[i + 2], &A);
				VarStack.pop_back();
				VarStack.push_back(A);	
				i += 2;
				continue;
			}
			if (entryPoint->Sequence[i] == "return")
			{
				if (VarStack.size() != 0)
				{
					A = VarStack.back();
					VarStack.pop_back();
					entryPoint->returnValue = A;
				}				
				return;
			}
			if (entryPoint->Sequence[i] == "$input")
			{
				A = VarStack.back();
				VarStack.pop_back();
				A->input();
				continue;
			}
			if (entryPoint->Sequence[i] == "$output")
			{
				A = VarStack.back();
				VarStack.pop_back();
				A->output();
				continue;
			}
			if (entryPoint->Sequence[i] == "$JMP")
			{
				A = VarStack.back();
				VarStack.pop_back();
				if (!A->value.Boolean)
					i = atoi(entryPoint->Sequence[i + 1].c_str()) - 1;
				else
					++i;
				continue;
			}
			if (entryPoint->Sequence[i] == "$JMP_true")
			{
				i = atoi(entryPoint->Sequence[i + 1].c_str()) - 1;
				continue;
			}
			if (entryPoint->Sequence[i + 1] == "$create_obj")
			{
				VarStack.push_back(createObj(entryPoint->Sequence[i]));
				i++;
				continue;
			}
			if (entryPoint->Sequence[i] == "$create_obj")
			{
				VarStack.push_back(createObj(entryPoint->Sequence[i - 1]));
				continue;
			}
			VarStack.push_back(getVariable(entryPoint->Sequence[i], Obj, entryPoint));
		}
	
	}



};