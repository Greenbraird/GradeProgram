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
                break;
            }
            else if (num == 4) {
                
            }
    }
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
        rwcsv().SaveUserDataSCV(csv, pro);
    }
    else if(csv == "student.csv")
    {
        Student stu = Student(name, major, number, id, password, email);
        rwcsv().SaveUserDataSCV(csv, stu);
    }
}
