#include "TableMaker.h"
#include "Executor.h"
#include "Interpreter.h"
#include<windows.h>

int main()
{
	int comand;
	TableMaker* myTableMaker;

	Recognizer* myRecognizer;
	Scanner* myScanner;
	Builder* myBuilder;

	Interpreter* myInterpreter;

	Executor* myExecutor;
	
	SetConsoleOutputCP(1251);
	while (true)
	{
		cout << "1. Make Preceded Table " << endl;
		cout << "2. Build programm " << endl;
		cout << "0. Exit programm " << endl;
		cin >> comand;
		switch (comand)
		{
		case 1:
		{
				  myTableMaker = new TableMaker();
				  myTableMaker->createPrecededTable();
				  myTableMaker->writePrecededTable();
				  break;
		}
		case 2:
		{

				  myScanner = new Scanner();
				  myRecognizer = new Recognizer();	
				  myBuilder = new Builder();

				  myInterpreter = new Interpreter(myScanner, myRecognizer, myBuilder);
				  myInterpreter->work();

				  myExecutor = new Executor(&myBuilder->Classes);
				  myExecutor->RunProgramm(myBuilder->mainObj->getContext(),
					  &myBuilder->mainObj->ClassBehavior, myBuilder->entryPoint);
				  break;
		}
		case 0:
		{
				  cout << "BB!" << endl;;
				  return 0;
		}
		default:
			break;
		}
	}
	return 1;
}