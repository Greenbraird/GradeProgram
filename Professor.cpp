#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Professor.h"

using namespace std;

// ����ü ����: �л� CSV ������ ����
struct Student {
    string name;
    string number;
};

// ����ü ����: ���� CSV ������ ����
struct Professor {
    string name;
    string subject;
};



/* 3.1. ���� ���� */
// ���� filename(csv ����) ��θ� �޾�, ���� �� �����͸� professor ��ü�� ����
vector<Professor> readCSV(const string& filename) {
    vector<Professor> professors;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return professors;
    }

    // ù ��° ������ �ǳʶ�
    string line;
    getline(file, line);

    // ���� �� ���ڿ� ������ ó��, ������ �����͸� ���ڿ� ������ ����
    while (getline(file, line)) {
        stringstream ss(line);
        string name, subject;

        // ','�� �и�
        getline(ss, name, ',');
        getline(ss, subject, ',');

        // ���� ������ ����
        professors.push_back({ name, subject });
    }

    file.close();
    return professors;
}

// �Էµ� �̸��� �ش��ϴ� ���� ��� �Լ�
void displaySubjects(const vector<Professor>& professors, const string& targetName) {
    int count = 0;

    for (const auto& professor : professors) {
        if (professor.name == targetName) {
            cout << ++count << ". " << professor.subject << endl;
        }
    }

    if (count == 0) {
        cout << targetName << "�� �ش��ϴ� ������ �����ϴ�." << endl;
    }
}
// �Էµ� ������ �ƴ϶� �α��� ������ �������� ������ ����ؾ��� //
// �α����� ������ ���� ��������� �����ؾ���//




/* 3.2. ���׸� ���� */

// CSV ���� �б�
vector<Student> readCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return students;
    }

    string line;
    // ����� �ǳʶٱ�
    getline(file, line);

    // ������ �б�
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number;

        // ','�� �и��Ͽ� ������ �б�
        getline(ss, name, ',');
        getline(ss, number, ',');

        // ����ü�� ������ ����
        students.push_back({ name, number });
    }

    file.close();
    return students;
}

// CSV ���� ���� �Լ�
void writeCSV(const string& filename, const vector<Student>& students, const string& newColumn) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return;
    }

    // ��� ����
    file << "name,number," << newColumn << endl;

    // ������ ����
    for (const auto& student : students) {
        file << student.name << "," << student.number << ",0" << endl; // �� ���� �⺻�� 0
    }

    file.close();
}



void createAssignment() {
    string filename = "subjectCalculus.csv"; // �ӽ÷� �س��� ��... ����ڰ� ������ ������ ���� ������ ������

    // CSV ���� �б�
    vector<Student> students = readCSV(filename);
    if (students.empty()) {
        cerr << "CSV ���Ͽ��� �����͸� ���� ���߽��ϴ�." << endl;
        return;
    }

    cout << "�߰��� ���׸� �̸��� �Է��ϼ���: ";
    string newColumn;
    cin >> newColumn;

    // �� �� �߰�
    writeCSV(filename, students, newColumn);

    cout << "CSV ������ ���������� �����Ǿ����ϴ�: " << filename << endl;
}







void Professor::main() const
{
    string whichSubject;
    int profMode;

    while (true) {
        system("cls");
        cout << "=======================�� ���ǽ�=======================\n";
        // 3.1. ���� ���� : ���� ����Ʈ ���/����� �Է�
        // �������� �Ҵ�� ������ subject.csv���� �ҷ�����. �̸� ���� subject.csv���� name, subject �������� ����Ǿ��ִ� ����
        string profName = ; //�α��� �������� ���� �̸� ������ ���� �����ؾ� ��
        string filename = "professor.csv";
        vector<Professor> professors = readCSV(filename);

        if (professors.empty()) {
            cerr << "CSV �����͸� �д� �� �����߽��ϴ�." << endl;
            return 1;
        }

        cout << "������ ���ǽ��� �����ϼ���." << endl;
        displaySubjects(professors, profName);

        cin >> whichSubject;
        if (whichSubject == ) {
            system("cls");
            string csv = ? ? ; //���� �־ �����ؾ� �ϳ�...
            // �� ���� csv�� �̵�
        }

        cout << "1. ���׸� ���� " << "2. ���� �Է� " << endl;
        cin >> profMode;
        if (profMode == 1) {
            createAssignment();
        }
        else if (profMode == 2) {
            // ���� �Է� �Լ� ����
        }
        return 0;
    }
}
