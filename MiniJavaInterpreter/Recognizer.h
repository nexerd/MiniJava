#pragma once
#include "Lexem.h"
#include "Rule.h"



// Метод заменяющий в правилах все нетерм. символы на "S"
vector<rule> refreshRules(vector<rule>& P, vector<string>& VN)
{
	vector<rule> newP = P;
	// Просто для красоты
	//P.front().left = "S";

	for (int i = 0; i < P.size(); i++)
	{
		// Замена левой части правила
		newP[i].left = "S";
		// Замена нетрем. символов в парвой части правила
		for (int j = 0; j < newP[i].right.size(); j++)
		if (isFrom(newP[i].right[j], VN))
			newP[i].right[j] = "S";
	}
	VN.front() = "S";
	return newP;
}

// Функция сравнения правой части правила с цепочкой
bool compareRules(rule& P, vector<string>& str)
{
	if (P.right.size() != str.size())
		return false;
	for (int i = 0; i < str.size(); i++)
	if (P.right[i] != str[i])
		return false;
	return true;
}

// Функция свертки
void Convolution(vector<string>& myStack, vector<rule>& P, vector<string>& VT, int TermHeadOfStak,
	vector<vector<precedenceRelation>> precedenceTable, vector<int>& numRules)
{
	int left = TermHeadOfStak - 1, right = TermHeadOfStak, pos1, pos2 = whatPosition(myStack[right], VT);

	// Посик символов составляющих освнову
	while (left > 0)
	{
		if (isFrom(myStack[left], VT))
		{
			// Если этом темр. символ то проверяем отношение предшествоания
			pos1 = whatPosition(myStack[left], VT);
			// Составляем основу для  терм.символов с отношением =*
			if (precedenceTable[pos1][pos2] == basic)
			{
				right = left;
				pos2 = pos1;
				--left;
			}
			else
				break;

		}
		else
			// Нетерм. символы пропускаем
			--left;
	}

	vector<string> buffer(myStack.begin() + 1 + left, myStack.end());

	// Подбираем правило
	for (int i = 0; i < P.size(); i++)
	if (compareRules(P[i], buffer))
	{
		// Удаляем основу из стека
		myStack.erase(myStack.begin() + left + 1, myStack.end());
		// Пишем в стек леву часть правила - заменили основу
		myStack.push_back(P[i].left);
		// Записываем номер правила
		numRules.push_back(i + 1);
		return;
	}

	// Если неудалось подобрать правила, то ошибка
	throw exception("Not a rule for this basic!");
}

struct  Recognizer
{
	string VTFile, VNFile, RuleFile, TablePrecededFile;

	//Стэк
	vector<string> myStack;

	// Мн-во терм символов.
	vector<string> VT;
	// Мн-во нетерм. симоволов
	vector<string> VN;
	// Мно-ва правли грамматики
	vector<rule> P;
	
	// Таблица предшествования
	vector<vector<precedenceRelation>> precedenceTable;

	int TermHeadOfStak, pos1, pos2;

	// Считывание из файла мн-в символов
	void readSymbols(string file, vector<string>& V);

	void readRule();

	void readPrecededTable();

	bool Recognize(lexem l);

	Recognizer();

	bool RecognizeLexems(vector<lexem> programm);
};


Recognizer::Recognizer()
{
	VTFile = "VTFile.txt";
	VNFile = "VNFile.txt";
	RuleFile = "RuleFile.txt";
	TablePrecededFile = "TablePrecededFile.txt";

	myStack.push_back("$b");
	TermHeadOfStak = 0;

	readSymbols(VTFile, VT);
	VT.push_back("$b");
	VT.push_back("$e");
	readSymbols(VNFile, VN);
	readRule();
	P = refreshRules(P, VN);
	readPrecededTable();
}

void  Recognizer::readSymbols(string file, vector<string>& V)
{
	ifstream fin(file);
	string buf;
	if (!fin.is_open())
		throw exception("File is not open!");
	while (!fin.eof())
	{
		fin >> buf;
		if (buf != " " && buf != "")
		V.push_back(buf);
	}
	fin.close();
}

void Recognizer::readRule()
{
	ifstream fin(RuleFile);
	string buf;
	int size;
	if (!fin.is_open())
		throw exception("File is not open!");
	while (!fin.eof())
	{
		P.push_back(rule());
		fin >> P.back().left;
		fin >> size;	
		if (size == -1 || P.back().left == " " || P.back().left == "")
		{			
			P.pop_back();
			break;
		}
		P.back().right.reserve(size);
		while (size-- != 0)
		{
			fin >> buf;
			P.back().right.push_back(buf);
		}
	}
	fin.close();
}

void Recognizer::readPrecededTable()
{
	ifstream fin(TablePrecededFile);
	char buf;
	int size;
	if (!fin.is_open())
		throw exception("File is not read!");
	fin >> size;
	precedenceTable = vector<vector<precedenceRelation>>(size, vector<precedenceRelation>(size, empty));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fin >> buf;
			switch (buf)
			{
			case ('-') :
			{
						   precedenceTable[i][j] = empty;
						   break;
			}
			case ('=') :
			{
						   precedenceTable[i][j] = basic;
						   break;
			}
			case ('<') :
			{
						   precedenceTable[i][j] = preceded;
						   break;
			}
			case ('>') :
			{
						   precedenceTable[i][j] = follow;
						   break;
			}
			default:
				throw exception("Error in table precede file!");
				break;
			}
		}
	}
	fin.close();
}

// Распознание цепочки
bool Recognizer::Recognize(lexem l)
{	
	// Номера правил
	vector<int> numRules;

	string c = l.str_type;
	
	pos1 = whatPosition(myStack[TermHeadOfStak], VT);
	// Распознание цепочки

	// Если нетерм. символ то сразу переносим в стек.
	if (isFrom(c, VN))
		myStack.push_back(c);
	else
	{
		if (isFrom(c, VT))
		{
			// Если терминальный символ, то смотрим его позицию для сравнения по таблице предшествования
			// С верхушкой стека.
			pos2 = whatPosition(c, VT);

			switch (precedenceTable[pos1][pos2])
			{
			case (empty) :
			{
							 // Если клетка в таблице пуста, то ошибка - недопустимая комбинация.
							 throw exception("Empry cell of preceded table!");
							 break;
			}
			case (preceded) :
			{
								// Если отношение предшестваоания <* - то пишем в стек и перемещаем 
								// адрес первого темр. символа в стеке.
								// Сдвиг
								myStack.push_back(c);
								pos1 = pos2;
								TermHeadOfStak = myStack.size() - 1;
								break;
			}
			case (basic) :
			{
							 // Если отношение основы =* - то пишем в стек и перемещаем 
							 // адрес первого темр. символа в стеке.
							 // Сдвиг
							 myStack.push_back(c);
							 pos1 = pos2;
							 TermHeadOfStak = myStack.size() - 1;
							 break;
			}
			case (follow) :
			{
							  // Если отношение следует *> - то свертка
							  Convolution(myStack, P, VT, TermHeadOfStak, precedenceTable, numRules);
							  // Иещм к последний темр. символ
							  TermHeadOfStak = myStack.size() - 1;
							  while (!isFrom(myStack[TermHeadOfStak], VT))
							  {
								  --TermHeadOfStak;
							  }
							  pos1 = whatPosition(myStack[TermHeadOfStak], VT);
							  return false;
			}
			default:
				break;
			}
		}
		return true;
	}
	for (int j = 0; j < myStack.size(); j++)
		cout << myStack[j] << " ";
	cout << endl;
}

bool Recognizer::RecognizeLexems(vector<lexem> programm)
{
	programm.push_back(lexem("$e", _$e));
	for (int i = 0; i < programm.size(); i++)
	{
		while ((!Recognize(programm[i])));
			
		for (int j = 0; j < myStack.size(); j++)
			cout << myStack[j] << " ";
		cout << endl;
	}
	return true;
}