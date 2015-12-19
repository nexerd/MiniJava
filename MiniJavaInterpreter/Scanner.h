#pragma once
#include "Lexem.h"
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>


class lexical_exception : exception
{
public:
	int position;
	const char* str;
	lexical_exception(int pos, const char* cause) : position(pos), exception()
	{
		char* buff = new char[100];
		strcpy(buff, cause);
		str = buff;
	}
	virtual const char* what() const throw() { return str; }
};





struct automatic
{
	int state;
	string str;

	automatic() : state(0) { str = ""; }

	virtual string get_value()
	{
		string rezult = str;
		state = 0;
		str = "";
		return rezult;
	}

	virtual bool recognize(char a) = 0;
};

struct number_automatic : automatic
{
	virtual bool recognize(char a)
	{
		switch (state)
		{
		case 0:{
				   if (a == '-' || myFindInMas(numbers, numbers_size, a))
				   {
					   state = 1;
					   str += a;
					   return true;
				   }
				   else
					   return false;
		}
		case 1:{
				   if (myFindInMas(numbers, numbers_size, a))
				   {
					   str += a;
					   return true;
				   }
				   if (a == '.')
				   {
					   state = 2;
					   str += a;
					   return true;
				   }
				   if (a == 'e')
				   {
					   state = 3;
					   str += a;
					   return true;
				   }
				   if (myFindInMas(dividers, dividers_size, a))
				   {
					   return false;
				   }
				   throw exception("Not a naumber.");//return false;					   
		}
		case 2:{
				   if (myFindInMas(numbers, numbers_size, a))
				   {
					   str += a;
					   return true;
				   }
				   return false;
		}
		case 3:{
				   if (a == '+' || a == '-')
				   {
					   state = 2;
					   str += a;
					   return true;
				   }
				   if (myFindInMas(dividers, dividers_size, a))
				   {
					   str += a;
					   return false;
				   }
				   throw exception("Excepted sign(\"+\" or \"-\").");//return false;
		}
		default:
			return false;
			break;
		}
	}
};

struct string_automatic : automatic
{
	bool is_string(char a)
	{
		return (97 <= a && a <= 122) || (65 <= a && a <= 90 || a == '_') || (48 <= a && a < 58);
	}
	virtual bool recognize(char a)
	{
		switch (state)
		{
		case 0:
		{
				  // if (!(myFindInMas(numbers, numbers_size, a) || myFindInMas(dividers, dividers_size, a)))
				  if (is_string(a))
				  {
					  state = 1;
					  str += a;
					  return true;
				  }
				  return false;
		}
		case 1:
		{
				  //if (!myFindInMas(dividers, dividers_size, a))
				  if (is_string(a))
				  {
					  str += a;
					  return true;
				  }
				  return false;
		}
		default:
			return false;
			break;
		}
	}

};

struct comment_automatic : automatic
{
	virtual bool recognize(char a)
	{
		switch (state)
		{
		case 0:{
				   if (a == '/')
				   {
					   state = 1;
					   return true;
				   }
				   return false;
		}
		case 1:{
				   if (a == '/')
				   {
					   state = 2;
					   return true;
				   }
				   if (a == '*')
				   {
					   state = 3;
					   return true;
				   }
				   return false;
		}
		case 2:{
				   if (a != '\n')
				   {
					   str += a;
					   return true;
				   }
				   return false;
		}
		case 3:{
				   if (a != '*')
				   {
					   str += a;
				   }
				   else
					   state = 4;
				   return true;

		}
		case 4:{
				   if (a != '/')
				   {
					   str += a;
					   if (a != '*')
					   {
						   state = 3;
						   return true;
					   }
				   }
				   return false;

		}
		default:
			return false;
			break;
		}
	}
};

struct operator_automatic : automatic
{
	virtual bool recognize(char a)
	{
		switch (state)
		{
		case 0:{
				   if (myFindInMas(semicolon_dividers, 1, a))
				   {
					   str += a;
					   state = 1;
					   return true;
				   }
				   if (myFindInMas(point_dividers, 1, a))
				   {
					   str += a;
					   state = 1;
					   return true;
				   }
				   if (myFindInMas(comma_dividers, 1, a))
				   {
					   str += a;
					   state = 1;
					   return true;
				   }
				   if (myFindInMas(bracet_dividers, 4, a))
				   {
					   str += a;
					   state = 4;
					   return true;
				   }
				   if (myFindInMas(assignment_divider, 1, a))
				   {
					   str += a;
					   state = 3;
					   return true;
				   }
				   if (myFindInMas(math_dividers, 6, a))
				   {
					   str += a;
					   state = 1;
					   return true;
				   }
				   if (myFindInMas(bool_dividers, 3, a))
				   {
					   str += a;
					   if (a != '!')
					   {
						   state = 2;
						   //   return true;
					   }
					   else
						   state = 3;
					   return true;
				   }
				   if (myFindInMas(compare_dividers, 3, a))
				   {
					   str += a;
					   state = 3;
					   return true;
				   }
				   return false;
		}
		case 1:{
				   if ((str.back() == '+' && a == '+') || (str.back() == '-' && a == '-'))
				   {
					   str += a;
				   }
				   return false;
		}
		case 2:{
				   if ((str.back() == '&' && a == '&') || (str.back() == '|' && a == '|'))
				   {
					   str += a;
					   return false;
				   }
				   throw exception("Expected bool operator.");
		}
		case 3:{
				   if (((str.back() == '!' || str.back() == '=' || str.back() == '<' || str.back() == '>') &&
					   a == '='))
				   {
					   str += a;
				   }
				   return false;
		case 4:{
				   return false;
		}
		}
		default:
			break;
		}
	}
};

struct string_constants_automatic : automatic
{
	virtual bool recognize(char a)
	{
		switch (state)
		{
		case 0:{
				   if (a == '"')
				   {
					   state = 1;
					   return true;
				   }
				   return false;
		}
		case 1:{
				   if (a != '"')
				   {
					   str += a;
					   return true;
				   }
				   return false;
		}
		default:
			break;
		}
	}
};

struct Scanner
{
	int state;
	string buff;

	string ProgrammFile;
	vector<lexem> lexemes;

	number_automatic FSA_number;
	string_automatic FSA_string;
	comment_automatic FSA_comment;
	operator_automatic FSA_operator;
	string_constants_automatic FSA_string_constatns;

	Scanner() : state(0), ProgrammFile("ProgrammFile.txt") {};

	void add_to_lexems_list(lexem buff)
	{
		lexemes.push_back(buff);
	}

	void recognize(string& str)
	{
		str += '\n';
		for (int i = 0; i < str.length(); ++i)
		{
			try{
				switch (state)
				{
				case 0:{
						   if (FSA_number.recognize(str[i]))
						   {
							   state = 1;
							   break;
						   }
						   if (FSA_string.recognize(str[i]))
						   {
							   state = 2;
							   break;
						   }
						   if (FSA_comment.recognize(str[i]))
						   {
							   state = 3;
							   break;
						   }
						   if (FSA_operator.recognize(str[i]))
						   {
							   state = 4;
							   break;
						   }
						   if (FSA_string_constatns.recognize(str[i]))
						   {
							   state = 5;
							   break;
						   }
						   break;
				}
				case 1:{

						   if (!FSA_number.recognize(str[i]))
						   {
							   --i;
							   // lexemes.push_back(FSA_number.get_value());
							   add_to_lexems_list(FSA_number.get_value());
							   state = 0;
						   }
						   break;
				}
				case 2:{
						   if (!FSA_string.recognize(str[i]))
						   {
							   --i;
							   //lexemes.push_back(FSA_string.get_value());
							   add_to_lexems_list(FSA_string.get_value());
							   state = 0;
						   }
						   break;
				}
				case 3:{
						   if (!FSA_comment.recognize(str[i]))
						   {
							   buff = FSA_comment.get_value();
							   if (buff == "")
							   {
								   i -= 2;
								   state = 4;
							   }
							   else
							   {
								   state = 0;
								   // lexemes.push_back(lexem(buff, _comment));
								   add_to_lexems_list(lexem(buff, _comment));
							   }

						   }
						   break;
				}
				case 4:{
						   if (!FSA_operator.recognize(str[i]))
						   {
							   if (FSA_operator.str.length() == 1)
								   --i;
							   //lexemes.push_back(FSA_operator.get_value());
							   add_to_lexems_list(FSA_operator.get_value());
							   state = 0;
						   }
						   break;
				}
				case 5:{
						   if (!FSA_string_constatns.recognize(str[i]))
						   {
							   //lexemes.push_back(lexem(FSA_string_constatns.get_value(), _string_constatn));
							   add_to_lexems_list(lexem(FSA_string_constatns.get_value(),
								   _string_constatn));
							   state = 0;
						   }
						   else
						   if (i == str.length() - 1)
						   {
							   throw exception("Expected \" ");
						   }
						   break;
				}
				default:
					break;
				}

			}
			catch (exception ex)
			{
				throw lexical_exception(i, ex.what());
			}
		}
	}

	void check()
	{
		if (state != 0)
		{
			if (FSA_comment.state != 0)
				throw lexical_exception(0, "Commend is not closed!");
		}
	}

	void work()
	{
		string str;		
		ifstream fin(ProgrammFile);
		try
		{
			while (!fin.eof())
			{
				getline(fin, str);
				cout << str << endl;
				recognize(str);
			}
			check();
		}
		catch (lexical_exception& ex)
		{
			for (int i = 0; i < ex.position; i++)
				cout << '.';
			cout << "^" << endl;
			cout << "Lexical error!" << endl;
			cout << ex.what() << endl;
		}
		fin.close();
	}
};
