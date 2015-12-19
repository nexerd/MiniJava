#pragma once
#include "Rule.h"


// ������ ��������� ������� ���������� ��������, � ��������. ���� ������ ���� �� ��������, �� �����������.
bool isEnd(vector<int>& last_size, vector<vector<string>>& a)
{
	for (int i = 0; i < a.size(); i++)
	if (last_size[i] != a[i].size())
		return false;
	return true;
}

// ������� ���������� ��-�� ������� ������. ��������
void makeSetExtremCharacters(vector<vector<string>>& A, vector<string>& VN)
{
	int position;
	vector<string> buffer_to_add;
	// ��� ������� ��������� (������� ������. �������)
	for (int i = 0; i < A.size(); i++)
	{
		// ��� ������� ������. ������� � ���
		for (int j = 0; j < A[i].size(); j++)
		{
			buffer_to_add.clear();
			// ������� ����� �������� ������� �������
			position = whatPosition(A[i][j], VN);
			if (position < A.size())
			{
				// �� ��������� ������� �������� ��� ������� � �������� �������
				// ������� ��� ������� � �������� ���������, �������� ����������
				for (int k = 0; k < A[position].size(); k++)
				{
					// ������������ ������� ��������
					if (!isFrom(A[position][k], A[i]))
						buffer_to_add.push_back(A[position][k]);
				}
			}
			// �������� � ���������
			A[i].insert(A[i].end(), buffer_to_add.begin(), buffer_to_add.end());
		}

	}
}

// ������� ������������ ��-� ������� ����. ��������
void makeSetExtremTerminalCharacters(vector<vector<string>>& A, vector<vector<string>>& At, vector<string>& VN)
{
	int position;
	vector<string> buffer_to_add;
	// ��� ������� ������. �������
	for (int i = 0; i < A.size(); i++)
	{
		// ��� ���� ������. �������� ������� � ��� ���-�� ������� ��������
		for (int j = 0; j < A[i].size(); j++)
		{
			buffer_to_add.clear();
			// ������� ����� �������� ������� �������
			position = whatPosition(A[i][j], VN);
			if (position < A.size())
			{
				// ���������� ��� ����. ��������� �� ��� ��-�� ������� ����. �������, �������� ����������
				for (int k = 0; k < At[position].size(); k++)
				{
					// ������������ ������
					if (!isFrom(At[position][k], At[i]))
						buffer_to_add.push_back(At[position][k]);
				}
			}
			// ������ ����. ��������
			At[i].insert(At[i].end(), buffer_to_add.begin(), buffer_to_add.end());
		}
	}
}

//  ������� ������ ������
void writeTable(int position1, int position2, precedenceRelation value,
	vector<vector<precedenceRelation>>& precedenceTable, vector<string>& VT, rule r)
{
	// ���� ������� �� ��������� ������ ������, �� ������ ��������
	// ��� ���������  � ������������ ���������.
	cout << r.left << " ";
	for (int i = 0; i < r.right.size(); i++)
		cout << r.right[i] << " ";
	cout << " : " << VT[position1] << " " << value << " " << VT[position2] << endl;
	if (precedenceTable[position1][position2] == empty || precedenceTable[position1][position2] == value)
	{
		precedenceTable[position1][position2] = value;
	}
	else
		// �����, ������. ��������������� ��������� ���� ���� ��������.
	{
		//cout << "Error!!!!";
		throw exception("This is not operators precendence gramma! Double prcedence in table!");
	}
}


//��������� ��� ������������ �������
struct TableMaker
{
	// ����� � ����� ����������
	string VTFile, VNFile, RuleFile, TablePrecededFile;
	
	// ��-�� ���� ��������.
	vector<string> VT;
	// ��-�� ������. ���������
	vector<string> VN;
	// ���-�� ������ ����������
	vector<rule> P;

	// ������� ���������������
	vector<vector<precedenceRelation>> precedenceTable;

	// ���������� �� ����� ��-� ��������
	void readSymbols(string file, vector<string>& V);

	void readRule();

	void createPrecededTable();

	void writePrecededTable();

	TableMaker();

};

TableMaker::TableMaker()
{
	VTFile = "VTFile.txt";
	VNFile = "VNFile.txt";
	RuleFile = "RuleFile.txt";
	TablePrecededFile = "TablePrecededFile.txt";

	readSymbols(VTFile, VT);
	readSymbols(VNFile, VN);
	readRule();
}

void  TableMaker::readSymbols(string file, vector<string>& V)
{
	ifstream fin(file);
	string buf;
	if (!fin.is_open())
		throw exception("File is not open!");
	while (!fin.eof())
	{
		fin >> buf;
		V.push_back(buf);
	}
	fin.close();
}

void TableMaker::readRule()
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
		if (P.back().left == " " || P.back().left == "")
		{
			P.pop_back();
			break;
		}
		fin >> size;
		P.back().right.reserve(size);
		while (size-- != 0)
		{
			fin >> buf;
			P.back().right.push_back(buf);
		}
	}
	fin.close();
}

void TableMaker::writePrecededTable()
{
	ofstream fout(TablePrecededFile);
	if (!fout.is_open())
		throw exception("File is not open!");
	fout << VT.size() << endl;
/*	for (int i = 0; i < VT.size(); i++)
		fout << VT[i] << " ";*/
	fout << endl;

	for (int i = 0; i < VT.size(); i++)
	{
		for (int j = 0; j < VT.size(); j++)
		switch (precedenceTable[i][j])
		{
			case (empty) :
			{
							 fout << " - ";
							 break;
			}
			case (basic) :
			{
							 fout << " = ";
							 break;
			}
			case (preceded) :
			{
								fout << " < ";
								break;
			}
			case (follow) :
			{
							  fout << " > ";
							  break;
			}
			default:
				break;
		}
		fout << endl;
	}
	fout.close();
}

void TableMaker::createPrecededTable()
{
	int size_VT = VT.size(), size_VN = VN.size(), size_Rules = P.size();

	vector<vector<string>> L(size_VN, vector<string>());
	vector<vector<string>> R(size_VN, vector<string>());

	// ���������� �������� ��������� L, R. ��� �������� ��������� ��-�.
	vector<int> last_size_L(size_VN, -1);
	vector<int> last_size_R(size_VN, -1);


	// ��������� ��������� ������� ����� � ������ ��������
	// ������������ L0 � R0
	vector<rule>::iterator current_Rule;
	for (int i = 0; i < size_VN; i++)
	{
		// ���� ������ ������� ���������� � ����� ����� ������� ������. ������
		current_Rule = find(P.begin(), P.end(), VN[i]);
		while (current_Rule != P.end())
		{
			// L0
			if (!isFrom(current_Rule->right.front(), L[i]))
				L[i].push_back(current_Rule->right.front());
			// R0
			if (!isFrom(current_Rule->right.back(), R[i]))
				R[i].push_back(current_Rule->right.back());
			// ������� � ���������� ������� ����������� � ����� ����� ������� ������. ������
			current_Rule = find(current_Rule + 1, P.end(), VN[i]);
		}
	}

	// ������������ L � R - �������� (������� �����, ������ ��������)
	// ���� ������ ��������� ������� ������� ������ ��� ������ ������. ������� ��������
	while (!isEnd(last_size_L, L) || !isEnd(last_size_R, R))
	{
		// ���������� ������� ������� ��� ������������ ���������
		for (int i = 0; i < size_VN; i++)
		{
			last_size_L[i] = L[i].size();
			last_size_R[i] = R[i].size();
		}
		// ���������� ��-�� L
		makeSetExtremCharacters(L, VN);
		// ���������� ��-�� R
		makeSetExtremCharacters(R, VN);
	}

	// ������������ �������� ������� ����� � ������ ������������ ��������
	vector<vector<string>> Lt(size_VN, vector<string>());
	vector<vector<string>> Rt(size_VN, vector<string>());

	// ������������ Lt0 � Rt0
	// ��� ������ ��������������� �������
	for (int i = 0; i < size_VN; i++)
	{
		// �������� �������, ��� �� �����
		current_Rule = find(P.begin(), P.end(), VN[i]);
		while (current_Rule != P.end())
		{
			// ���� ������ ����� ������������ ������� � ������ ����� �������
			for (int j = 0; j < current_Rule->right.size(); j++)
			{
				// ����������, �������� �������������
				if (isFrom(current_Rule->right[j], VT))
				{
					if (!isFrom(current_Rule->right[j], Lt[i]))
						Lt[i].push_back(current_Rule->right[j]);
					break;
				}
			}
			// ���� ������ ������ ������������ ������� � ������ ����� �������
			for (int j = current_Rule->right.size() - 1; j >= 0; j--)
			{
				// ����������, �������� �������������
				if (isFrom(current_Rule->right[j], VT))
				{
					if (!isFrom(current_Rule->right[j], Rt[i]))
						Rt[i].push_back(current_Rule->right[j]);
					break;
				}
			}
			current_Rule = find(current_Rule + 1, P.end(), VN[i]);
		}
	}

	// ���������� �������� ��������� Lt, Rt. ��� �������� ��������� ��-�.
	vector<int> last_size_Lt(size_VN, -1);
	vector<int> last_size_Rt(size_VN, -1);

	// ������������ ��-� Lt, Rt - ������� ����. ���������
	// ���� ������ ��������� ������� ������� ������ ��� ������ ������. ������� ��������
	while (!isEnd(last_size_Lt, Lt) || !isEnd(last_size_Rt, Rt))
	{
		// ���������� ������� �������
		for (int i = 0; i < size_VN; i++)
		{
			last_size_Lt[i] = Lt[i].size();
			last_size_Rt[i] = Rt[i].size();
		}
		// ��������� Lt
		makeSetExtremTerminalCharacters(L, Lt, VN);
		// ��������� Rt
		makeSetExtremTerminalCharacters(R, Rt, VN);
	}

	// ���������� ������� ���������������
	precedenceTable = vector<vector<precedenceRelation>>(size_VT + 2, vector<precedenceRelation>(size_VT + 2, empty));

	string char1, char2, char3;
	int pos1, pos2, pos3;
	try{
		// � ������ �������
		for (int i = 0; i < size_Rules; i++)
		{
			for (int j = 0; j < P[i].right.size() - 1; j++)
			{
				char1 = P[i].right[j];
				char2 = P[i].right[j + 1];
				// ����, ��� ��� �� ��������� ������� �� ����� ������.
				if (j < P[i].right.size() - 2)
				{
					char3 = P[i].right[j + 2];
					pos3 = whatPosition(char3, VT);
				}
				else
					pos3 = size_VT;

				// ������� ������ ����. ��������
				pos1 = whatPosition(char1, VT);
				pos2 = whatPosition(char2, VT);
				// ��� �� ����. ������� ������� ����� ������� ��-�� ����. ��������
				if (pos1 != size_VT)
				{
					// ���� ������ ������ ������������
					if (pos2 != size_VT)
					{
						// ���� ������ ������ ������������, ������� � ������� =*
						writeTable(pos1, pos2, basic, precedenceTable, VT, P[i]);
					}
					else
					{
						// ���� ������ ������
						// ��������� ��� ������ � ��-�� ������ ��������
						pos2 = whatPosition(char2, VN);
						//  ��� ��� ��� �������� �� Lt - ������� ����� ������
						for (int k = 0; k < Lt[pos2].size(); k++)
						{
							// ���������� � ������� <*
							writeTable(pos1, whatPosition(Lt[pos2][k], VT), preceded, precedenceTable, VT, P[i]);
						}
						if (pos3 != size_VT)
						{
							// ���� ������ ������ ������������:  ...aBc... , �� a =* c
							// ����������  � ������� =*
							writeTable(pos1, pos3, basic, precedenceTable, VT, P[i]);
						}
					}
				}
				else
				{
					// ���� ������ ������ ��������������
					if (pos2 != size_VT)
					{
						// ���� ������ ������ ������������
						// �������� ������� ������ � ��-�� ��������������
						pos1 = whatPosition(char1, VN);
						// ��� ������� ����. ������� �� ��-�� ��� ������� ����� ����. �������� - Rt
						for (int k = 0; k < Rt[pos1].size(); k++)
						{
							// ������� � ������� *>
							writeTable(whatPosition(Rt[pos1][k], VT), pos2, follow, precedenceTable, VT, P[i]);
						}
					}
					else
						// ��� �������� �������������� �������: ...AB... - ������
						throw exception("Two not terminal symbols near.");
				}
			}
		}
	}
	catch (exception ex)
	{
		// ���� ���������, � �������� ������������ �������
		// ��� ��� �������� ������. �������
		// ��� ������� �������, � ���������� ��� ������ �������
		// ������ ���������� �� �������� ��� ������ ������������ ���������������
		cout << ex.what() << endl;
		throw exception(ex);
	}

	// ������� � ��-�� ����. �������� ������� ������ � ����� ���������
	// ������ ������ �������
	VT.push_back("$b");
	// ������ ����� �������
	VT.push_back("$e");
	size_VT += 2;
	// ��� ���� ����. ������ �� ��-�� ������� ����� �������� �������� ������� ����������
	for (int i = 0; i < Lt[0].size(); i++)
	{
		// ���������� ��� ���������� ������� � �������� ����. ������� <*
		writeTable(VT.size() - 2, whatPosition(Lt[0][i], VT), preceded, precedenceTable, VT, P[i]);
	}
	// ��� ���� ����. ������ �� ��-�� �������  �������� �������� ������� ����������
	for (int i = 0; i < Rt[0].size(); i++)
	{
		// ���������� ��� ���������� ������� � �������� ����. ������� *>
		writeTable(whatPosition(Rt[0][i], VT), VT.size() - 1, follow, precedenceTable, VT, P[i]);
	}

	// ��������� ����� ������ ����� � ������ ������
	writeTable(VT.size() - 2, VT.size() - 1, basic, precedenceTable, VT, P[0]);

}