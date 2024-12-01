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


	void AddSubjectDataCSV(string subjectname, int professornum);
	void MakeSubjectCSV(string subjectname, vector<string> studnetnameVector, vector<int> studentnums);
	void AddSubjectToStudent(const string& subjectToAdd, const vector<int>& studentNumbers);
	void deletSubjectCSV(const string& subjectname);

	void PrintSubjectList(const Professor& prof);
	void PrintSubjectList();

	vector<string> PrintStudentSubject(const string& filename, const string& studentName);

	void PrintALLStudentGrade(const vector<string>& filenames, const string& studentName);
	void PrintStudentGrade(const string& filename, const string& studentName);
};

