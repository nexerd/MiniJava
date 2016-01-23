#include "TableMaker.h"
#include "Executor.h"
#include "Interpreter.h"
#include<windows.h>

int main()
{
	int comand;
	TableMaker* myTableMaker = NULL;

	Recognizer* myRecognizer = NULL;
	Scanner* myScanner = NULL;
	Builder* myBuilder = NULL;

	Interpreter* myInterpreter = NULL;

	Executor* myExecutor = NULL;

	bool is_interpreted = false;
	
	SetConsoleOutputCP(1251);
	while (true)
	{
		cout << "1. Make Preceded Table " << endl;
		cout << "2. Interpret programm " << endl;
		cout << "3. Run programm " << endl;
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
				  try
				  {
					  myInterpreter = new Interpreter(myScanner, myRecognizer, myBuilder);
					  myInterpreter->work();
				  }
				  catch (lexical_exception& ex)
				  {
					  for (int i = 0; i < ex.position; i++)
						  cout << '.';
					  cout << "^" << endl;
					  cout << "Lexical error!" << endl;
					  cout << ex.what() << endl << endl;
					  break;
				  }
				  catch (syntax_exception& ex)
				  {
					  cout << "Syntax error!" << endl;
					  cout << ex.what() << endl << endl;
					  break;
				  }
				  is_interpreted = true;
				  cout << "Interpreting success!" << endl << endl;
				  break;
		}
		case 3:
		{
				  if (is_interpreted)
				  {
					  cout << "\nRun programm!" << endl << endl;
					  try
					  {
						  myExecutor = new Executor(&myBuilder->Classes);

						  myExecutor->RunProgramm(myBuilder->mainObj->getContext(),
							  &myBuilder->mainObj->ClassBehavior, myBuilder->entryPoint);
					  }
					  catch (execute_exception& ex)
					  {
						  cout << "Execute error!" << endl;
						  cout << ex.what() << endl << endl;
						  break;
					  }
					  cout << "\nEnd programm!" << endl << endl;
				  }
				  else
					  cout << "Programm is not interpreted!" << endl << endl;
				  break;
		}
		case 0:
		{
				  cout << "BB!" << endl;
				  return 0;
		}
		default:
			break;
		}
	}
	return 1;
}