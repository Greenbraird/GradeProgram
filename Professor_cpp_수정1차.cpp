#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Professor.h"

using namespace std;

class Score {
public:
    float attendance;
    float midtermTest;
    float finalTest;
    float assignment;

    Score() : attendance(0), midtermTest(0), finalTest(0), assignment(0) {}
};

// Subject Ŭ���� ���� (Score ���) ++ ���� ������ ������ ��ӹ������ֵ��� �ؾ�
class Subject : public Score {
public:
    string name;
    Subject(const string& subjectName) : name(subjectName) {}
};




void displaySubjects(int professorNum) {
    ifstream file("subjectList.csv");
    if (!file.is_open()) {
        cout << "subjectList.csv ������ �� �� �����ϴ�." << endl;
        return;
    }
    string line;
    int count = 0;

    // ���Ͽ��� �� �پ� �б�
    while (getline(file, line)) {
        string subject;
        int num;

        // CSV ������ �� ���� ','�� �����Ͽ� �Ľ�
        stringstream ss(line);
        getline(ss, subject, ','); // subject �б�
        ss >> num; // professorNum �б�

        // �Է¹��� professorNum�� ��ġ�ϸ� ���
        if (num == professorNum) {
            cout << ++count << ". " << subject << endl;
        }
    }
    file.close();

    if (count == 0) {
        cout << professorNum << "�� �ش��ϴ� ������ �����ϴ�." << endl;
    }
}


void editSubject(const string& whichSubject) {
    string fileName = whichSubject + ".csv";

    fstream file(fileName, ios::in | ios::out);
    if (!file.is_open()) {
        cout << fileName << " ������ �� �� �����ϴ�." << endl;
        return;
    }

    void pointSetting(Subject & whichSubject) {
        cout << "����: " << whichSubject.name << endl;

        // ���� ����
        cout << "attendance�� % ������ �Է��ϼ���: ";
        cin >> whichSubject.attendance;

        cout << "midtermTest�� % ������ �Է��ϼ���: ";
        cin >> whichSubject.midtermTest;

        cout << "finalTest�� % ������ �Է��ϼ���: ";
        cin >> whichSubject.finalTest;

        cout << "assignment�� % ������ �Է��ϼ���: ";
        cin >> whichSubject.assignment;

        cout << endl;
        cout << "=======================���� ����=======================" << endl;
        cout << "Attendance: " << whichSubject.attendance << "%" << endl;
        cout << "Midterm Test: " << whichSubject.midtermTest << "%" << endl;
        cout << "Final Test: " << whichSubject.finalTest << "%" << endl;
        cout << "Assignment: " << whichSubject.assignment << "%" << endl;
    }





void Professor::main() const
{
    string whichSubject;
    int num;
    int professornum;

    while (true) {
        system("cls");

        // ���� ����Ʈ ��� : �������� �Ҵ�� ������ subjectList.csv���� �ҷ�����. �̸� ���� subjectList.csv���� '�����','������ȣ' �������� ����Ǿ��ִ� ����
        cout << "=======================�� ���ǽ�=======================\n";
        displaySubjects(professornum);

        cout << "������ ���ǽ��� �Է��ϼ���. (ex. ��ü�������α׷���)" << endl;
        cin >> whichSubject;
        editSubject(whichSubject);

        system("cls");
        cout << "1. ���׸� ���� ���� " << "2. ���� �Է� " << "3. ���� ���� " << endl;
        cin >> num;
        if (num == 1) {
            pointSetting(whichSubject);
            // int ���� point�� �����ص�. �ٵ� ���� ������� �ϴ°�?? ��������Ҷ�??
        }
        else if (num == 2) {

        }
        else if (num == 3) {

        }
        return 0;
    }
}
