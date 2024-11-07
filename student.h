#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class student
{
private:
	string name;
	string major;
	int number;
	string id;
	string password;

public:
	student(string n , string m , int num,
		string id , string pw , string em );

	string getName();
	string getMajor();
	int getNumber();
	string getId();
	string getPassword();

	void setName(string n);
	void setMajor(string m);
	void setNumber(int num);
	void setId(string _id);
	void setPassword(string pw);

};

void studentmain();
