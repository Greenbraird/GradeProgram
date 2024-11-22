#pragma once
#include "Student.h"
#include "Professor.h"
#include "User.h"

#include <vector>

class rwcsv
{
public:
	//person을 상속 받은 애들 read write하는 프로그래밍
	void AddUserDataCSV(const string& filename, User& user);

	vector<User*> ReadUserCSV(const string& user);

	void PrintUserCSV(const string& user);

	User* UserLogin(const string& filename, const string& id, const string& password);


	void AddSubjectDataCSV(string subjectname, int professornum, vector<int> studentnums);

	void MakeSubjectCSV(string subjectname, vector<int> studentnums);
	
	void deletSubjectCSV(string subjectname);

	void PrintSubjectList();
};

