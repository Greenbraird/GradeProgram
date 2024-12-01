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

	void inputGrade_all(const string& filename);

	void inputGrade_search(const string& filename);

	void inputGrade_selectedHeader(const string& filename);

	vector<string> readFile(const string& filename);

	void main() const override;

};

