#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

struct elem
{
	string data;
	elem *next;
};
typedef elem* Pelem;

class Hash
{
	Pelem *hashtable;
	int size;
	int full = 0;
public:
	Hash() : hashtable(nullptr), size(200), full(0) {}
	int myHash(string);
	void insert_elem(string);
	void create_Hash();
	string reseach(string);
	int Hash_key(string);
};

int Hash::Hash_key(string str)
{
	char ch;
	int sum = 0, dit, i = 0;
	while (str[i] != '\0')
	{
		ch = str[i];
		dit = ch;
		sum = sum + dit;
		i++;
	}
	return (sum%size);
}

int Hash::myHash(string str)
{
	char ch;
	int sum = 0, dit;
	for (int i = 0; i < str.find(';'); i++)
	{
		ch = str[i];
		dit = ch;
		sum = sum + dit;
	}
	return (sum%size);
}

void Hash::insert_elem(string str)
{
	Pelem p, p0;
	int h = myHash(str);
	p = new elem;
	if (!hashtable[h])
	{
		full++;
		if (full > 80 * (size / 100));
	}
	p0 = hashtable[h];
	hashtable[h] = p;
	p->next = p0;
	p->data = str;
}

void Hash::create_Hash()
{
	hashtable = new elem*[size];
	for (int i = 0; i < size; i++)
	{
		hashtable[i] = nullptr;
	}
	ifstream dict("dict_processed.txt");
	string str;
	while (!dict.eof())
	{
		getline(dict, str);
		if (!dict.eof()) insert_elem(str);
	}
	dict.close();
}

string Hash::reseach(string str)
{
	int h = Hash_key(str);
	Pelem p;
	p = hashtable[h];
	while (p)
	{
		if (p->data.substr(0, p->data.find(';')) == str) return p->data;
		p = p->next;
	}
	return "Слово не найдено.";
}

void output(Hash &table, string &word)
{

	cout << "Найденное слово <" << word << ">" << endl;
	transform(word.begin(), word.end(), word.begin(), toupper);
	cout << table.reseach(word) << endl;
	word = "";
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Таблица генерируется. Пожалуйста, подождите." << endl;
	Hash table;
	table.create_Hash();
	cout << "Таблица готова. Введите своё предложение:" << endl;
	string sentense;
	getline(cin, sentense);
	string word;
	while (sentense.length() != 0)
	{
		int k = 0;
		while (sentense[k] != ' ' && sentense[k] != '\0')
		{
			if (sentense[k] != ',' && sentense[k] != '.') word += sentense[k];
			k++;
		}
		output(table, word);
		if (sentense[k] != '\0') sentense.erase(0, sentense.find(' ') + 1);
		else sentense.erase(0, sentense.find('\0'));

	}
	system("pause");
}