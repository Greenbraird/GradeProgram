#define NOMINMAX
#include "student.h"
#include "rwcsv.h"

#include <iostream>
#include <windows.h>


void Student::main() const {
    system("cls");
    while (true) {
        cout << "=================================================================\n";
        cout << this->getName() << " �л� ȯ���մϴ�." << endl << endl;
        cout << "=================================================================\n";

        //for (auto i : mysubjects) {
        //    cout << i << endl;
        //}
        vector<string> mysubjects = rwcsv().PrintStudentSubject("studentsSubjects.csv", this->getName());

        int num;
        while (true) {
            cout << "1. ��ü������ȸ   2. Ư�� ���� ������ȸ   3. ���α׷� ����\n";
            cout << ">> �Է�: ";
            cin >> num;

            if (cin.fail() || (num < 1 || num > 3)) {
                cin.clear(); // ��Ʈ�� ���� �ʱ�ȭ
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
                cout << "�߸��� �Է��Դϴ�. 1, 2, 3 �� �ϳ��� �������ּ���.\n";
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
            //��ü ���� ��°� Ư�� ���� ���� ���
            cout << "��ȸ �� ���� ������� �Է����ּ���." << endl;
            cout << ">> �����: ";
            cin >> subjectName;
            rwcsv().PrintStudentGrade(subjectName, this->getName());
        }
        else if (num == 3) {
            exit(0);
        }
    }
}