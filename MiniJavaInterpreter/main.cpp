#include "TableMaker.h"
#include "Recognizer.h"
#include "Scanner.h"

int main()
{
	int comand;
	TableMaker* myTableMaker;
	Recognizer* myRecognizer;
	Scanner* myScanner;
	while (true)
	{
		cout << "1. Make Preceded Table " << endl;
		cout << "2. Recognize programm " << endl;
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