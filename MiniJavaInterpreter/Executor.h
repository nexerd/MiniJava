#include "Class.h"


struct Executor
{
	vector<MyClass> myClasses;
	vector<Function> FunStack;

	Executor(vector<MyClass>& Classes)
	{
		myClasses = Classes;		
	}

	vector<Variable>::iterator getVariable(string& name, Function& entryPoint)
	{
		vector<Variable>::iterator A;
		if (!entryPoint.CurContext.getVariable(name, &A))
		{
			if (!entryPoint.Parametrs.getVariable(name, &A))
				throw exception("Name!");
		}
		return A;
	}

	void RunProgramm(Function& entryPoint)
	{
		FunStack.push_back(entryPoint);
		vector<Variable> VarStack;
		Variable A, B;
		for (int i = 0; i < entryPoint.Sequence.size(); i++)
		{
			if (entryPoint.Sequence[i] == "+")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A + B);
				continue;
			}
			if (entryPoint.Sequence[i] == "-")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A - B);
				continue;
			}
			if (entryPoint.Sequence[i] == "*")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A * B);
				continue;
			}
			if (entryPoint.Sequence[i] == "/")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A / B);
				continue;
			}
			if (entryPoint.Sequence[i] == "%")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A % B);
				continue;
			}
			if (entryPoint.Sequence[i] == "&&")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A && B);
				continue;
			}
			if (entryPoint.Sequence[i] == "||")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A || B);
				continue;
			}
			if (entryPoint.Sequence[i] == "!")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(!A);
				continue;
			}
			if (entryPoint.Sequence[i] == "<")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A < B);
				continue;
			}
			if (entryPoint.Sequence[i] == "==")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A == B);
				continue;
			}
			if (entryPoint.Sequence[i] == ">")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A > B);
				continue;
			}
			if (entryPoint.Sequence[i] == "<=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A < B);
				continue;
			}
			if (entryPoint.Sequence[i] == "!=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A == B);
				continue;
			}
			if (entryPoint.Sequence[i] == ">=")
			{
				A = VarStack.back();
				VarStack.pop_back();
				B = VarStack.back();
				VarStack.pop_back();
				VarStack.push_back(A > B);
				continue;
			}
			
		//	VarStack.insert(VarStack.end(), getVariable(entryPoint.Sequence[i], entryPoint));
		}
	
	}



};