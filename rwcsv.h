#pragma once
#include "Student.h"
#include "Professor.h"
#include "User.h"

#include <vector>

class rwcsv
{
public:
	//person�� ��� ���� �ֵ� read write�ϴ� ���α׷���
	void SaveUserDataCSV(const string& filename, User& user);

	vector<User*> ReadUserCSV(const string& user);

	void PrintUserCSV(const string& user);

	User* UserLogin(const string& filename, const string& id, const string& password);

};

