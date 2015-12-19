#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
// ������� ����������
struct rule
{
	// ����� �� ����. ������
	string left;
	// ������ ����� �������
	vector<string> right;
	// ���������, ��� ������ ������� �� ��������� ����� �����.
	bool operator==(const string& a);
};

// ���������, ��� ������ ������� �� ��������� ����� �����.
bool rule::operator==(const string& a)
{
	return left == a;
}


// ��������, ��� ������� ���������������
// - , <* , *>, =*
// ��� ������, � ������������ �, � ������� �� �, � � � - ������
enum precedenceRelation { empty = 0, preceded, follow, basic };

// ����������� �������������� �������
bool isFrom(string& a, vector<string>& A)
{
	return find(A.begin(), A.end(), a) != A.end();
}

// ����� ������� � �������
int whatPosition(string& a, vector<string>& A)
{
	return find(A.begin(), A.end(), a) - A.begin();
}