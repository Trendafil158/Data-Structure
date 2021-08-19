#include <iostream>
#include <string>
#include <unordered_map>

int countFreq(std::string& pat, std::string& txt)
{
	int M = pat.length();
	int N = txt.length();
	int res = 0;

	for (int i = 0; i <= N - M; i++)
	{
		int j;
		for (j = 0; j < M; j++)
			if (txt[i + j] != pat[j])
				break;

		if (j == M)
		{
			res++;
			j = 0;
		}
	}
	return res;
}

std::string toggle(std::string& str)
{
	int length = str.length();
	for (int i = 0; i < length; i++) {
		int c = str[i];
		if (isupper(c))
			str[i] = tolower(c);
	}

	return str;
}

int CountWords(std::string str)
{
	int count = 1;
	int size = str.length();

	for (int i = 0; i < size; i++)
	{
		if (str[i] == ' ')
		{
			count++;
		}
	}
	return count;
}

std::string removeSymbol(std::string& str)
{
	std::string output;
	output.reserve(str.size()); // optional, avoids buffer reallocations in the loop
	for (size_t i = 0; i < str.size(); ++i)
		if (str[i] != ',' && str[i] != '!') output += str[i];

	return output;
}

// а)

void findEqualWords(std::string& firstSentence, std::string& secondSentence)
{
	std::unordered_map<std::string, int> multWordsForFirst;
	std::unordered_map<std::string, int> multWordsForSecond;
	std::unordered_map<std::string, int> finalWords;

	std::string firstWord = "";
	std::string secondWord = "";

	firstSentence = toggle(firstSentence);
	secondSentence = toggle(secondSentence);

	firstSentence = removeSymbol(firstSentence);
	secondSentence = removeSymbol(secondSentence);

	int sizeFirst = firstSentence.length();
	int sizeSecond = secondSentence.length();

	for (int i = 0; i < sizeFirst; i++)
	{
		if (firstSentence[i] == ' ')
		{
			multWordsForFirst[firstWord]++;
			firstWord = "";                                    
			continue;
		}

		firstWord += firstSentence[i];

		if (i == sizeFirst - 1)
		{
			multWordsForFirst[firstWord]++;
			firstWord = "";
		}
	}

	for (int i = 0; i < sizeSecond; i++)
	{
		if (secondSentence[i] == ' ')
		{
			multWordsForSecond[secondWord]++;
			secondWord = "";
			continue;
		}

		secondWord += secondSentence[i];

		if (i == sizeSecond - 1)
		{
			multWordsForSecond[secondWord]++;
			secondWord = "";
		}
	}

	for (auto const& pair : multWordsForFirst)
	{
		int count = pair.second;
		for (auto const& secondPair : multWordsForSecond)
		{
			if (secondPair.first == pair.first)
			{
				count += secondPair.second;
				finalWords[pair.first] = count;
			}
		}
	}

	for (auto const& pair : finalWords)
	{
		std::cout << pair.first << "\n";
	}
}

//б)

void findAfterWords(std::string& sentence)
{
	std::unordered_map<std::string, int> collectWords;
	sentence = removeSymbol(sentence);
	sentence = toggle(sentence);
	int size = sentence.length();
	int i = 0;
	std::string helpStr = "";
	const int maxSize = CountWords(sentence);
	std::string array[1000];
	int j = 0;

	while (i < size)
	{
		helpStr += sentence[i];
		if (sentence[i] == ' ')
		{
			array[j] = helpStr;
			j++;
			helpStr = "";
		}
		i++;

		if (i == size)
		{
			array[j] = helpStr;
			j++;
			helpStr = "";
		}
	}

	j = 0;
	while (j < maxSize)
	{
		helpStr += array[j] += '/';
		helpStr += array[j + 1];
		collectWords[helpStr]++;
		helpStr = "";
		j++;
	}

	for (auto const& pair : collectWords)
	{
		if (pair.second >= 2)
		{
			std::cout << pair.first << ": " << pair.second << "\n";
		}
	}
}

//в)

bool canBeCreatedByFirst(std::string& firstStr, std::string& secondStr)
{
	firstStr = toggle(firstStr);
	secondStr = toggle(secondStr);

	firstStr = removeSymbol(firstStr);
	secondStr = removeSymbol(secondStr);

	std::unordered_map<std::string, int> firstMap;
	std::unordered_map<std::string, int> secondMap;

	int firstSize = firstStr.length();
	int secondSize = secondStr.length();

	std::string helpStr = "";

	int i = 0;
	
	while (i < firstSize)
	{
		helpStr += firstStr[i];

		if (firstStr[i] == ' ')
		{
			firstMap[helpStr]++;
			helpStr = "";
		}
		i++;

		if (i == firstSize)
		{
			firstMap[helpStr]++;
			helpStr = "";
		}
	}

	i = 0;
	helpStr = "";

	while (i < secondSize)
	{
		helpStr += secondStr[i];

		if (secondStr[i] == ' ')
		{
			secondMap[helpStr]++;
			helpStr = "";
		}
		i++;

		if (i == secondSize - 1)
		{
			secondMap[helpStr]++;
			helpStr = "";
		}
	}

	int mapFirstSize = firstMap.size();
	int mapSecondSize = secondMap.size();

	if (mapFirstSize != mapSecondSize)
	{
		return false;
	}

	for (std::unordered_map<std::string, int>::iterator firstIt = firstMap.begin(), secondIt = secondMap.begin(); firstIt != firstMap.end(), secondIt != secondMap.end(); firstIt++, secondIt++)
	{
		if (firstIt->second != secondIt->second)
		{
			return false;
			break;
		}
	}

	return true;
}

int main()
{
	std::string first = "The brown fox jumps over the brown dog";
	std::string second = "What an easy exam today, what an opportunity!";
	std::string third = "What a difficult exam today, I give up!";
	std::string b = "In computing a hash table (hash map) is a data structure that implements an associative array abstract data type, a structure that can map keys to values. A hash table uses a hash function to compute an index, also called a hash code, into an array of buckets or slots, from which the desired value can be found.";

	//Проверка за а)
	findEqualWords(second, third);

	std::cout << "\n";

	//Проверка за б)
	findAfterWords(b);

	std::cout << "\n";

	//Проверка за в)
	std::cout << canBeCreatedByFirst(first, second);

	return 0;
}

