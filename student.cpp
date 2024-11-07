#include "student.h"

#include <iostream>
student::student(string n ="", string m="", int num=0,
	string _id="", string pw="", string em="") {
	name = n;
	number = num;
	major = m;
	id = _id;
	password = pw;
}

//getter와 setter만들기

string student::getName() {return name;}
string student::getMajor() { return major; }
int student::getNumber() { return number; }
string student::getId() { return id; }
string  student::getPassword() { return password; }

void student::setMajor(string m) { major = m; }
void student::setName(string n) { name = n; }
void student::setNumber(int num) { number = num; }
void student::setId(string _id) { id = _id; }
void student::setPassword(string pw) { password = pw; }


void studentmain() {
	
}