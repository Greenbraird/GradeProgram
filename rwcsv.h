#pragma once
#include "Student.h"
#include "Professor.h"
#include "User.h"

#include <vector>

class rwcsv
{
public:
	//person을 상속 받은 애들 read write하는 프로그래밍
	void SaveUserDataSCV(const string& filename, User& user);

	User* UserLogin(const string& filename, const string& id, const string& password);
};

