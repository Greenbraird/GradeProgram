#define NOMINMAX
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

        cout << "===============================================================" << endl;
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
/// amdin이 교과목를 관리하는 main 콘솔 화면
/// </summary>
void admin::adminSubjectManaging() {
    int num;
    while (true) {
        system("cls");
        cout << "===============================================================" << endl;
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
            break;
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
    cout << "추가하실 과목명을 입력해주세요." << endl;
    cout << ">> 입력: ";
    cin >> subjectName;

    // 과목명을 중복 확인 후 조정
    subjectName = rwcsv().adjustSubjectName(subjectName);
    cout << "확정된 과목명: " << subjectName << endl;

    vector<User*> professordata = rwcsv().ReadUserCSV("professor");

    // professor.csv 파일에 있는 교수의 내용을 콘솔 창에 출력
    rwcsv().PrintUserCSV("professor");
    cout << "과목에 배정할 교수님의 교번을 선택해 주세요. (ex. 2001)" << endl;
    

    // 교수의 교번을 입력받고 없으면 계속 입력 받음
    int professornum = 0;
    while (true) {
        cout << ">> 입력: ";
        cin >> professornum;

        bool flag = false;

        for (User* professor : professordata)
        {
            if (professor->getNumber() == professornum) {
                cout << professor->getName() << "님을 " << subjectName << "에 배정하겠습니다." << endl;
                flag = true;
                break;
            }
        }

        if (!flag) {
            cout << "입력하신 교번에 교수님이 없습니다. 다시 입력해주세요." << endl;
        }
        else
        {
            break;
        }

    }

    // student.csv 파일에 있는 교수의 내용을 콘솔 창에 출력
    rwcsv().PrintUserCSV("student");
    cout << "과목에 수강할 학생의 학번을 선택해 주세요. (ex. 20214778)" << endl;
    cout << ">> 입력(완료되면 -1를 입력해주세요.): " ;

    vector<User*> studentdata = rwcsv().ReadUserCSV("student");

    // 학생의 학번을 입력받고 -1를 입력시 완료로 반정
    int studentnum = 0;
    // 학생은 한명만 입력 받는 것이 아니기 때문에 vector에 학생 학번 저장
    vector <int> studentnumVector;
    vector <string> studnetnameVector;
    while (studentnum != -1) {
        cin >> studentnum;

        bool flag = false;

        for (User* student : studentdata)
        {
            if (student->getNumber() == studentnum) {
                cout << student->getName() << "님을 " << subjectName << "에 배정하겠습니다." << endl;
                studentnumVector.push_back(studentnum);
                studnetnameVector.push_back(student->getName());
                flag = true;
                break;
            }
            else if (studentnum == -1)
            {
               break;
            }
        }
        if (!flag && !(studentnum == -1)) {
            cout << "입력하신 학번에 해당하는 학생이 없습니다. 다시 입력해주세요." << endl;
        }

    }

    cout << subjectName << "에 " << professornum << "교번 교수님과 ";
    for (int number : studentnumVector) {
        cout << number << ", ";
    }

    cout << "들을 배정합니다." << endl;

    //subjectList.csv에 과목 추가
    rwcsv().AddSubjectDataCSV(subjectName, professornum);
    // 과목명.csv이름으로 새로운 csv 파일 생성 후 header로 학번 저장
    rwcsv().MakeSubjectCSVFile(subjectName, studnetnameVector,studentnumVector);
    // studentsSubjects.csv를 열어 각 학생에게 과목 배당
    rwcsv().AddSubjectToStudent(subjectName, studentnumVector);
    this->adminMain();
}

/// <summary>
/// 교과목명을 입력 받아 그에 대한 data를 삭제하는 함수
/// adminSubjectManaging()에서 교과목 삭제 시
/// 실행되는 함수
/// </summary>
void admin::deletSubject() {
    //과목 list를 print하는 함수가 필요 할 듯 함.
    system("cls");
    rwcsv().PrintSubjectList();
    cout << "삭제하실 과목명을 입력해주세요. (ex. ex001 )" << endl;
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
#include <limits> // 유효성 검사를 위해 필요

void admin::addUser(string role) {
    system("cls");
    string csv = role + ".csv";
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

    while (true) {
        if (role == "student")
            cout << "학번을 입력해주세요: ";
        else
            cout << "교번을 입력해주세요: ";

        cin >> number;

        // 유효성 검사: 입력 실패 여부 확인
        if (cin.fail()) {
            cin.clear(); // 스트림 상태 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
            cout << "잘못된 입력입니다. 숫자를 입력해주세요.\n";
        }
        // 유효성 검사: 범위 확인
        else if (number < 1000 || number > 99999999) { // 예: 4~8자리 숫자로 제한
            cout << "유효한 범위의 숫자를 입력해주세요 (예: 1000 ~ 99999999).\n";
        }
        else {
            break; // 올바른 입력
        }
    }

    cout << "이메일을 입력해주세요: ";
    cin >> email;

    string id = to_string(number);
    string password = "pass" + to_string(number);

    if (csv == "professor.csv") {
        Professor pro = Professor(name, major, number, id, password, email);
        rwcsv().AddUserDataCSV(csv, pro);
    }
    else if (csv == "student.csv") {
        Student stu = Student(name, major, number, id, password, email);
        rwcsv().AddUserDataCSV(csv, stu);
    }

}
