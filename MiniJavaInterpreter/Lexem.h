#pragma once
#include <string>
#include <vector>
using namespace std;
enum _lexem_type
{
	_type,
	_integer,
	_real,
	_identifier,
	_string_constatn,
	_comment,
	_$b,
	_$e,
	_S,
	_boolean
};

string lexems_type[] = {		
	"type",
	"integer",
	"real",
	"identifier",	
	"string_constatn",
	"comment",
	"$b",
	"$e",
	"S",
	"boolean"
};

template<class T>
bool myFindInMas(const T* mas, int n, T& a)
{
	for (int i = 0; i < n; i++)
	{
		if (mas[i] == a)
			return true;
	}
	return false;
}

const string const  math_operators[] = { "+", "-", "*", "/", "%", "++", "--" };
const string const  bool_opreators[] = { "&&", "||", "!" };
const string const  comparison_operators[] = { "==", ">", "<", "<=", ">=", "!=" };
const string const  specifiers_visibility[] = { "public", "private", "protected" };
const string const  modifier[] = { "static", "const" };
const string const  class_codeword[] = { "class" };
const string const  this_codeword[] = { "this" };
const string const  main_codeword[] = { "main" };
const string const  controle_codeword[] = { "if", "else", "for", "while", "switch", "case", "default" };
const string const  types[] = { "int", "double", "string", "boolean", "long", "void" , "type" };
const string const  boolean_constant[] = { "true", "false" };


const char semicolon_dividers[] = { ';' };
const char point_dividers[] = { '.' };
const char comma_dividers[] = { ',' };
const char bracet_dividers[] = { '(', ')', '{', '}' };
const char assignment_divider[] = { '=' };
const char math_dividers[] = { '+', '-', '*', '/', '%' };
const char bool_dividers[] = { '&', '|', '!' };
const char compare_dividers[] = { '=', '<', '>' };
const char dividers[] = { '(', ')', '{', '}', '=', '.', ',', '	', ' ', ';', '+', '-', '*', '/', '%', '\n', '&', '|', '<', '>', '!' };
const char numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

#define dividers_size 21
#define numbers_size 10

struct lexem
{
	string str;
	_lexem_type type;
	string str_type;
	vector<int> positions;
	lexem(string lexem, _lexem_type t)
	{
		str = lexem;
		str_type = lexems_type[t];
		type = t;
	}
	lexem(string lexem, string t)
	{
		str = lexem;
		str_type = t;
	}
	lexem(string lexem)
	{
		str = lexem;
		if (myFindInMas(numbers, 10, str[0]) || (str[0] == '-' && str.length() > 1))
		{
			if (str.length() > 1 && (find(str.begin(), str.end(), 'e') != str.end()
				|| find(str.begin(), str.end(), '.') != str.end()))
				str_type = lexems_type[_real];
			else
				str_type = lexems_type[_integer];
		}
		else
		{

			if (myFindInMas(semicolon_dividers, 1, str[0]))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(point_dividers, 1, str[0]))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(comma_dividers, 1, str[0]))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(bracet_dividers, 4, str[0]))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(assignment_divider, 1, str[0]) && str.length() == 1)
			{
				str_type = str;
				return;
			}
			if (myFindInMas(math_operators, 7, str))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(bool_opreators, 3, str))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(comparison_operators, 6, str))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(specifiers_visibility, 3, str))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(modifier, 2, str))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(class_codeword, 1, str))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(this_codeword, 1, str))
			{
				str_type = str;
				return;
			}
			/*if (myFindInMas(main_codeword, 1, str))
			{
				str_type = str;
				return;
			}*/
			if (myFindInMas(controle_codeword, 7, str))
			{
				str_type = str;
				return;
			}
			if (myFindInMas(types, 7, str))
			{
				str_type = lexems_type[_type];
				return;
			}
			if (myFindInMas(boolean_constant, 2, str))
			{
				str_type = lexems_type[_boolean];
				return;
			}
			str_type = lexems_type[_identifier];
		}
	}

	void add_position(int pos)
	{
		positions.push_back(pos);
	}

	bool operator==(const lexem& a) const
	{
		return type == a.type && str == a.str;
	}

};