#include "rwcsv.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iomanip>

using namespace std;

/// <summary>
/// �����̸����� id�� password�� ���� user�� ã��
/// ������ �� Professor Ȥ�� Student ��ü ��ȯ
/// </summary>
/// <param name="filename">student.csv�� professor.csv</param>
/// <param name="id"></param>
/// <param name="password"></param>
/// <returns>Professor Ȥ�� Student ��ü ��ȯ</returns>
User* rwcsv::UserLogin(const string& filename, const string& id, const string& password) {
    ifstream csvFile(filename);

    if (!csvFile.is_open()) {
        cout << "������ �� �� �����ϴ�: " << filename << endl;
        return nullptr; // ������ ������ ������ nullptr ��ȯ
    }

    string line;
    getline(csvFile, line); // ��� �ǳʶٱ�

    while (getline(csvFile, line)) {
        stringstream ss(line); // �� �ٷ� �Ǿ� �ִ� ���� stringstream���� ó��

        string _name, _major, _number;
        string _id, _password, _email;

        getline(ss, _name, ',');    // name
        getline(ss, _major, ',');   // major
        getline(ss, _number, ',');  // number
        getline(ss, _id, ',');      // id
        getline(ss, _password, ','); // password
        getline(ss, _email, ',');   // email

        int number = stoi(_number); // string -> int ��ȯ

        if (id == _id && password == _password) {
            csvFile.close(); // ���� �ݱ�
            if (filename == "student.csv") {
                return new Student(_name, _major, number, _id, _password, _email);
            }
            else {
                return new Professor(_name, _major, number, _id, _password, _email);
            }
        }
    }

    csvFile.close(); // ���� �ݱ�
    cout << "�α��ο� �����߽��ϴ�." << endl;
    return nullptr; // �α��� ���� �� nullptr ��ȯ
}

/// <summary>
/// student�� professor�� �Է��ϸ�
/// �� �ش�Ǵ� .csv�� �о vector�� ��ȯ��.
/// </summary>
/// <param name="user">student�� professor�� �ϳ��� ���� �Է¹���.</param>
/// <returns></returns>
vector<User*> rwcsv::ReadUserCSV(const string& user) {
    string filename = user + ".csv";
    ifstream csvFile(filename);

    vector<User*> users; // ��ȯ�� User ������ ����

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // ��� �ǳʶٱ�

        while (getline(csvFile, line)) {
            stringstream ss(line);

            string name, major, numberStr, id, password, email;
            getline(ss, name, ',');     // �̸�
            getline(ss, major, ',');    // ����
            getline(ss, numberStr, ','); // �й� (���ڿ��� �б�)
            getline(ss, id, ',');       // ���̵�
            getline(ss, password, ','); // ��й�ȣ
            getline(ss, email, ',');    // �̸���

            int number = stoi(numberStr); // �й��� ������ ��ȯ

            // ���ҿ� ���� Student �Ǵ� Professor ��ü ����
            if (user == "student") {
                users.push_back(new Student(name, major, number, id, password, email));
            }
            else if (user == "professor") {
                users.push_back(new Professor(name, major, number, id, password, email));
            }
        }

        csvFile.close();
    }
    else {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
    }

    return users;
}
/// <summary>
/// user�� �̸��� �޾� user�� csv ������ �ܼ�â ����ϴ� �Լ�.
/// </summary>
/// <param name="printuser">professor Ȥ�� student</param>
void rwcsv::PrintUserCSV(const string& printuser) {
    // ��� ���
    cout << "=================================================================" << endl;
    cout << "|                            "<< printuser <<"                            |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num      | Name            | Major               | Number     |" << endl;
    cout << "=================================================================" << endl;

    vector<User*> uservector = this->ReadUserCSV(printuser);
    
    int numbering = 0;
    // �� User ������ ���
    for (const User* user : uservector) {
        numbering += 1;
        // ����� ���� ���
        cout << "| " << setw(10) << left << numbering
            << "| " << setw(15) << left << user->getName()
            << "| " << setw(20) << left << user->getMajor()
            << "| " << setw(11) << left << user->getNumber()
            << "|" << endl;
    }
    // �� User ������ ���
    

    // ���̺� �ϴ� ���
    cout << "=================================================================" << endl;
}
/// <summary>
/// ���� filename�� ���� user data�� �����ϴ� �Լ�
/// </summary>
/// <param name="filename"></param>
/// <param name="user"></param>
void rwcsv::AddUserDataCSV(const string& filename, User& user) {

    //append ���� ������ ����
    ofstream csvfile(filename, ios::app);
    if (csvfile.is_open()) {
        csvfile << user.getName() << "," << user.getMajor() << ","
            << user.getName() << "," << user.getId() << ","
            << user.getPassword() << "," << user.getEmail() << "\n";
        csvfile.close();
    }
    else
    {
        cerr << "������ ã�� �� �����ϴ�." << endl;
    }
}

void rwcsv::AddSubjectDataCSV(string subjectname, int professornum, vector<int> studentnums) {

    //append ���� ������ ����
    ofstream csvfile("subjectList.csv", ios::app);
    if (csvfile.is_open()) {
        csvfile << subjectname << "," << professornum << ",";
        for (int i = 0; i < studentnums.size(); i++)
        {
            // �������̸� \n�� �߰���.
            if (i == studentnums.size() - 1) {
                csvfile << studentnums[i] << endl;
            }
            else {
                csvfile << studentnums[i] << ",";
            }
        }
        cout << "���������� �����Ͽ����ϴ�." << endl;
    }
    else
    {
        cerr << "������ ã�� �� �����ϴ�." << endl;
    }
}

