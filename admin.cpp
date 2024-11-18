#include <iostream>
#include <windows.h>
#include "admin.h"
#include "Student.h"
#include "Professor.h"
#include "rwcsv.h"

using namespace std;
/// <summary>
/// admin���� �α��� �� ������ main �ܼ�
/// </summary>
void admin::adminMain() {
    int num;
    while (true) {
        system("cls");
        cout << "===============================================================" << endl;
        cout << "1. ���� ��� " <<"2. �л� ��� " << "3. ������ ���� " << "4. ����" << endl;
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
        cout << "1. ������ �߰� " << "2. ������ ���� " << "3. �ڷΰ���" << endl;
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
    cout << "�߰��Ͻ� ������� �Է����ּ���." << endl;
    cin >> subjectName;
    rwcsv().PrintUserCSV("professor");
    cout << "���� ������ �������� ������ ������ �ּ���. (ex. 1002)" << endl;
    int professornum;
    cin >> professornum;

}

/// <summary>
/// ����� ������ �Է� �޾Ƽ�, csv�� �����ϴ� �Լ�
/// </summary>
/// <param name="role">csv ���� ���</param>
void admin::addUser(string csv) {
    system("cls");
    cout << "===============================================================" << endl;
    cout << csv << "�� " << "�����մϴ�." << endl;

    string name;
    string major;
    int number;
    string email;

    cout << "�̸��� �Է����ּ���: ";
    cin >> name;
    
    cout << "������ �Է����ּ���: ";
    cin >> major;

    cout << "�й��� �Է����ּ���: ";
    cin >> number;

    cout << "�̸����� �Է����ּ���: ";
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
