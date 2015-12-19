#pragma once
#include "Lexem.h"
#include "Rule.h"



// ����� ���������� � �������� ��� ������. ������� �� "S"
vector<rule> refreshRules(vector<rule>& P, vector<string>& VN)
{
	vector<rule> newP = P;
	// ������ ��� �������
	//P.front().left = "S";

	for (int i = 0; i < P.size(); i++)
	{
		// ������ ����� ����� �������
		newP[i].left = "S";
		// ������ ������. �������� � ������ ����� �������
		for (int j = 0; j < newP[i].right.size(); j++)
		if (isFrom(newP[i].right[j], VN))
			newP[i].right[j] = "S";
	}
	VN.front() = "S";
	return newP;
}

// ������� ��������� ������ ����� ������� � ��������
bool compareRules(rule& P, vector<lexem>& str)
{
	if (P.right.size() != str.size())
		return false;
	for (int i = 0; i < str.size(); i++)
	if (P.right[i] != str[i].str_type)
		return false;
	return true;
}

// ������� �������
void Convolution(vector<lexem>& myStack, vector<rule>& P, vector<string>& VT, int TermHeadOfStak,
	vector<vector<precedenceRelation>> precedenceTable, vector<int>& numRules)
{
	int left = TermHeadOfStak - 1, right = TermHeadOfStak, pos1, pos2 = whatPosition(myStack[right].str_type, VT);

	// ����� �������� ������������ �������
	while (left > 0)
	{
		if (isFrom(myStack[left].str_type, VT))
		{
			// ���� ���� ����. ������ �� ��������� ��������� ��������������
			pos1 = whatPosition(myStack[left].str_type, VT);
			// ���������� ������ ���  ����.�������� � ���������� =*
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
			// ������. ������� ����������
			--left;
	}

	vector<lexem> buffer(myStack.begin() + 1 + left, myStack.end());

	// ��������� �������
	for (int i = 0; i < P.size(); i++)
	if (compareRules(P[i], buffer))
	{
		// ������� ������ �� �����
		myStack.erase(myStack.begin() + left + 1, myStack.end());
		// ����� � ���� ���� ����� ������� - �������� ������
		myStack.push_back(lexem(P[i].left, _S));
		// ���������� ����� �������
		numRules.push_back(i + 1);
		cout << i + 1 << endl;
		return;
	}

	// ���� ��������� ��������� �������, �� ������
	throw exception("Not a rule for this basic!");
}

struct  Recognizer
{
	string VTFile, VNFile, RuleFile, TablePrecededFile;

	//����
	vector<lexem> myStack;

	// ��-�� ���� ��������.
	vector<string> VT;
	// ��-�� ������. ���������
	vector<string> VN;
	// ���-�� ������ ����������
	vector<rule> P;
	
	// ������� ���������������
	vector<vector<precedenceRelation>> precedenceTable;

	int TermHeadOfStak, pos1, pos2;

	// ���������� �� ����� ��-� ��������
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

	myStack.push_back(lexem("$b", _$b));
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

// ����������� �������
bool Recognizer::Recognize(lexem l)
{	
	// ������ ������
	vector<int> numRules;

	lexem c = l;
	
	pos1 = whatPosition(myStack[TermHeadOfStak].str_type, VT);
	// ����������� �������

	// ���� ������. ������ �� ����� ��������� � ����.
	if (isFrom(c.str_type, VN))
		myStack.push_back(c);
	else
	{
		if (isFrom(c.str_type, VT))
		{
			// ���� ������������ ������, �� ������� ��� ������� ��� ��������� �� ������� ���������������
			// � ��������� �����.
			pos2 = whatPosition(c.str_type, VT);

			switch (precedenceTable[pos1][pos2])
			{
			case (empty) :
			{
							 // ���� ������ � ������� �����, �� ������ - ������������ ����������.
							 throw exception("Empry cell of preceded table!");
							 break;
			}
			case (preceded) :
			{
								// ���� ��������� ��������������� <* - �� ����� � ���� � ���������� 
								// ����� ������� ����. ������� � �����.
								// �����
								myStack.push_back(c);
								pos1 = pos2;
								TermHeadOfStak = myStack.size() - 1;
								break;
			}
			case (basic) :
			{
							 // ���� ��������� ������ =* - �� ����� � ���� � ���������� 
							 // ����� ������� ����. ������� � �����.
							 // �����
							 myStack.push_back(c);
							 pos1 = pos2;
							 TermHeadOfStak = myStack.size() - 1;
							 break;
			}
			case (follow) :
			{
							  // ���� ��������� ������� *> - �� �������
							  Convolution(myStack, P, VT, TermHeadOfStak, precedenceTable, numRules);
							  // ���� � ��������� ����. ������
							  TermHeadOfStak = myStack.size() - 1;
							  while (!isFrom(myStack[TermHeadOfStak].str_type, VT))
							  {
								  --TermHeadOfStak;
							  }
							  pos1 = whatPosition(myStack[TermHeadOfStak].str_type, VT);
							  return false;
			}
			default:
				break;
			}
		}
		return true;
	}
	for (int j = 0; j < myStack.size(); j++)
		cout << myStack[j].str << " ";
	cout << endl;
}

bool Recognizer::RecognizeLexems(vector<lexem> programm)
{
	programm.push_back(lexem("$e", _$e));
	for (int i = 0; i < programm.size(); i++)
	{
		while ((!Recognize(programm[i])))
		{
			for (int j = 0; j < myStack.size(); j++)
				cout << myStack[j].str << " ";
			cout << endl;
		}
		for (int j = 0; j < myStack.size(); j++)
			cout << myStack[j].str << " ";
		cout << endl;
	}
	return true;
}