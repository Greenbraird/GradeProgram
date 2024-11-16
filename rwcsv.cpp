#include "rwcsv.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line);//��� �ǳʶٱ�

        while (getline(csvFile, line)) {

            stringstream ss(line); //���ٷ� �Ǿ��ִ� �� string

            string _name; string _major; string _number;
            string _id; string _password; string _email;

            getline(ss, _name, ','); // name
            getline(ss, _major, ','); // major
            getline(ss, _number, ','); // number
            getline(ss, _id, ','); // id
            getline(ss, _password, ','); //passwor
            getline(ss, _email, ','); //email

            int number = stoi(_number); // string -> int ��ȯ

            if (id == _id && password == _password) {
                if (filename == "student.csv") {
                    return new Student(_name, _major, number, _id, _password, _email);
                }
                else
                {
                    return new Professor(_name, _major, number, _id, _password, _email);
                }
            }
        }
        cout <<"�α��ο� �����߽��ϴ�." << endl;
    }
}

/// <summary>
/// ���� filename�� ���� user data�� �����ϴ� �Լ�
/// </summary>
/// <param name="filename"></param>
/// <param name="user"></param>
void rwcsv::SaveUserDataSCV(const string& filename, User& user) {

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
