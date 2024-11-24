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

	void inputGrade_all(const string& subjectName);

	void inputGrade_search(const string& subjectName);

	void main() const override;

};

