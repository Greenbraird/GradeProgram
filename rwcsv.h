#pragma once
#include "Student.h"
#include "Professor.h"
#include "User.h"

#include <vector>

class rwcsv
{
public:
#pragma region user data 관련
	void AddUserDataCSV(const string& filename, User& user);
	vector<User*> ReadUserCSV(const string& user);
	void PrintUserCSV(const string& user);
	User* UserLogin(const string& filename, const string& id, const string& password);
#pragma endregion

#pragma region subject 관련
	void AddSubjectDataCSV(string subjectname, int professornum);
	void RemoveSubjectDataCSV(string subjectname);

	void MakeSubjectCSVFile(string subjectname, vector<string> studnetnameVector, vector<int> studentnums);
	void RemoveSubjectCSVFile(const string& subjectname);

	void AddSubjectToStudent(const string& subjectToAdd, const vector<int>& studentNumbers);
	void RemoveSubjectFromStudents(const string& subjectToRemove);

	void PrintSubjectList(const Professor& prof);
	void PrintSubjectList();
#pragma endregion

#pragma region 학생 및 교수 관련
	void UpdateAllStudentsGrade(const string& subjectName, const int& categorynum);
	void UpdateStudentGrade(const string& subjectName, int studentNumber, const int& category, int score);

	vector<string> PrintStudentSubject(const string& filename, const string& studentName);

	void PrintALLStudentGrade(vector<string> filenames, string studentName);
	void PrintStudentGrade(const string& filename, const string& studentName);

	void PrintStudentsList(string subjectname);
#pragma endregion
};

