#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;


map <int, char> dict;

void FullDict()
{
	int first;
	char second;
	ifstream f("Dictionary.txt");
	string s;
	while (getline(f,s))
	{
		second = s[0];
		s.erase(0, 4);
		first = stoi(s);
		dict.insert(pair<int, char>(first, second));
	}
	f.close();
}
