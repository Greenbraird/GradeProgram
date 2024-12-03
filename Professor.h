#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include "User.h"

using namespace std;


class Professor : public User
{
public:
	Professor(const string& n, const string& m,
		int num, const string& i, const string& p, const string& e)
		: User(n, m, num, i, p, e) {}

	int inputScore(const string& prompt, int min, int max);

	pair<string, vector<string>> readFile (string& subjectFilename);

	void inputGrade_searchStudent(string& filename);

	void inputGrade_selectedHeader(string& filename);

	void main();

};

