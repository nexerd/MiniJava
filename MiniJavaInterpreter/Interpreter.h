#include "Scanner.h"
#include "Recognizer.h"
#include "Builder.h"

struct Interpreter
{
	Scanner* myScanner;
	Recognizer* myRecognizer;
	Builder* myBuilder;

	string ProgrammFile;

	vector<lexem> ListOfConvulsion;
	int ruleNumber;

	Interpreter(Scanner* s, Recognizer* r, Builder* b)
	{
		myScanner = s;
		myRecognizer = r;
		myBuilder = b;
		ProgrammFile = "ProgrammFile.txt";
	}

	void CorrectTypeLexem(lexem& l, vector<MyClass>& classes)
	{
		if (l.str_type == "identifier")
		{
			if (myBuilder->curClass != NULL && myBuilder->curClass->name == l.str)
			{
				l.str_type = "type";
				return;
			}
			for (int i = 0; i < classes.size(); i++)
			if (classes[i].name == l.str)
			{
				l.str_type = "type";
				return;
			}
		}
	}

	void work()
	{
		string str;
		ifstream fin(ProgrammFile);
		lexem l;
		try
		{
			while (!fin.eof())
			{
				getline(fin, str);
				str += '\n';
				//cout << str << endl;
				for (int i = 0; i < str.size(); i++)
				if (myScanner->Scan(str[i], i, str.size(), &l))
				{
					CorrectTypeLexem(l, myBuilder->Classes);
					while (!myRecognizer->RecognizeLexems(l, ListOfConvulsion, ruleNumber))
					{
						myBuilder->makePart(ListOfConvulsion, ruleNumber);
					}
				}
			}
			fin.close();
			myScanner->check();
			while (!myRecognizer->RecognizeLexems(lexem("$e", _$e), ListOfConvulsion, ruleNumber))
			{
				myBuilder->makePart(ListOfConvulsion, ruleNumber);
			}
		}
		catch (lexical_exception& ex)
		{
			for (int i = 0; i < ex.position; i++)
				cout << '.';
			cout << "^" << endl;
			cout << "Lexical error!" << endl;
			cout << ex.what() << endl;
		}
		
	}
};