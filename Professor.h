#pragma once
#include <iostream>
#include <cstring>
#include "User.h"

using namespace std;


class Professor : public User
{
public:
	Professor(const string& n, const string& m,
		int num, const string& i, const string& p, const string& e)
		: User(n, m, num, i, p, e) {}

	void main() const override;
};

