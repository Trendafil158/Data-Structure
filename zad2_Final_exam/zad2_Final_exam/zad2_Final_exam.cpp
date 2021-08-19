#include <iostream>
#include <fstream>

struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
	{
		this->data = data;
		this->left = left;
		this->right = right;
	}
};

// à)

int sumEven(TreeNode*& root)
{
	if (root == nullptr)
	{
		return 0;
	}

	int n = 0;

	if (root->data % 2 == 0)
	{
		n = root->data;
	}
	 
	return n + sumEven(root->left) + sumEven(root->right);
}

int sumOdd(TreeNode*& root)
{
	if (root == nullptr)
	{
		return 0;
	}

	int n = 0;
	if (root->data % 2 != 0)
	{
		n = root->data;
	}

	return n + sumOdd(root->left) + sumOdd(root->right);
}

TreeNode* checkEqualEvenOddElements(TreeNode*& root, TreeNode* &write)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (sumEven(root) == sumOdd(root))
	{
		write = root;
	}

	checkEqualEvenOddElements(root->left, write);
	checkEqualEvenOddElements(root->right, write);

	return write;
}

// á)

void reverseString(std::string& res, int count)
{
	char temp;
	for (int i = 0; i < count / 2; i++)
	{
		temp = res[i];
		res[i] = res[count - 1 - i];
		res[count - 1 - i] = temp;
	}
}

void convertNumberToString(std::string& str, int number)
{
	int count = 0;
	std::string res;
	while (number != 0)
	{
		res += number % 10 + '0';
		number /= 10;
		count++;
	}
	reverseString(res, count);
	str += res;
}

void convertTreeToStr(TreeNode*& root, std::string& stringTree)
{
	if (root == nullptr)
	{
		stringTree += " ()";
		return;
	}

	stringTree += stringTree.empty() ? "(" : " (";
	convertNumberToString(stringTree, root->data);

	convertTreeToStr(root->left, stringTree);
	convertTreeToStr(root->right, stringTree);
	stringTree += ")";
}

void writeFile(const std::string& fileName)
{
	std::ofstream outFile(fileName);

	TreeNode* root = new TreeNode(8);
	root->left = new TreeNode(10);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(7);
	root->right = new TreeNode(7);
	root->right->left = new TreeNode(23);
	root->right->right = new TreeNode(4);

	std::string treeToString;
	convertTreeToStr(root, treeToString);

	if (!outFile.is_open())
	{
		std::cout << "Unable to open " << fileName << " file.\n";
		return;
	}

	outFile << treeToString << "\n";

	outFile.close();
}

// â)

void insertBST(TreeNode*& root, int data)
{
	if (root == nullptr)
	{
		return;
	}

	if (data < root->data)
	{
		insertBST(root->left, data);
	}
	else
	{
		insertBST(root->right, data);
	}
}

int main()
{
	TreeNode* root = new TreeNode(8);
	root->left = new TreeNode(10);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(7);
	root->right = new TreeNode(7);
	root->right->left = new TreeNode(23);
	root->right->right = new TreeNode(4);

	//std::cout << sumOdd(root);
	TreeNode* write = new TreeNode();
	TreeNode* node = checkEqualEvenOddElements(root, write);
	std::cout << node->data;

	writeFile("text.txt");

	return 0;
}

