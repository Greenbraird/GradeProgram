#include "student.h"
#include "rwcsv.h"

#include <iostream>
#include <windows.h>

void Student::main() const{
    
    while (true) {
        system("cls");
        cout << "=================================================================\n";
        cout << this->getName() << " 학생 환영합니다." << endl << endl;
        cout << "=================================================================\n";

        //for (auto i : mysubjects) {
        //    cout << i << endl;
        //}
        vector<string> mysubjects = rwcsv().PrintStudentSubject("studentsSubjects.csv", this->getName());

        cout << "1. 전체성적조회   2. 특정 과목 성적조회   3. 종료\n";
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



