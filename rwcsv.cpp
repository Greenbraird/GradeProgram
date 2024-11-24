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

void rwcsv::deletSubjectCSV(const string& subjectname) {
    string filename = "subjectList.csv";
    ifstream inputFile(filename);
    ofstream tempFile("temp.csv"); // 임시 파일 생성

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "파일 열기에 실패했습니다." << endl;
        return;
    }

    string line;
    bool found = false;

    // 헤더 복사
    if (getline(inputFile, line)) {
        tempFile << line << endl; // 헤더를 임시 파일로 복사
    }

    // 각 줄을 읽으면서 subjectname과 일치하지 않는 줄을 임시 파일로 복사
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string currentSubject;
        getline(ss, currentSubject, ','); // subject 이름 추출 (첫 번째 값)

        if (currentSubject != subjectname) {
            tempFile << line << endl; // 다른 이름은 그대로 복사
        }
        else {
            found = true; // 삭제 대상 발견
        }
    }

    inputFile.close();
    tempFile.close();

    // 삭제 완료 후 원본 파일을 임시 파일로 대체
    if (found) {
        if (remove(filename.c_str()) != 0 || rename("temp.csv", filename.c_str()) != 0) {
            cerr << "파일 처리 중 오류가 발생했습니다." << endl;
        }
        else {
            remove((subjectname + ".csv").c_str());
            cout << "과목 \"" << subjectname << "\"가 성공적으로 삭제되었습니다." << endl;
        }
    }
    else {
        remove("temp.csv"); // 임시 파일 삭제
        cout << "과목 \"" << subjectname << "\"를 찾을 수 없습니다." << endl;
    }
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
/// <summary>
/// 과목명과 교본, 학번들을 입력 받아 data들 subjectList.csv에 저장하는 함수
/// </summary>
/// <param name="subjectname">과목명</param>
/// <param name="professornum">당담교수 교번</param>
/// <param name="studentnums">수강하는 학생들 학번들</param>
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

void rwcsv::PrintSubjectList(const Professor& prof) {

    string filename = "subjectList.csv";
    ifstream csvFile(filename);

    cout << "=================================================================" << endl;
    cout << "|                         Subject List                          |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num     |  Subject             |        Professor Num         |" << endl;
    cout << "=================================================================" << endl;

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // 헤더 건너뛰기
        // cout numbering
        int numbering=0;
        // 교과목 이름
        string subject;
        //교번
        string professornum;

        while (getline(csvFile, line)) {
            stringstream ss(line);

            getline(ss, subject, ',');     // 이름
            getline(ss, professornum, ',');    // 교번

            numbering += 1;
            if (prof.getNumber() == stoi(professornum)) {
                cout << "| " << setw(8) << left << numbering
                    << "| " << setw(21) << left << subject
                    << "| " << setw(29) << left << professornum
                    << "|" << endl;
            }
        }
    }
    cout << "=================================================================" << endl;
}
void rwcsv::PrintSubjectList() {
    string filename = "subjectList.csv";
    ifstream csvFile(filename);

    cout << "=================================================================" << endl;
    cout << "|                         Subject List                          |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num     |  Subject             |        Professor Num         |" << endl;
    cout << "=================================================================" << endl;

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // 헤더 건너뛰기
        int numbering = 0;      // 출력 번호
        string subject, professornum;

        while (getline(csvFile, line)) {
            stringstream ss(line);
            getline(ss, subject, ',');      // 과목명
            getline(ss, professornum, ','); // 교번

            numbering++;
            cout << "| " << setw(8) << left << numbering
                << "| " << setw(21) << left << subject
                << "| " << setw(29) << left << professornum
                << "|" << endl;
        }
    }
    else {
        cerr << "Failed to open file: " << filename << endl;
    }
    cout << "=================================================================" << endl;
}

/// <summary>
/// 새로운 과목에 대한 새로운 .csv를 생성하고 거기에 학번들을 저장하는 함수
/// </summary>
/// <param name="subjectname">과목명, 과목명 + "csv"로 .csv 생성</param>
/// <param name="studentsnum">header로 들어갈 학번들</param>
void rwcsv::MakeSubjectCSV(string subjectname, vector<int> studentnums) {
    
    // 파일을 만들고
    string filename = subjectname + ".csv";
    
    ofstream csvfile(filename);
    // 거기에 header 할당(학생들의 학번)
    if (csvfile.is_open()) {
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
    }

    
}

