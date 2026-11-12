#include "poland.h"
#include <iostream>

using namespace std;

int main()
{
    // Пример 1: просто числа
    PolishExpression expr1("a + b * c");
    map<char, double> vals1 = { { 'a', 2 },{ 'b', 3 },{ 'c', 4 } };
    cout << "Infix: " << expr1.GetInfix() << endl;
    cout << "Postfix: " << expr1.GetPostfix() << endl;
    cout << "Result: " << expr1.Calculate(vals1) << endl; // 2 + 3*4 = 14

    // Пример 2: с переменными
    PolishExpression expr2("(a + b) * c");
    map<char, double> vals2 = { { 'a', 1 },{ 'b', 2 },{ 'c', 3 } };
    cout << "Infix: " << expr2.GetInfix() << endl;
    cout << "Postfix: " << expr2.GetPostfix() << endl;
    cout << "Result: " << expr2.Calculate(vals2) << endl; // (1+2)*3 = 9

    return 0;
}