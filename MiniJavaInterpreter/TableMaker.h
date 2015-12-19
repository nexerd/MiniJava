#pragma once
#include "Rule.h"


// Фунция сравнения массива предыдущих размеров, с текущими. Если хотябы один не совпдает, то продолжение.
bool isEnd(vector<int>& last_size, vector<vector<string>>& a)
{
	for (int i = 0; i < a.size(); i++)
	if (last_size[i] != a[i].size())
		return false;
	return true;
}

// Функция увелечения мн-ва крайних неткрм. символов
void makeSetExtremCharacters(vector<vector<string>>& A, vector<string>& VN)
{
	int position;
	vector<string> buffer_to_add;
	// Для каждого множества (каждого нетерм. символа)
	for (int i = 0; i < A.size(); i++)
	{
		// Для каждого нетерм. символа в нем
		for (int j = 0; j < A[i].size(); j++)
		{
			buffer_to_add.clear();
			// Находим номер текущего нетермю символа
			position = whatPosition(A[i][j], VN);
			if (position < A.size())
			{
				// ИЗ множества крайних символов для символа в наиденой позиции
				// запишем все символы в исходное множество, исключая повторения
				for (int k = 0; k < A[position].size(); k++)
				{
					// Формирование массива символов
					if (!isFrom(A[position][k], A[i]))
						buffer_to_add.push_back(A[position][k]);
				}
			}
			// Дозапись в множество
			A[i].insert(A[i].end(), buffer_to_add.begin(), buffer_to_add.end());
		}

	}
}

// Функция формирования мн-в крайних терм. символов
void makeSetExtremTerminalCharacters(vector<vector<string>>& A, vector<vector<string>>& At, vector<string>& VN)
{
	int position;
	vector<string> buffer_to_add;
	// Для каждого нетрем. симвлоа
	for (int i = 0; i < A.size(); i++)
	{
		// Для всех нетрем. симвлово лежащих в его мно-ве крайних символов
		for (int j = 0; j < A[i].size(); j++)
		{
			buffer_to_add.clear();
			// Находим номер текущего нетермю символа
			position = whatPosition(A[i][j], VN);
			if (position < A.size())
			{
				// Дописываем все терм. символовы из его мн-ва крайних терм. симовло, исключая повторения
				for (int k = 0; k < At[position].size(); k++)
				{
					// формирования буфера
					if (!isFrom(At[position][k], At[i]))
						buffer_to_add.push_back(At[position][k]);
				}
			}
			// Запись трем. символов
			At[i].insert(At[i].end(), buffer_to_add.begin(), buffer_to_add.end());
		}
	}
}

//  Функция записи табицы
void writeTable(int position1, int position2, precedenceRelation value,
	vector<vector<precedenceRelation>>& precedenceTable, vector<string>& VT, rule r)
{
	// Если таблица по указаному адрему пустая, то запись значения
	// или совпадает  с записываемым значением.
	cout << r.left << " ";
	for (int i = 0; i < r.right.size(); i++)
		cout << r.right[i] << " ";
	cout << " : " << VT[position1] << " " << value << " " << VT[position2] << endl;
	if (precedenceTable[position1][position2] == empty || precedenceTable[position1][position2] == value)
	{
		precedenceTable[position1][position2] = value;
	}
	else
		// Иначе, ошибка. Неоднозначность отношения двух терм символов.
	{
		//cout << "Error!!!!";
		throw exception("This is not operators precendence gramma! Double prcedence in table!");
	}
}


//структура для формирования табилцы
struct TableMaker
{
	// Путик к фалам грамматики
	string VTFile, VNFile, RuleFile, TablePrecededFile;
	
	// Мн-во терм символов.
	vector<string> VT;
	// Мн-во нетерм. симоволов
	vector<string> VN;
	// Мно-ва правли грамматики
	vector<rule> P;

	// Таблица предшествования
	vector<vector<precedenceRelation>> precedenceTable;

	// Считывание из файла мн-в символов
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

	// Предыдущие рарзмеры множества L, R. Для проверки изменения мн-в.
	vector<int> last_size_L(size_VN, -1);
	vector<int> last_size_R(size_VN, -1);


	// Формируем множество крайних левых и правых символов
	// Формирование L0 и R0
	vector<rule>::iterator current_Rule;
	for (int i = 0; i < size_VN; i++)
	{
		// Ищем первое правило содержащие в левой части текущий нетрем. символ
		current_Rule = find(P.begin(), P.end(), VN[i]);
		while (current_Rule != P.end())
		{
			// L0
			if (!isFrom(current_Rule->right.front(), L[i]))
				L[i].push_back(current_Rule->right.front());
			// R0
			if (!isFrom(current_Rule->right.back(), R[i]))
				R[i].push_back(current_Rule->right.back());
			// Переход к следующему правилу содержащему в левой части текущий нетерм. символ
			current_Rule = find(current_Rule + 1, P.end(), VN[i]);
		}
	}

	// Формирование L и R - множеств (крайних левых, правых символов)
	// Пока размер множества крайних символо хотябы для одного нетрем. символа меняется
	while (!isEnd(last_size_L, L) || !isEnd(last_size_R, R))
	{
		// Запоминаем текущие размеры для последующего сравнения
		for (int i = 0; i < size_VN; i++)
		{
			last_size_L[i] = L[i].size();
			last_size_R[i] = R[i].size();
		}
		// Наращиваем мн-во L
		makeSetExtremCharacters(L, VN);
		// Наращиваем мн-во R
		makeSetExtremCharacters(R, VN);
	}

	// Формирование множеств крайних левых и правых терминальных символов
	vector<vector<string>> Lt(size_VN, vector<string>());
	vector<vector<string>> Rt(size_VN, vector<string>());

	// Формирование Lt0 и Rt0
	// Для каждоо нетерминального символа
	for (int i = 0; i < size_VN; i++)
	{
		// Выбираем правила, где он слева
		current_Rule = find(P.begin(), P.end(), VN[i]);
		while (current_Rule != P.end())
		{
			// Ищем крйние левые терминальные символы в правой части правила
			for (int j = 0; j < current_Rule->right.size(); j++)
			{
				// Записываем, исключая повторяющиеся
				if (isFrom(current_Rule->right[j], VT))
				{
					if (!isFrom(current_Rule->right[j], Lt[i]))
						Lt[i].push_back(current_Rule->right[j]);
					break;
				}
			}
			// Ищем крйние правые терминальные символы в правой части правила
			for (int j = current_Rule->right.size() - 1; j >= 0; j--)
			{
				// Записываем, исключая повторяющиеся
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

	// Предыдущие рарзмеры множества Lt, Rt. Для проверки изменения мн-в.
	vector<int> last_size_Lt(size_VN, -1);
	vector<int> last_size_Rt(size_VN, -1);

	// Формирование мн-в Lt, Rt - крайних терм. симоволов
	// Пока размер множества крайних символо хотябы для одного нетрем. символа меняется
	while (!isEnd(last_size_Lt, Lt) || !isEnd(last_size_Rt, Rt))
	{
		// Записываем текущие размеры
		for (int i = 0; i < size_VN; i++)
		{
			last_size_Lt[i] = Lt[i].size();
			last_size_Rt[i] = Rt[i].size();
		}
		// Дополняем Lt
		makeSetExtremTerminalCharacters(L, Lt, VN);
		// Дополняем Rt
		makeSetExtremTerminalCharacters(R, Rt, VN);
	}

	// Построение таблици предшествования
	precedenceTable = vector<vector<precedenceRelation>>(size_VT + 2, vector<precedenceRelation>(size_VT + 2, empty));

	string char1, char2, char3;
	int pos1, pos2, pos3;
	try{
		// В каждом правиле
		for (int i = 0; i < size_Rules; i++)
		{
			for (int j = 0; j < P[i].right.size() - 1; j++)
			{
				char1 = P[i].right[j];
				char2 = P[i].right[j + 1];
				// Если, это два не последних символа то берем третий.
				if (j < P[i].right.size() - 2)
				{
					char3 = P[i].right[j + 2];
					pos3 = whatPosition(char3, VT);
				}
				else
					pos3 = size_VT;

				// Находим номера терм. символов
				pos1 = whatPosition(char1, VT);
				pos2 = whatPosition(char2, VT);
				// Для не терм. символо позиция равна размеру мн-ва терм. символов
				if (pos1 != size_VT)
				{
					// Если первый сивлов терминальный
					if (pos2 != size_VT)
					{
						// Если второй символ терминальный, запимеш в таблицу =*
						writeTable(pos1, pos2, basic, precedenceTable, VT, P[i]);
					}
					else
					{
						// Если второй нетерм
						// Определим его позиию в мн-ве нетерм символов
						pos2 = whatPosition(char2, VN);
						//  Для все его символов ил Lt - крайних левых нетерм
						for (int k = 0; k < Lt[pos2].size(); k++)
						{
							// Записываем в табилцу <*
							writeTable(pos1, whatPosition(Lt[pos2][k], VT), preceded, precedenceTable, VT, P[i]);
						}
						if (pos3 != size_VT)
						{
							// Если третий символ терминальный:  ...aBc... , то a =* c
							// Записываем  в таблицу =*
							writeTable(pos1, pos3, basic, precedenceTable, VT, P[i]);
						}
					}
				}
				else
				{
					// Если первый символ нетерминальный
					if (pos2 != size_VT)
					{
						// Если второй символ терминальный
						// Определи позицию первог в мн-во нетерминальных
						pos1 = whatPosition(char1, VN);
						// Для каждого терм. символа из мн-ва его крайних правы терм. символов - Rt
						for (int k = 0; k < Rt[pos1].size(); k++)
						{
							// Запишем в таблицу *>
							writeTable(whatPosition(Rt[pos1][k], VT), pos2, follow, precedenceTable, VT, P[i]);
						}
					}
					else
						// Два соседних нетерминальных символа: ...AB... - ошибка
						throw exception("Two not terminal symbols near.");
				}
			}
		}
	}
	catch (exception ex)
	{
		// Если произлаша, в процессе формирования табилци
		// Или два соседних нетерм. симвлоа
		// Или попытка записть, в заполненую уже клетку табилцы
		// Значит грамматика не подходит для метода операторного предшествования
		cout << ex.what() << endl;
		throw exception(ex);
	}

	// Допишем в мн-во терм. символов символы начала и концы программы
	// Символ начала цепочки
	VT.push_back("$b");
	// Символ конца цепочки
	VT.push_back("$e");
	size_VT += 2;
	// Для всех терм. символ из мн-ва крайних левых символов НАЧАНОГО символа грамматики
	for (int i = 0; i < Lt[0].size(); i++)
	{
		// Записываем для начального символа и текущего темр. символа <*
		writeTable(VT.size() - 2, whatPosition(Lt[0][i], VT), preceded, precedenceTable, VT, P[i]);
	}
	// Для всех терм. символ из мн-ва крайних  символов НАЧАНОГО символа грамматики
	for (int i = 0; i < Rt[0].size(); i++)
	{
		// Записываем для начального символа и текущего темр. символа *>
		writeTable(whatPosition(Rt[0][i], VT), VT.size() - 1, follow, precedenceTable, VT, P[i]);
	}

	// Отношение между знаком конца и знаком начала
	writeTable(VT.size() - 2, VT.size() - 1, basic, precedenceTable, VT, P[0]);

}