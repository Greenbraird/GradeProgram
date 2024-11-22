#include <iostream>
#include <windows.h>
#include <vector>
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
                
            }
            else {
                cout << "�ٽ� �Է����ּ���. " << endl;
            }
    }
}

/// <summary>
/// amdin�� ������ �����ϴ� main �ܼ� ȭ��
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
            this->deletSubject();
           
        }
        else if (num == 3) {
            this->adminMain();
        }
    }
}

/// <summary>
/// ������ ���� �� �й��� �Է¹޾� subjectList.csv�� �����ϰ�
/// ������.csv�� ����� �Լ� adminSubjectManaging()���� ������ �߰� ��
/// ����Ǵ� �Լ�
/// </summary>
void admin::addSubject() {
    system("cls");
    // �߰��� ������� �Է¹���.
    string subjectName;
    cout << "�߰��Ͻ� ������� �Է����ּ���." << endl;
    cin >> subjectName;

    // professor.csv ���Ͽ� �ִ� ������ ������ �ܼ� â�� ���
    rwcsv().PrintUserCSV("professor");
    cout << "���� ������ �������� ������ ������ �ּ���. (ex. 1002)" << endl;

    vector<User*> professordata = rwcsv().ReadUserCSV("professor");

    // ������ ������ �Է¹ް� ������ ��� �Է� ����
    int professornum = 0;
    while (professornum == 0) {

        cin >> professornum;

        bool flag = false;

        for (User* professor : professordata)
        {
            if (professor->getNumber() == professornum) {
                cout << professor->getName() << "���� " << subjectName << "�� �����ϰڽ��ϴ�.";
                break;
            }
        }
        if (!flag) {
            cout << "�Է��Ͻ� ������ �������� �����ϴ�. �ٽ� �Է����ּ���." << endl;
        }

    }

    // student.csv ���Ͽ� �ִ� ������ ������ �ܼ� â�� ���
    rwcsv().PrintUserCSV("student");
    cout << "���� ������ �л��� �й��� ������ �ּ���. (ex. 20214778)" << endl;
    cout << "(�Ϸ�Ǹ� -1�� �Է����ּ���.)" << endl;

    vector<User*> studentdata = rwcsv().ReadUserCSV("student");

    // �л��� �й��� �Է¹ް� -1�� �Է½� �Ϸ�� ����
    int studentnum = 0;
    // �л��� �Ѹ� �Է� �޴� ���� �ƴϱ� ������ vector�� �л� �й� ����
    vector <int> studentnumVector;
    while (studentnum != -1) {
        cin >> studentnum;

        bool flag = false;

        for (User* student : studentdata)
        {
            if (student->getNumber() == studentnum) {
                cout << student->getName() << "���� " << subjectName << "�� �����ϰڽ��ϴ�." << endl;
                studentnumVector.push_back(studentnum);
                flag = true;
                break;
            }
            else if (studentnum == -1)
            {
                cout << "���� ������ �Ϸ� �մϴ�." << endl;
                break;
            }
        }
        if (!flag && !(studentnum == -1)) {
            cout << "�Է��Ͻ� �й��� �ش��ϴ� �л��� �����ϴ�. �ٽ� �Է����ּ���." << endl;
        }

    }

    cout << subjectName << "�� " << professornum << "���� �����԰� ";
    for (int number : studentnumVector) {
        cout << number << ", ";
    }

    cout << "���� �����մϴ�." << endl;

    //subjectList.csv�� ���� �߰�
    rwcsv().AddSubjectDataCSV(subjectName, professornum, studentnumVector);
    // �����.csv�̸����� ���ο� csv ���� ���� �� header�� �й� ����
    rwcsv().MakeSubjectCSV(subjectName, studentnumVector);
}

/// <summary>
/// ��������� �Է� �޾� �׿� ���� data�� �����ϴ� �Լ�
/// adminSubjectManaging()���� ������ ���� ��
/// ����Ǵ� �Լ�
/// </summary>
void admin::deletSubject() {
    //���� list�� print�ϴ� �Լ��� �ʿ� �� �� ��.
    system("cls");
    rwcsv().PrintSubjectList();
    cout << "=================================================================" << endl;
    cout << "�����Ͻ� ������� �Է����ּ���. (ex. ex001 )" << endl;
    string subjectname;
    cin >> subjectname;
    cout << "=================================================================" << endl;
    cout << "���� �����Ͻðڽ��ϱ�? (y/n)" << endl;
    string yorn;
    cin >> yorn;
    
    if (yorn == "y") {
        rwcsv().deletSubjectCSV(subjectname);
    }
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
        rwcsv().AddUserDataCSV(csv, pro);
    }
    else if(csv == "student.csv")
    {
        Student stu = Student(name, major, number, id, password, email);
        rwcsv().AddUserDataCSV(csv, stu);
    }
}
