#include "student.h"
#include "rwcsv.h"

#include <iostream>
#include <windows.h>

void Student::main() const{

    cout << this->getNumber() << this->getNumber() << "로 로그인 되었습니다." << endl;

    
    while (true) {
        system("cls");

        //for (auto i : mysubjects) {
        //    cout << i << endl;
        //}
        vector<string> mysubjects = rwcsv().PrintStudentSubject("studentsSubjects.csv", this->getName());

        cout << "1. 전과목 성적조회   2. 특정 과목 성적조회   3. 종료\n";
        cout << ">> 입력: ";
        int num;
        cin >> num;

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
            break;
        }
    }
}
