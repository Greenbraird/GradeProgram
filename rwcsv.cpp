#include "rwcsv.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/// <summary>
/// 파일이름에서 id와 password가 같은 user를 찾아
/// 있으면 각 Professor 혹은 Student 객체 반환
/// </summary>
/// <param name="filename">student.csv와 professor.csv</param>
/// <param name="id"></param>
/// <param name="password"></param>
/// <returns>Professor 혹은 Student 객체 반환</returns>
User* rwcsv::UserLogin(const string& filename, const string& id, const string& password) {
    ifstream csvFile(filename);

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line);//헤더 건너뛰기

        while (getline(csvFile, line)) {

            stringstream ss(line); //한줄로 되어있는 것 string

            string _name; string _major; string _number;
            string _id; string _password; string _email;

            getline(ss, _name, ','); // name
            getline(ss, _major, ','); // major
            getline(ss, _number, ','); // number
            getline(ss, _id, ','); // id
            getline(ss, _password, ','); //passwor
            getline(ss, _email, ','); //email

            int number = stoi(_number); // string -> int 변환

            if (id == _id && password == _password) {
                if (filename == "student.csv") {
                    return new Student(_name, _major, number, _id, _password, _email);
                }
                else
                {
                    return new Professor(_name, _major, number, _id, _password, _email);
                }
            }
        }
        cout <<"로그인에 실패했습니다." << endl;
    }
}

/// <summary>
/// 받은 filename를 열어 user data를 저장하는 함수
/// </summary>
/// <param name="filename"></param>
/// <param name="user"></param>
void rwcsv::SaveUserDataSCV(const string& filename, User& user) {

    //append 모드로 파일을 연다
    ofstream csvfile(filename, ios::app);
    if (csvfile.is_open()) {
        csvfile << user.getName() << "," << user.getMajor() << ","
            << user.getName() << "," << user.getId() << ","
            << user.getPassword() << "," << user.getEmail() << "\n";
        csvfile.close();
    }
    else
    {
        cerr << "파일을 찾을 수 없습니다." << endl;
    }
}
