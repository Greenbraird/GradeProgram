#pragma once
#include <string>

using namespace std;

// 이름, 전공, 학번, 아이디, 비번, 이메일의 멤버 변수를 가지는 클래스
class User {

private:
    string name;
    string major;
    int number;
    string id;
    string password;
    string email;

public:
    User(string n="", string m = "",
        int num=0, string i="", string p = "", string e = "")
        : name(n), major(m), number(num), id(i), password(p), email(e) {}


    virtual void main() const = 0;

    string getName() const { return name; }
    string getMajor() const { return major; }
    int getNumber() const { return number; }
    string getId() const { return id; }
    string  getPassword() const { return password; }
    string getEmail() const { return email; }

    void setMajor(string m) { major = m; }
    void setName(string n) { name = n; }
    void setNumber(int num) { number = num; }
    void setId(string _id) { id = _id; }
    void setPassword(string pw) { password = pw; }
    void setEmail(string em) { email = em; }
};
