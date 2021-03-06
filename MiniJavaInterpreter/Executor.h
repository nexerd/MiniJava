#pragma once
#include "Class.h"

struct Executor
{
	vector<MyClass>* myClasses;

	Executor(vector<MyClass>* Classes)
	{
		myClasses = Classes;		
	}

	Variable* getClassVariable(string& name, string& second_name)
	{
		Variable* A;
		for (int i = 0; i < myClasses->size(); i++)
		{
			if ((*myClasses)[i].name == name && (*myClasses)[i].is_static)
			{
				if ((*myClasses)[i].ClassContext.getVariable(second_name, &A))
					return A;
			}
		}
		return NULL;
	}

	bool getClassNext(string& name, string& fun_name, Context** nextC, Behavior** nextB)
	{
		Function* f = NULL;
		for (int i = 0; i < myClasses->size(); i++)
		{
			if ((*myClasses)[i].name == name && (*myClasses)[i].is_static)
			{
				if ((*myClasses)[i].ClassBehavior.getFunction(fun_name, &f))
				{
					*nextC = &(*myClasses)[i].ClassContext;
					*nextB = &(*myClasses)[i].ClassBehavior;
					return true;
				}
					
			}
		}
		return false;
	}

	Variable* getVariable(string& name, Context* curConext, Function* entryPoint)
	{
		Variable* A = NULL;
		if (!entryPoint->CurContext.getVariable(name, &A))
		{
			if (!entryPoint->Parametrs.getVariable(name, &A))
			{
				curConext->getVariable(name, &A);					
			}
		}
		if (A == NULL)
			throw execute_exception("Undefine variable or function!");
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
		throw execute_exception("Undefine class name!");
	}

	void RunProgramm(Context* curConext, Behavior* curBehavior, Function* entryPoint)
	{				
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
				VarStack.push_back(*B != A);
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
				if (entryPoint->Sequence[i + 1] == "NULL")
				{
					type = "NULL";
					VarStack.push_back(new Variable(type,
						Value((Object*)NULL)));
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
				if (entryPoint->Sequence[i - 1] == "NULL")
				{
					type = "NULL";
					VarStack.push_back(new Variable(type,
						Value((Object*)NULL)));
				}
				//i += 2;
				continue;
			}
			if (entryPoint->Sequence[i] == "$function")
			{
				Function* nextFun;
				
				string nameF = entryPoint->Sequence[i + 2];

				Context* nextConext;
				Behavior* nextBehavior;
				
				if (!getClassNext(entryPoint->Sequence[i + 3], entryPoint->Sequence[i + 2], &nextConext, &nextBehavior))
				{
					VarStack.push_back(getVariable(entryPoint->Sequence[i + 3], curConext, entryPoint));
					Object* ObjF;
					ObjF = VarStack.back()->value.Obj;
					ObjF->objBehavior->getFunction(nameF, &nextFun);
					VarStack.pop_back();

					nextConext = &(ObjF->objContext);
					nextBehavior = ObjF->objBehavior;
				}
				else 
					nextBehavior->getFunction(nameF, &nextFun);
				
				
				int countParams = atoi(entryPoint->Sequence[i + 1].c_str());
				for (int j = 0; j < countParams; j++)
				{
					nextFun->Parametrs.VarList[j] = VarStack.back();
					VarStack.pop_back();
				}
				RunProgramm(nextConext, nextBehavior, nextFun);
				if (nextFun->returnValue.type != "void" && !nextFun->is_returned)
					throw execute_exception("Function '" + nextFun->name + "' must retund value!");
				if (nextFun->returnValue.type != "void")
					VarStack.push_back(&nextFun->returnValue);
				i += 3;
				continue;
			}

			if (entryPoint->Sequence[i] == "$own_function")
			{
				Function* nextFun;
				string nameF = entryPoint->Sequence[i + 2];
				curBehavior->getFunction(nameF, &nextFun);				
				
				int countParams = atoi(entryPoint->Sequence[i + 1].c_str());
				for (int j = 0; j < countParams; j++)
				{
					nextFun->Parametrs.VarList[j] = VarStack.back();
					VarStack.pop_back();
				}
				RunProgramm(curConext, curBehavior, nextFun);
				if (nextFun->returnValue.type != "void" && !nextFun->is_returned)
					throw execute_exception("Function '" + nextFun->name + "' must retund value!");
				if (nextFun->returnValue.type != "void")
					VarStack.push_back(&nextFun->returnValue);
				i += 2;
				continue;
			}


			if (entryPoint->Sequence[i] == ".")
			{

				A = getClassVariable(entryPoint->Sequence[i + 1], entryPoint->Sequence[i + 2]);
				if (A == NULL)
				
				{
					VarStack.push_back(getVariable(entryPoint->Sequence[i + 1], curConext, entryPoint));
					VarStack.back()->value.Obj->objContext.getVariable(entryPoint->Sequence[i + 2], &A);
					VarStack.pop_back();
				}			
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
					entryPoint->is_returned = true;
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
			VarStack.push_back(getVariable(entryPoint->Sequence[i], curConext, entryPoint));
		}
	
	}



};