#pragma once
#include "Student.h"
#include "Professor.h"
#include "User.h"

#include <vector>

class rwcsv
{
public:
	//person�� ��� ���� �ֵ� read write�ϴ� ���α׷���
	void SaveUserDataSCV(const string& filename, User& user);

	User* UserLogin(const string& filename, const string& id, const string& password);
};

