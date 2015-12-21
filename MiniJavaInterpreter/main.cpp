#include "TableMaker.h"
#include "Recognizer.h"
#include "Scanner.h"
#include "Builder.h"
#include "Executor.h"
#include<windows.h>

int main()
{
	int comand;
	TableMaker* myTableMaker;
	Recognizer* myRecognizer;
	Scanner* myScanner;
	Builder* myBuilder;
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
				  myScanner->work();
				  myRecognizer = new Recognizer();	
				  myRecognizer->RecognizeLexems(myScanner->lexemes);
				  myBuilder = new Builder();
				  myBuilder->makeProgramm(myRecognizer->ListOfConvulsion, myRecognizer->numRules);
				  myExecutor = new Executor(myBuilder->Classes);
				  myExecutor->RunProgramm(myBuilder->entryPoint);
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