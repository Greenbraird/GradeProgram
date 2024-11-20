#include "rwcsv.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iomanip>

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

    if (!csvFile.is_open()) {
        cout << "파일을 열 수 없습니다: " << filename << endl;
        return nullptr; // 파일이 열리지 않으면 nullptr 반환
    }

    string line;
    getline(csvFile, line); // 헤더 건너뛰기

    while (getline(csvFile, line)) {
        stringstream ss(line); // 한 줄로 되어 있는 것을 stringstream으로 처리

        string _name, _major, _number;
        string _id, _password, _email;

        getline(ss, _name, ',');    // name
        getline(ss, _major, ',');   // major
        getline(ss, _number, ',');  // number
        getline(ss, _id, ',');      // id
        getline(ss, _password, ','); // password
        getline(ss, _email, ',');   // email

        int number = stoi(_number); // string -> int 변환

        if (id == _id && password == _password) {
            csvFile.close(); // 파일 닫기
            if (filename == "student.csv") {
                return new Student(_name, _major, number, _id, _password, _email);
            }
            else {
                return new Professor(_name, _major, number, _id, _password, _email);
            }
        }
    }

    csvFile.close(); // 파일 닫기
    cout << "로그인에 실패했습니다." << endl;
    return nullptr; // 로그인 실패 시 nullptr 반환
}

/// <summary>
/// student나 professor를 입력하면
/// 각 해당되는 .csv를 읽어서 vector로 반환함.
/// </summary>
/// <param name="user">student나 professor중 하나의 값을 입력받음.</param>
/// <returns></returns>
vector<User*> rwcsv::ReadUserCSV(const string& user) {
    string filename = user + ".csv";
    ifstream csvFile(filename);

    vector<User*> users; // 반환할 User 포인터 벡터

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // 헤더 건너뛰기

        while (getline(csvFile, line)) {
            stringstream ss(line);

            string name, major, numberStr, id, password, email;
            getline(ss, name, ',');     // 이름
            getline(ss, major, ',');    // 전공
            getline(ss, numberStr, ','); // 학번 (문자열로 읽기)
            getline(ss, id, ',');       // 아이디
            getline(ss, password, ','); // 비밀번호
            getline(ss, email, ',');    // 이메일

            int number = stoi(numberStr); // 학번을 정수로 변환

            // 역할에 따라 Student 또는 Professor 객체 생성
            if (user == "student") {
                users.push_back(new Student(name, major, number, id, password, email));
            }
            else if (user == "professor") {
                users.push_back(new Professor(name, major, number, id, password, email));
            }
        }

        csvFile.close();
    }
    else {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
    }

    return users;
}
/// <summary>
/// user의 이름을 받아 user의 csv 내용을 콘솔창 출력하는 함수.
/// </summary>
/// <param name="printuser">professor 혹은 student</param>
void rwcsv::PrintUserCSV(const string& printuser) {
    // 헤더 출력
    cout << "=================================================================" << endl;
    cout << "|                            "<< printuser <<"                            |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num      | Name            | Major               | Number     |" << endl;
    cout << "=================================================================" << endl;

    vector<User*> uservector = this->ReadUserCSV(printuser);
    
    int numbering = 0;
    // 각 User 정보를 출력
    for (const User* user : uservector) {
        numbering += 1;
        // 사용자 정보 출력
        cout << "| " << setw(10) << left << numbering
            << "| " << setw(15) << left << user->getName()
            << "| " << setw(20) << left << user->getMajor()
            << "| " << setw(11) << left << user->getNumber()
            << "|" << endl;
    }
    // 각 User 정보를 출력
    

    // 테이블 하단 장식
    cout << "=================================================================" << endl;
}
/// <summary>
/// 받은 filename를 열어 user data를 저장하는 함수
/// </summary>
/// <param name="filename"></param>
/// <param name="user"></param>
void rwcsv::AddUserDataCSV(const string& filename, User& user) {

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

void rwcsv::AddSubjectDataCSV(string subjectname, int professornum, vector<int> studentnums) {

    //append 모드로 파일을 연다
    ofstream csvfile("subjectList.csv", ios::app);
    if (csvfile.is_open()) {
        csvfile << subjectname << "," << professornum << ",";
        for (int i = 0; i < studentnums.size(); i++)
        {
            // 마지막이면 \n를 추가함.
            if (i == studentnums.size() - 1) {
                csvfile << studentnums[i] << endl;
            }
            else {
                csvfile << studentnums[i] << ",";
            }
        }
        cout << "성공적으로 저장하였습니다." << endl;
    }
    else
    {
        cerr << "파일을 찾을 수 없습니다." << endl;
    }
}

