#ifndef POLISH_EXPRESSION_H_
#define POLISH_EXPRESSION_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include "tstack.h"

using namespace std;


class PolishExpression
{
private:
	string infix;				// начальное выражение
	string postfix;				// обратная польская запись
	vector<char> lexem;			// массив лексем
	map<char, int> priority;	// приоритеты операций
	map<char, double> operands;	// значения переменных


	void Parse();				// разбиение на лексемы
	void ToPostfix();			// перевод в обратную польскую запись


public:
	PolishExpression(string str_infix);
	~PolishExpression() {}

	vector<char> GetOperands() const;
	string GetInfix() const;
	string GetPostfix();
	double Calculate(const map<char, double>& values);
};


#endif 