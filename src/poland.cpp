#include "tstack.h"
#include "poland.h"
#include <stdexcept>


PolishExpression::PolishExpression(string str_infix)
{
	infix = str_infix;

	priority = { { '+', 1 },{ '-', 1 },{ '*', 2 },{ '/', 2 },{ '(', 0 } };

	ToPostfix();
}

void PolishExpression::Parse()
{
	for (char c : infix)
		if (c != ' ')
			lexem.push_back(c);
}

void PolishExpression::ToPostfix()
{
	Parse();
	TStack<char> st((int)lexem.size() + 1);
	char StackItem;

	for (char Item : lexem)
	{
		switch (Item)
		{
		case ('('):
			st.push(Item);
			break;

		case (')'):
			StackItem = st.top();
			st.pop();

			while (StackItem != '(')
			{
				postfix += StackItem;
				StackItem = st.top();
				st.pop();
			}
			break;

		case '+': case '-': case '*': case '/':
			while (!st.empty())
			{
				StackItem = st.top();
				st.pop();

				if (priority[Item] <= priority[StackItem])
					postfix += StackItem;
				else
				{
					st.push(StackItem);
					break;
				}
			}
			st.push(Item);
			break;

		default:
			operands.insert({ Item,{ 0.0 } });
			postfix += Item;
			break;
		}
	}

	while (!st.empty())
	{
		StackItem = st.top();
		st.pop();
		postfix += StackItem;
	}
}


double PolishExpression::Calculate(const map<char, double>& values)
{
	for (auto& val : values)
		operands.at(val.first) = val.second;

	TStack<double> st((int)postfix.size() + 1);
	double left, right;

	for (char lexem : postfix)
	{
		switch (lexem)
		{
		case '+':
			right = st.top();
			st.pop();
			left = st.top();
			st.pop();
			st.push(left + right);
			break;

		case '-':
			right = st.top();
			st.pop();
			left = st.top();
			st.pop();
			st.push(left - right);
			break;

		case '*':
			right = st.top();
			st.pop();
			left = st.top();
			st.pop();
			st.push(left * right);
			break;

		case '/':
			right = st.top();
			st.pop();
			left = st.top();
			st.pop();
			if (right == 0) throw runtime_error("Division by zero");
			st.push(left / right);
			break;

		default:
			st.push(operands[lexem]);
			break;
		}
	}

	return st.top();
}


vector<char> PolishExpression::GetOperands() const
{
	vector<char> op;
	for (const auto& item : operands)
	{
		op.push_back(item.first);
	}
	return op;
}

string PolishExpression::GetInfix() const
{
	return infix;
}


string PolishExpression::GetPostfix()
{
	return postfix;
}