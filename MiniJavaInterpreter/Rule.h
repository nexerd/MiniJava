#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
// Правило грамматики
struct rule
{
	// Левый не трем. символ
	string left;
	// Правая часть правила
	vector<string> right;
	// Сравнения, для поиска правлиа по известной правй части.
	bool operator==(const string& a);
};

// Сравнения, для поиска правлиа по известной правй части.
bool rule::operator==(const string& a)
{
	return left == a;
}


// Значения, для таблици предшествований
// - , <* , *>, =*
// нет записи, а предшествует б, а следует за б, а и б - основа
enum precedenceRelation { empty = 0, preceded, follow, basic };

// Определение принадлежности массиву
bool isFrom(string& a, vector<string>& A)
{
	return find(A.begin(), A.end(), a) != A.end();
}

// Посик позиции в массиве
int whatPosition(string& a, vector<string>& A)
{
	return find(A.begin(), A.end(), a) - A.begin();
}