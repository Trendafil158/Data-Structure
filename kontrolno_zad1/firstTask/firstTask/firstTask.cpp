#include <iostream>
#include <string>
#include <stack>

// 1 задача
struct Node {
	int data;
	Node* next;

	//Използвам конструктор единствено с цел по лесна инициализация на данната, сочена от указателя
	Node(int data, Node* next = nullptr)
	{
		this->data = data;
		this->next = next;
	}
};

void pushBack(Node*& first, int data)
{
	Node* newNode = new Node(data);

	if (first == nullptr)
	{
		first = newNode;
	}
	else
	{
		Node* current = first;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = newNode;
		//newNode->next = nullptr;
	}
}

void printList(Node*& first)
{
	Node* current = first;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

void pushBefore(Node*& first, int data, int beforeData)
{
	if (first == nullptr)
	{
		return;
	}

	Node* current = first;
	Node* newNode = new Node(data);

	while (current->next != nullptr && current->next->data != beforeData)
	{
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;
}

Node* fillGaps(Node*& L)
{
	Node* current = L;

	while (current->next != nullptr)
	{

		if (current->data != current->next->data - 1)
		{
			int firstNumber = current->data;
			Node* numberToInsert = current;
			int secondNumber = current->next->data;
			while (numberToInsert->data != secondNumber - 1)
			{
				pushBefore(L, ++firstNumber, secondNumber);
				numberToInsert = numberToInsert->next;
			}
		}
		current = current->next;
	}
	return L;
}

//Задача 2б

//Необходима ни е функция, която превръща символ в число. Не съм я реализирал, но я добавям понеже е нужна.
int convertCharToNum(char el)
{
	return 0;
}

bool isDigit(char n)
{
	return n >= '0' || n <= '9';
}

void decode(std::string s)
{
	std::stack<int> numberSymStack;
	std::stack<char> symbolStack;
	std::stack<std::string> resultStack;

	int sizeOfString = s.size();

	for (int i = 0; i < sizeOfString; i++)
	{
		if (isDigit(s[i]))
		{
			numberSymStack.push(convertCharToNum(s[i]));
		}
		if (s[i] == '[')
		{
			numberSymStack.push(s[i]);
		}

		if (s[i] != ']')
		{
			symbolStack.push(s[i]);
		}
		else
		{
			std::string strLetters = "";
			while (!symbolStack.empty())
			{
				strLetters += symbolStack.top();
				symbolStack.pop();
			}
			numberSymStack.pop();

			std::string result = "";
			int timesToPrint = numberSymStack.top();
			numberSymStack.pop();
			for (int i = 0; i < timesToPrint; i++)
			{
				result += strLetters;
			}
			resultStack.push(result);
		}
	}
}

int main()
{
	//Тест за първата задача

	Node* first = nullptr;

	pushBack(first, 1);
	pushBack(first, 3);
	pushBack(first, 4);
	pushBack(first, 8);
	pushBack(first, 15);
	pushBack(first, 30);
	pushBack(first, 40);

	std::cout << "This is our list: " << std::endl;
	printList(first);
	std::cout << std::endl;

	std::cout << "This is the result: " << std::endl;
	Node* result = fillGaps(first);
	printList(result);

	return 0;
}

