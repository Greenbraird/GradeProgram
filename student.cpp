#define NOMINMAX
#include "student.h"
#include "rwcsv.h"

#include <iostream>
#include <windows.h>


void Student::main() const {
    system("cls");
    while (true) {
        cout << "=================================================================\n";
        cout << this->getName() << " 학생 환영합니다." << endl << endl;
        cout << "=================================================================\n";

        //for (auto i : mysubjects) {
        //    cout << i << endl;
        //}
        vector<string> mysubjects = rwcsv().PrintStudentSubject("studentsSubjects.csv", this->getName());

        int num;
        while (true) {
            cout << "1. 전체성적조회   2. 특정 과목 성적조회   3. 프로그램 종료\n";
            cout << ">> 입력: ";
            cin >> num;

            if (cin.fail() || (num < 1 || num > 3)) {
                cin.clear(); // 스트림 상태 초기화
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
                cout << "잘못된 입력입니다. 1, 2, 3 중 하나를 선택해주세요.\n";
            }
            else {
                break;
            }
        }
        

        if (num == 1) {
            rwcsv().PrintALLStudentGrade(mysubjects, this->getName());
        }
        else if (num == 2) {
            string subjectName;
            //전체 성적 출력과 특정 과목 성적 출력
            cout << "조회 할 성적 과목명을 입력해주세요." << endl;
            cout << ">> 과목명: ";
            cin >> subjectName;
            rwcsv().PrintStudentGrade(subjectName, this->getName());
        }
        else if (num == 3) {
            exit(0);
        }
    }
}