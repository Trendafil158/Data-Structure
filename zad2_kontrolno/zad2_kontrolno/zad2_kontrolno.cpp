#include <iostream>
#include <stack>
#include <queue>
#include <string.h>

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

int convertToNum(char c)
{
	int b = c - '0';
	return b;
}

std::string decodeExpression(std::string& expression)
{
	std::stack<int> numberStack;
	std::stack<char> symbolStack;
	std::stack<char> helpStack;

	std::string helpStr = "";
	std::string mainStr = "";
	std::string finalStr = "";

	int size = expression.length();

	for (int i = 0; i < size; i++)
	{
		if (isDigit(expression[i]))
		{
			numberStack.push(convertToNum(expression[i]));
		}
		else
		{
			if (expression[i] == ']')
			{
				continue;
			}
			symbolStack.push(expression[i]);
		}
	}

	while (!numberStack.empty())
	{
		while (symbolStack.top() != '[')
		{
			helpStack.push(symbolStack.top());
			symbolStack.pop();
		}
		symbolStack.pop();

		while (!helpStack.empty())
		{
			helpStr += helpStack.top();
			helpStack.pop();
		}

		int count = numberStack.top();
		numberStack.pop();

		for (int i = 0; i < count; i++)
		{
			mainStr += helpStr;
		}
		helpStr = "";

		for (int j = 0; j < mainStr.size(); j++)
		{
			symbolStack.push(mainStr[j]);
		}
		mainStr = "";
	}

	while (!symbolStack.empty())
	{
		helpStack.push(symbolStack.top());
		symbolStack.pop();
	}

	while (!helpStack.empty())
	{
		finalStr += helpStack.top();
		helpStack.pop();
	}

	return finalStr;
}

int main()
{
	std::string str = "abc2[cd]";
	std::cout << "Decode string: " << decodeExpression(str);

	return 0;
}


