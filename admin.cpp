#include <iostream>
#include <windows.h>
#include <vector>
#include "admin.h"
#include "Student.h"
#include "Professor.h"
#include "rwcsv.h"

using namespace std;
/// <summary>
/// admin으로 로그인 시 나오는 main 콘솔
/// </summary>
void admin::adminMain() {
    int num;
    while (true) {

        cout << "========================================================" << endl;
        cout << "관리자 모드로 접속 중입니다.\n" << endl;
        cout << "1. 교수 등록 " <<"2. 학생 등록 " << "3. 교과목 관리 " << "4.  종료" << endl;
        cout << ">> 입력: ";
        cin >> num;
            if (num == 1) {
                string role = "professor";
                addUser(role);
            }
            else if (num == 2) {
                string role = "student";
                addUser(role);
            }
            else if (num == 3) {
                this->adminSubjectManaging();
            }
            else if (num == 4) {
                break;
            }
            else {
                cout << "다시 입력해주세요. " << endl;
            }
    }
}

/// <summary>
/// admin이 교과목을 관리하는 main 콘솔 화면
/// </summary>
void admin::adminSubjectManaging() {
    int num;
    while (true) {
        system("cls");
        cout << "========================================================" << endl;
        cout << "1. 교과목 추가 " << "2. 교과목 삭제 " << "3. 뒤로가기" << endl;
        cout << ">> 입력: ";
        cin >> num;
        if (num == 1) {
            this->addSubject();
        }
        else if (num == 2) {
            this->deletSubject();
           
        }
        else if (num == 3) {
            this->adminMain();
        }
    }
}

/// <summary>
/// 과목명과 교번 및 학번을 입력받아 subjectList.csv에 저장하고
/// 교과목.csv를 만드는 함수 adminSubjectManaging()에서 교과목 추가 시
/// 실행되는 함수
/// </summary>
void admin::addSubject() {
    // 추가할 과목명을 입력받음.
    // 추가할 과목명을 입력받음.
    string subjectName;
    cout << "추가하실 과목명을 입력해주세요할 과목명을 입력해주세요. (ex. ex001 )" << endl;
    string subjectname;
    cout << ">> 입력: ";
    cin >> subjectname;
    cout << "=================================================================" << endl;
    cout << "정말 삭제하시겠습니까? (y/n)" << endl;
    string yorn;
    cin >> yorn;
    
    if (yorn == "y") {
        rwcsv().RemoveSubjectCSVFile(subjectname);
        rwcsv().RemoveSubjectDataCSV(subjectname);
        rwcsv().RemoveSubjectFromStudents(subjectname);
        this->adminMain();
    }
}

/// <summary>
/// 사용자 정보를 입력 받아서, csv에 저장하는 함수
/// </summary>
/// <param name="role">csv 파일 경로</param>
void admin::addUser(string role) {
    system("cls");
    string csv = role + ".csv";
    cout << "=================================================================" << endl;
    cout << csv << "에 " << "저장합니다." << endl;

    string name;
    string major;
    int number;
    string email;

    cout << "이름을 입력해주세요: ";
    cin >> name;
    
    cout << "전공을 입력해주세요: ";
    cin >> major;
    if (role == "student")
        cout << "학번을 입력해주세요: ";
    else
        cout << "교번을 입력해주세요: ";
    cin >> number;

    cout << "이메일을 입력해주세요: ";
    cin >> email;

    string id = to_string(number);
    string password = to_string(number) + "@";

    if (csv == "professor.csv") {
        Professor pro = Professor(name, major, number, id , password, email);
        rwcsv().AddUserDataCSV(csv, pro);
    }
    else if(csv == "student.csv")
    {
        Student stu = Student(name, major, number, id, password, email);
        rwcsv().AddUserDataCSV(csv, stu);
    }
}
