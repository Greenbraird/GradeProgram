#include <iostream>
#include <windows.h>
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
        system("cls");
        cout << "===============================================================" << endl;
        cout << "1. 교수 등록 " <<"2. 학생 등록 " << "3. 교과목 관리 " << "4. 종료" << endl;
        cin >> num;
            if (num == 1) {
                string csv = "professor.csv";
                addUser(csv);
            }
            else if (num == 2) {
                string csv = "student.csv";
                addUser(csv);
            }
            else if (num == 3) {
                this->adminSubjectManaging();
            }
            else if (num == 4) {
                break;
            }
    }
}

/// <summary>
/// 
/// </summary>
void admin::adminSubjectManaging() {
    int num;
    while (true) {
        system("cls");
        cout << "===============================================================" << endl;
        cout << "1. 교과목 추가 " << "2. 교과목 삭제 " << "3. 뒤로가기" << endl;
        cin >> num;
        if (num == 1) {
            this->addSubject();
        }
        else if (num == 2) {
           
        }
        else if (num == 3) {
            this->adminMain();
        }
    }
}

void admin::addSubject() {
    string subjectName;
    cout << "추가하실 과목명을 입력해주세요." << endl;
    cin >> subjectName;
    rwcsv().PrintUserCSV("professor");
    cout << "과목에 배정할 교수님의 교번을 선택해 주세요. (ex. 1002)" << endl;
    int professornum;
    cin >> professornum;

}

/// <summary>
/// 사용자 정보를 입력 받아서, csv에 저장하는 함수
/// </summary>
/// <param name="role">csv 파일 경로</param>
void admin::addUser(string csv) {
    system("cls");
    cout << "===============================================================" << endl;
    cout << csv << "에 " << "저장합니다." << endl;

    string name;
    string major;
    int number;
    string email;

    cout << "이름을 입력해주세요: ";
    cin >> name;
    
    cout << "전공을 입력해주세요: ";
    cin >> major;

    cout << "학번을 입력해주세요: ";
    cin >> number;

    cout << "이메일을 입력해주세요: ";
    cin >> email;

    string id = to_string(number);
    string password = to_string(number) + "@";

    if (csv == "professor.csv") {
        Professor pro = Professor(name, major, number, id , password, email);
        rwcsv().SaveUserDataCSV(csv, pro);
    }
    else if(csv == "student.csv")
    {
        Student stu = Student(name, major, number, id, password, email);
        rwcsv().SaveUserDataCSV(csv, stu);
    }
}
