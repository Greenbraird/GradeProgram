#include "student.h"
#include "rwcsv.h"

#include <iostream>
#include <windows.h>

void Student::main() const{

    cout << this->getNumber() << this->getNumber() << "�� �α��� �Ǿ����ϴ�." << endl;

    while (true) {
        system("cls");
        //Student = �α��� �� ������ ������ ��ü �����
        //���� list ����ϴ� �Լ�
        //rwscv���� readsubject(�̸� �ֱ�)�� ����� �� ��

        vector<string> mysubjects = rwcsv().PrintStudentSubject("studentsSubjects.csv", this->getName());

        cout << "1. ��ü������ȸ   2. Ư�� ������ȸ   3. ����\n";
        cout << ">> �Է�: ";
        int num;
        cin >> num;

        if (num == 1) {
            rwcsv().PrintALLStudentGrade(mysubjects, this->getName());
        }
        else if (num == 2) {
            string subjectName;
            //��ü ���� ��°� Ư�� ���� ���� ���
            cout << "��ȸ �� ���� ������� �Է����ּ���." << endl;
            cout << ">> �����: ";
            cin >> subjectName;
            rwcsv().PrintStudentGrade(subjectName, this->getName());
        }
    }
}



