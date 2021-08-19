#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

//à)

struct WordNode
{
	char data;
	std::vector<WordNode*> children;
};

WordNode* readTreeHelp(WordNode*& root, const char* &charTree)
{
	char ch = *charTree;
	root->data = ch;
	charTree++;

	if (*charTree == '[')
	{
		charTree++;
		while (*charTree != ']')
		{
			if (*charTree == '(')
			{
				charTree++;
				WordNode* child = new WordNode();
				readTreeHelp(child, charTree);
				root->children.push_back(child);
			}
			charTree++;
		}
		charTree++;
	}
	return root;
}

WordNode* readTree(const std::string& stringTree)
{
	WordNode* root = new WordNode();
	const char* charTree = stringTree.c_str() + 1;
	return readTreeHelp(root, charTree);
}

//á)

std::string printSentence(WordNode*& root)
{
	std::queue<WordNode*> queue;
	std::stack<WordNode*> stack;
	queue.push(root);
	stack.push(root);
	int size;
	std::string sentence = "";
	WordNode* current = nullptr;

	while (!queue.empty())
	{
		size = queue.size();

		while (size > 0)
		{
			current = queue.front();
			queue.pop();
			size--;

			size_t vectorSize = current->children.size();

			for (size_t i = 0; i < vectorSize; i++)
			{
				queue.push(current->children[i]);
				stack.push(current->children[i]);
			}
		}
	}

	while (!stack.empty())
	{
		sentence += stack.top()->data;
		sentence += " ";
		stack.pop();
	}

	return sentence;
}

//â)

void printTheBiggestLevel(WordNode*& root)
{
	std::queue<WordNode*> queue;
	queue.push(root);
	int size;
	int maxSize = 0;
	int level = 0;
	int maxLevel = 0;
	std::string levelSentence = "";
	std::string maxSentence = "";
	WordNode* current = nullptr;

	while (!queue.empty())
	{
		size = queue.size();
		level++;

		if (size > maxSize)
		{
			maxSize = size;
			maxLevel = level;
			maxSentence = levelSentence;
		}
		levelSentence = "";
		
		while (size > 0)
		{
			current = queue.front();
			queue.pop();
			size--;

			size_t vectorSize = current->children.size();

			for (size_t i = 0; i < vectorSize; i++)
			{
				levelSentence += current->children.at(i)->data;
			}

			for (size_t i = 0; i < vectorSize; i++)
			{
				queue.push(current->children[i]);
			}
		}
	}

	std::cout << maxSize << " " << maxLevel << " " << maxSentence;
}

int main()
{
	//std::string stringTree = "(A[(C[(H)(F)])(B)(S)(V)(P[(K)(M)(V)])])";
	std::string stringTree = "(k[(a[(y)])(y)(g[(a)(k)])])";
	WordNode* word = readTree(stringTree);

	/*std::string sentence = printSentence(word);
	std::cout << sentence;*/

	//printTheBiggestLevel(word);

	return 0;
}

