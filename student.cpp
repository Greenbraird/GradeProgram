#include "student.h"

#include <iostream>
#include <windows.h>

void Student::main() const{
    while (true) {
        system("cls");
        //Student = 로그인 한 내용을 가지고 객체 만들기
        //과목 list 출력하는 함수
        //rwscv에섯 readsubject(이름 넣기)를 만들면 될 듯
        string name;
        cout << this-> getNumber() << this->getNumber() << "로 로그인 되었습니다." << endl;
        cout << "===============================================================" << endl;
        cout << "과목명을 입력해주세요." << endl;
        cin >> name;
        //과목명이 맞으면 평가 항목별로 성적 출력
    }
}