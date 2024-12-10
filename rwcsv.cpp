#include "rwcsv.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iomanip>

using namespace std;
#pragma region User�� ���õ� CSV ���� �� ���� �Լ�

// user data�� csv�� �����ϴ� �Լ�
void rwcsv::AddUserDataCSV(const string& filename, User& user) {

    //append ���� ������ ����
    ofstream csvfile(filename, ios::app);
    if (csvfile.is_open()) {
        csvfile << user.getName() << "," << user.getMajor() << ","
            << user.getNumber() << "," << user.getId() << ","
            << user.getPassword() << "," << user.getEmail() << "\n";
        csvfile.close();

        cout << "���������� �߰��� �Ϸ�Ǿ����ϴ�." << endl;
    }
    else
    {
        cerr << "������ ã�� �� �����ϴ�." << endl;
    }
}

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
    cout << "===========================================" << endl;
    cout << "|                " << printuser << "                |" << endl;
    cout << "===========================================" << endl;
    cout << "| Num      | Number     | Name            |" << endl;
    cout << "===========================================" << endl;

    vector<User*> uservector = this->ReadUserCSV(printuser);

    int numbering = 0;
    // �� User ������ ���
    for (const User* user : uservector) {
        numbering += 1;
        // ����� ���� ���
        cout << "| " << setw(10) << left << numbering
            << "| " << setw(11) << left << user->getNumber()
            << "| " << setw(15) << left << user->getName()
            << "|" << endl;
    }
    // �� User ������ ���


    // ���̺� �ϴ� ���
    cout << "===========================================" << endl;
}
#pragma endregion


#pragma region ���� ���� CSV ���� �� ���� �Լ�
void rwcsv::RemoveSubjectCSVFile(const string& subjectname) {
    string filename = "subjectList.csv";
    ifstream inputFile(filename);
    ofstream tempFile("temp.csv"); // �ӽ� ���� ����

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "���� ���⿡ �����߽��ϴ�." << endl;
        return;
    }

    string line;
    bool found = false;

    // ��� ����
    if (getline(inputFile, line)) {
        tempFile << line << endl; // ����� �ӽ� ���Ϸ� ����
    }

    // �� ���� �����鼭 subjectname�� ��ġ���� �ʴ� ���� �ӽ� ���Ϸ� ����
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string currentSubject;
        getline(ss, currentSubject, ','); // subject �̸� ���� (ù ��° ��)

        if (currentSubject != subjectname) {
            tempFile << line << endl; // �ٸ� �̸��� �״�� ����
        }
        else {
            found = true; // ���� ��� �߰�
        }
    }

    inputFile.close();
    tempFile.close();

    // ���� �Ϸ� �� ���� ������ �ӽ� ���Ϸ� ��ü
    if (found) {
        if (remove(filename.c_str()) != 0 || rename("temp.csv", filename.c_str()) != 0) {
            cerr << "���� ó�� �� ������ �߻��߽��ϴ�." << endl;
        }
        else {
            remove((subjectname + ".csv").c_str());
            cout << "���� \"" << subjectname << "\"�� ���������� �����Ǿ����ϴ�." << endl;
        }
    }
    else {
        remove("temp.csv"); // �ӽ� ���� ����
        cout << "���� \"" << subjectname << "\"�� ã�� �� �����ϴ�." << endl;
    }
}
/// <summary>
/// ������ ����, �й����� �Է� �޾� data�� subjectList.csv�� �����ϴ� �Լ�
/// </summary>
/// <param name="subjectname">�����</param>
/// <param name="professornum">��㱳�� ����</param>
/// <param name="studentnums">�����ϴ� �л��� �й���</param>
void rwcsv::AddSubjectDataCSV(string subjectname, int professornum) {

    //append ���� ������ ����
    ofstream csvfile("subjectList.csv", ios::app);
    if (csvfile.is_open()) {
        csvfile << endl << subjectname << "," << professornum;
        cout << "���������� �����Ͽ����ϴ�." << endl;
    }
    else
    {
        cerr << "������ ã�� �� �����ϴ�." << endl;
    }
}
void rwcsv::RemoveSubjectDataCSV(string subjectname) {
    ifstream csvfile("subjectList.csv"); // �б� ���� ������ ����
    if (!csvfile.is_open()) {
        cerr << "������ ã�� �� �����ϴ�." << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    // ���Ͽ��� �� �پ� �о�ͼ� lines ���Ϳ� ����
    while (getline(csvfile, line)) {
        stringstream ss(line);
        string subject;
        getline(ss, subject, ','); // ����� �б�

        // ������� ��ġ�ϸ� �ش� ���� ����
        if (subject == subjectname) {
            found = true;
            continue; // ��ġ�ϴ� ���� �Ѿ��
        }

        lines.push_back(line); // ��ġ���� �ʴ� ���� ���Ϳ� ����
    }

    csvfile.close();

    // ������� �߰ߵǾ��ٸ� ������ ����� ���� ���� ������ �����͸� �ݿ�
    if (found) {
        ofstream outfile("subjectList.csv", ios::trunc); // ����� ���
        if (!outfile.is_open()) {
            cerr << "������ �� �� �����ϴ�." << endl;
            return;
        }

        // ���� �����͸� ���Ͽ� �ٽ� ����
        for (const string& newLine : lines) {
            outfile << newLine << endl;
        }

        cout << "���������� ������ �����Ͽ����ϴ�." << endl;
    }
    else {
        cout << "�ش� ������ ã�� �� �����ϴ�." << endl;
    }
}

void rwcsv::MakeSubjectCSVFile(string subjectname, vector<string> studentNameVector, vector<int> studentNums) {
    // ���� �̸� ����
    string filename = subjectname + ".csv";

    // ���� ����
    ofstream csvfile(filename);

    // ���� ���� ���� ���� Ȯ��
    if (csvfile.is_open()) {
        // ��� �ۼ�
        csvfile << "studentname,studentnumber,attendance,midtermTest,finalTest,assignment\n";

        // �л� ���� ���
        for (size_t i = 0; i < studentNameVector.size(); ++i) {
            csvfile << studentNameVector[i] << "," // �̸�
                << studentNums[i] << ","     // �й�
                << "," << "," << "," << "\n"; // ������ �� ���·�
        }

        csvfile.close(); // ���� �ݱ�
        cout << "CSV ������ �����Ǿ����ϴ�: " << filename << endl;
    }
    else {
        cerr << "CSV ������ ������ �� �����ϴ�: " << filename << endl;
    }
}

void rwcsv::AddSubjectToStudent(const string& subjectToAdd, const vector<int>& studentNumbers) {
    ifstream infile("studentsSubjects.csv"); // ���� CSV ���� ����
    vector<string> fileLines; // ��ü ���� �����͸� ����
    bool changesMade = false; // ���� ���� Ȯ��

    // ���� ���� ���� ó��
    if (!infile.is_open()) {
        cerr << "������ �� �� �����ϴ�" << endl;
        return;
    }

    string line;
    // ù ��(���) ����
    if (getline(infile, line)) {
        fileLines.push_back(line);
    }

    // ������ ��(�л� ������) ó��
    while (getline(infile, line)) {
        stringstream lineStream(line);
        vector<string> row;
        string token;

        // �� ���� �о� ���Ϳ� ����
        while (getline(lineStream, token, ',')) {
            row.push_back(token);
        }

        // �й�(�� ��° ��) Ȯ��
        if (row.size() > 1) {
            int studentNumber = stoi(row[1]); // �й�
            // �л� ��ȣ�� vector�� ���Ե� ��� ���� �߰�
            if (find(studentNumbers.begin(), studentNumbers.end(), studentNumber) != studentNumbers.end()) {
                // ���� �߰�
                row.push_back(subjectToAdd);
                changesMade = true;
            }
        }

        // ����� �����͸� �ٽ� �� �ٷ� ����
        string updatedLine;
        for (size_t i = 0; i < row.size(); ++i) {
            updatedLine += row[i];
            if (i < row.size() - 1) updatedLine += ",";
        }
        fileLines.push_back(updatedLine);
    }

    infile.close(); // ���� �ݱ�

    // ���� ������ ������ ����
    if (!changesMade) {
        cout << "����� ������ �����ϴ�." << endl;
        return;
    }

    // ����� �����͸� ���Ͽ� �ٽ� ����
    ofstream outfile("studentsSubjects.csv");
    if (outfile.is_open()) {
        for (const string& line : fileLines) {
            outfile << line << "\n";
        }
        outfile.close();
        cout << "������ ���������� �߰��Ǿ����ϴ�." << endl;
    }
    else {
        cerr << "������ �� �� �����ϴ�" << endl;
    }
}
void rwcsv::RemoveSubjectFromStudents(const string& subjectToRemove) {
    ifstream infile("studentsSubjects.csv"); // ���� CSV ���� ����
    vector<string> fileLines; // ��ü ���� �����͸� ����
    bool changesMade = false; // ���� ���� Ȯ��

    // ���� ���� ���� ó��
    if (!infile.is_open()) {
        cerr << "������ �� �� �����ϴ�" << endl;
        return;
    }

    string line;
    // ù ��(���) ����
    if (getline(infile, line)) {
        fileLines.push_back(line);
    }

    // ������ ��(�л� ������) ó��
    while (getline(infile, line)) {
        stringstream lineStream(line);
        vector<string> row;
        string token;

        // �� ���� �о� ���Ϳ� ����
        while (getline(lineStream, token, ',')) {
            row.push_back(token);
        }

        // ����鿡�� ������ ������ �ִ��� Ȯ��
        if (row.size() > 2) { // ������ �ִ��� Ȯ��
            bool subjectRemoved = false;
            for (size_t i = 2; i < row.size(); ++i) {
                if (row[i] == subjectToRemove) {
                    // ������ �����ϰ� ������ ������ ������ ����
                    row.erase(row.begin() + i);
                    subjectRemoved = true;
                    changesMade = true;
                    break;
                }
            }

            // ���� ������ �̷�����ٸ� ������Ʈ�� ���� ���
            if (subjectRemoved) {
                string updatedLine;
                for (size_t i = 0; i < row.size(); ++i) {
                    updatedLine += row[i];
                    if (i < row.size() - 1) updatedLine += ",";
                }
                fileLines.push_back(updatedLine);
            }
            else {
                fileLines.push_back(line); // ������ ������ ���� ���� �״�� ����
            }
        }
    }

    infile.close(); // ���� �ݱ�

    // ���� ������ ������ ����
    if (!changesMade) {
        cout << "������ ������ �����ϴ�." << endl;
        return;
    }

    // ����� �����͸� ���Ͽ� �ٽ� ����
    ofstream outfile("studentsSubjects.csv");
    if (outfile.is_open()) {
        for (const string& line : fileLines) {
            outfile << line << "\n";
        }
        outfile.close();
        cout << "������ ���������� �����Ǿ����ϴ�." << endl;
    }
    else {
        cerr << "������ �� �� �����ϴ�" << endl;
    }
}
string rwcsv::adjustSubjectName(const string& subjectName) {
    string adjustedName;
    vector<string> existingSubjects; // �����ϴ� ������� ������ ����

    // subjectList.csv ���� �б�
    ifstream subjectFile("subjectList.csv");
    if (subjectFile.is_open()) {
        string line, subject;
        getline(subjectFile, line); // ��� �ǳʶٱ�

        // CSV ���Ͽ��� ����� �о ����
        while (getline(subjectFile, line)) {
            stringstream ss(line);
            getline(ss, subject, ','); // ����� �б�
            existingSubjects.push_back(subject);
        }
        subjectFile.close();
    }
    else {
        cerr << "subjectList.csv ������ �� �� �����ϴ�." << endl;
        return subjectName + "1��"; // �⺻������ "1��" �߰�
    }

    // "1��", "2��", ..., N���� ���������� Ȯ���Ͽ� ���� ��ȣ�� ã��
    int suffix = 1; // �� ��ȣ ����
    while (true) {
        adjustedName = subjectName + to_string(suffix) + "��";
        if (find(existingSubjects.begin(), existingSubjects.end(), adjustedName) == existingSubjects.end()) {
            break; // �ߺ����� �ʴ� ������� ã���� ����
        }
        suffix++; // ���� �� ��ȣ Ȯ��
    }

    return adjustedName;
}

#pragma endregion


#pragma region ���� ���� �ܼ� print �Լ�
vector<string> rwcsv::PrintSubjectList(const Professor& prof) {

    string filename = "subjectList.csv";
    ifstream csvFile(filename);

    vector<string> subjects;

    cout << "=================================================================" << endl;
    cout << "|                         Subject List                          |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num     |  Subject             |        Professor Num         |" << endl;
    cout << "=================================================================" << endl;

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // ��� �ǳʶٱ�
        // cout numbering
        int numbering = 0;
        // ������ �̸�
        string subject;
        //����
        string professornum;

        while (getline(csvFile, line)) {
            stringstream ss(line);

            getline(ss, subject, ',');     // �̸�
            getline(ss, professornum, ',');    // ����

            numbering += 1;
            if (prof.getNumber() == stoi(professornum)) {
                cout << "| " << setw(8) << left << numbering
                    << "| " << setw(21) << left << subject
                    << "| " << setw(29) << left << professornum
                    << "|" << endl;
            }
            subjects.push_back(subject);
        }
    }
    csvFile.close();
    return subjects;
    cout << "=================================================================" << endl;
}

/// <summary>
/// ������ ��ü List�� ���
/// </summary>
void rwcsv::PrintSubjectList() {
    string filename = "subjectList.csv";
    ifstream csvFile(filename);

    cout << "=================================================================" << endl;
    cout << "|                         Subject List                          |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num     |  Subject             |        Professor Num         |" << endl;
    cout << "=================================================================" << endl;

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // ��� �ǳʶٱ�
        int numbering = 0;      // ��� ��ȣ
        string subject, professornum;

        while (getline(csvFile, line)) {
            stringstream ss(line);
            getline(ss, subject, ',');      // �����
            getline(ss, professornum, ','); // ����

            numbering++;
            cout << "| " << setw(8) << left << numbering
                << "| " << setw(21) << left << subject
                << "| " << setw(29) << left << professornum
                << "|" << endl;
        }
    }
    else {
        cerr << "Failed to open file: " << filename << endl;
    }
    cout << "=================================================================" << endl;
}

/// <summary>
/// ���ο� ���� ���� ���ο� .csv�� �����ϰ� �ű⿡ �й����� �����ϴ� �Լ�
/// </summary>
/// <param name="subjectname">�����, ����� + "csv"�� .csv ����</param>
/// <param name="studentsnum">header�� �� �й���</param>
#pragma endregion

/// <summary>
/// ������ �̸��� ������ �� ������ ������ ���� ���
/// </summary>
/// <param name="prof"></param>


/// <summary>
/// Ư�� �л��� �̸��� �Է� �޾� �л��� �������� ������ ��ȸ�ϴ� �Լ�
/// </summary>
/// <param name="filename"></param>
/// <param name="studentName"></param>
/// <returns></returns>
vector<string> rwcsv::PrintStudentSubject(const string & filename, const string & studentName) {
    ifstream file(filename); // ���� ����

    // ������ ������ ������ ���� �޽��� ���
    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return {}; //�� ���� ��ȯ
    }

    string line;
    vector<string> courses; // �л��� ���� ������ ������ ����
    bool studentFound = false;  // �ش� �л��� �����Ͱ� �ִ��� Ȯ��
    bool isFirstline = true; // ������� Ȯ��

    while (getline(file, line)) {
        // �� ���� ���� ��� �ǳʶٱ�
        if (line.empty())
            continue;

        //ù ���� ���(�л���, �й�, course1, course2, course3 ..)�� �����ϰ� ����
        if (isFirstline) {
            isFirstline = false;
            continue;
        }

        stringstream ss(line);
        string name, id, course;
        getline(ss, name, ','); // �л� �̸� �б�
        getline(ss, id, ','); // �л� �й� �б�

        // �л� �̸��� ��ġ�ϸ� ���� ���� ���� �б�
        if (name == studentName) {
            while (getline(ss, course, ',')) {
                courses.push_back(course);
            }
            studentFound = true;
            break;
        }
    }

    file.close();

    if (!studentFound) {
        cout << "�ش� �л� ������ ã�� �� �����ϴ�.\n";
        return {};
    }

    if (courses.empty()) {
        cout << "���� ���� ������ �����ϴ�.\n";
        return {};
    }

    // ���� ���� ���
    cout << "===================================\n";
    cout << "���� ���� ���� ���� �����Դϴ�.\n";
    for (size_t i = 0; i < courses.size(); ++i) {
        cout << i + 1 << ". " << courses[i] << '\n';
    }
    cout << "===================================\n";
    return courses;
}

/// <summary>
/// �л��� ������� �Է� �޾Ƽ� ������ �����ϴ� �Լ�
/// </summary>
/// <param name="filename"></param>
/// <param name="studentName"></param>
void rwcsv::PrintStudentGrade(const string& filename, const string& studentName) {
    string csvfilename = filename + ".csv";
    ifstream file(csvfilename); // ���� ����

    // ���� ���� ���� �� ���� �޽��� ��� �� ����
    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << csvfilename << endl;
        return;
    }

    string line;
    bool studentFound = false;

    // CSV ������ ����� �о ���
    if (getline(file, line)) {
        cout << left << setw(20) << "�л� �̸�"
            << setw(15) << "�й�"
            << setw(20) << "����"
            << setw(20) << "�⼮ ����"
            << setw(20) << "�߰���� ����"
            << setw(20) << "�⸻��� ����"
            << setw(20) << "���� ����" << endl;
    }
    else {
        cerr << "CSV ������ ����� ���� �� �����ϴ�: " << csvfilename << endl;
        return;
    }

    // ������ �� �پ� ����
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number, attendance, midterm, finalExam, assignment;

        // CSV ������ �Ľ�
        getline(ss, name, ',');
        getline(ss, number, ',');
        getline(ss, attendance, ',');
        getline(ss, midterm, ',');
        getline(ss, finalExam, ',');
        getline(ss, assignment, ',');

        // �л� �̸��� �Ű������� ��ġ�ϸ� ���
        if (name == studentName) {
            cout << left
                << setw(20) << name
                << setw(15) << number
                << setw(20) << filename
                << setw(20) << attendance
                << setw(20) << midterm
                << setw(20) << finalExam
                << setw(20) << assignment
                << endl;
            studentFound = true;
            break;
        }
    }

    // �л��� ã�� ���� ���
    if (!studentFound) {
        cout << "�ش� �л��� ã�� �� �����ϴ�: " << studentName << endl;
    }

    file.close(); // ���� �ݱ�

    // ����� �Է� ��û (������ �����ϰ� ��ġ ����)
    int num;
    cout << "Ȯ���ϼ̴ٸ� -1�� �Է����ּ���: ";
    cin >> num;
}

/// <summary>
/// �л��� ��� ������ ������ ��ȸ�ϴ� �Լ�
/// </summary>
/// <param name="filenames"></param>
/// <param name="studentName"></param>
void rwcsv::PrintALLStudentGrade(vector<string> filenames, string studentName) {
    cout << left
        << setw(20) << "�л� �̸�" << setw(15) << "�й�" << setw(20) << "���� " << setw(20)
        << setw(20) << "�⼮ ����" << setw(20) << "�߰���� ����" << setw(20) << "�⸻��� ����" << setw(20) << "���� ����" << endl;

    vector<string> noGradeSubject;
    for (string filename : filenames) {
        string csvfilename = filename + ".csv";
        ifstream file(csvfilename); // ���� ����

        // ���� ���� ���� �� ���� �޽��� ��� �� ����
        // ���� ���� ���� �� ���� �޽��� ��� �� ����
        if (!file.is_open()) {
            cerr << "������ �� �� �����ϴ�: " << csvfilename << endl;
            return;
        }

        string line;
        bool studentFound = false;

        // ������ �� �پ� ����
        while (getline(file, line)) {
            // ��� �ִ� ���� �ǳʶ�
            if (line.empty()) continue;

            stringstream ss(line);
            string name, number, attendance, midterm, finalExam, assignment;

            // CSV ������ �Ľ�
            if (!getline(ss, name, ',') || !getline(ss, number, ',') ||
                !getline(ss, attendance, ',') || !getline(ss, midterm, ',') ||
                !getline(ss, finalExam, ',') || !getline(ss, assignment, ',')) {
                noGradeSubject.push_back(filename);
            }

            // �л� �̸��� �Ű������� ��ġ�ϸ� ���
            if (name == studentName) {
                cout << left
                    << setw(20) << name
                    << setw(15) << number
                    << setw(20) << filename
                    << setw(20) << attendance
                    << setw(20) << midterm
                    << setw(20) << finalExam
                    << setw(20) << assignment
                    << endl;
                studentFound = true;
                break;
            }
        }

        // �л��� ã�� ���� ���
        if (!studentFound) {
            cout << "�ش� �л��� ã�� �� �����ϴ�: " << studentName << endl;
        }

       
        file.close(); // ���� �ݱ�
    }
    for (string i : noGradeSubject) {
        cout << i << ", ";
    }
    cout << "�� ���� ������ �ԷµǾ����� �ʾҽ��ϴ�." << endl;
    int num;
    cout << "Ȯ���ϼ̴ٸ� -1�� �Է����ּ���" << endl;
    cin >> num;
}
void rwcsv::UpdateAllStudentsGrade(const string& subjectName, const int& categorynum) {
    string filename = subjectName + ".csv"; // ���� �ش��ϴ� ���� �̸�
    ifstream infile(filename); // ���� ���� �б�
    vector<string> fileLines; // ������ ��� ���� ����
    vector<string> head;
    int categoryIndex = categorynum - 1; // ������ �� �׸��� �ε��� (0-based)

    // ���� ���� ���� �� ó��
    if (!infile.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return;
    }

    string line;
    // ù ��(���) �б�
    if (getline(infile, line)) {
        fileLines.push_back(line);
        stringstream lineStream(line);
        string token;
        while (getline(lineStream, token, ',')) {
            head.push_back(token); // ����� �״�� ����
        }
    }
    else {
        cerr << "CSV ������ ��� �ְų� ����� ���� �� �����ϴ�: " << filename << endl;
        infile.close();
        return;
    }

    // ������ ���� �� �б�
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string token;
        vector<string> row;

        // �� ���� ',' �������� �Ľ�
        while (getline(lineStream, token, ',')) {
            row.push_back(token); // ��� �ִ� �ʵ嵵 �� ���ڿ��� �߰�
        }

        // �ʵ� ���� ���� �� �� ���ڿ� �߰�
        while (row.size() < head.size()) {
            row.push_back(""); // ������ �ʵ常ŭ �� �� �߰�
        }

        // �� �׸��� ��ȿ�� �˻�
        if (row.size() <= categoryIndex + 2) {
            cerr << "CSV ������ ������ �ùٸ��� �ʽ��ϴ�: " << line << endl;
            fileLines.push_back(line); // ���� �� ����
            continue;
        }

        int newScore;
        while (true) {
            cout << row[0] << " �л��� " << head[categoryIndex + 2] << " ������ �Է����ּ���." << endl;
            cout << ">> �Է�: ";
            cin >> newScore;
            if (categoryIndex == 0 && newScore > 10) {
                cout << "�⼮ ������ 10���� �ʰ��� �� �����ϴ�." << endl;
            }
            else if (categoryIndex != 0 && newScore > 30) {
                cout << "������ 30���� �ʰ��� �� �����ϴ�." << endl;
            }
            else {
                break;
            }
        }

        // �ش� �׸��� ������ ���ο� ������ ������Ʈ
        row[categoryIndex + 2] = to_string(newScore);

        // ������Ʈ�� ���� �籸���ؼ� ����
        string updatedLine;
        for (size_t i = 0; i < row.size(); ++i) {
            updatedLine += row[i];
            if (i < row.size() - 1) updatedLine += ","; // �������� �ƴ� ��� ',' �߰�
        }
        fileLines.push_back(updatedLine);
    }

    infile.close(); // ���� �ݱ�

    // ������ ������ ���Ͽ� �ٽ� ����
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const string& fileLine : fileLines) {
            outfile << fileLine << "\n";
        }
        outfile.close();
        cout << "��� �л��� ������ ���������� ������Ʈ�Ǿ����ϴ�." << endl;
    }
    else {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
    }
}




void rwcsv::UpdateStudentGrade(const string& subjectName, int studentNumber, const int& categorynum, int score) {
    string filename = subjectName + ".csv"; // ���� �ش��ϴ� ���� �̸�
    ifstream infile(filename); // ���� ���� �б�
    vector<string> fileLines; // ������ ��� ���� ����
    bool studentFound = false; // �л��� �߰ߵǾ����� ����
    int categoryIndex = categorynum -1; // ������ �� �׸��� �ε���

    // ���� ���� ���� �� ó��
    if (!infile.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return;
    }

    string line;
    // ù ��(���) �б�
    if (getline(infile, line)) {
        fileLines.push_back(line);
        stringstream headerStream(line);
        string columnName;
        int index = 0;
    }

    // �� �׸��� ����� ���� ��� ���� ó��
    if (categoryIndex == -1) {
        cerr << "�� �׸��� ã�� �� �����ϴ�: " << categoryIndex << endl;
        infile.close();
        return;
    }

    // ������ ���� �� �б�
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string token;
        vector<string> row;
        while (getline(lineStream, token, ',')) {
            row.push_back(token);
        }

        // �й��� ��ġ�ϴ� �л� �߰� �� ���� ������Ʈ
        if (stoi(row[1]) == studentNumber) { // 1�� �ε����� �й��� �ִٰ� ����
            if (row.size() > categoryIndex) {
                row[categoryIndex +2] = to_string(score); // ���� ������Ʈ
            }
            studentFound = true;
        }

        // ������Ʈ�� ���� �籸���ؼ� ����
        string updatedLine;
        for (size_t i = 0; i < row.size(); ++i) {
            updatedLine += row[i];
            if (i < row.size() - 1) updatedLine += ",";
        }
        fileLines.push_back(updatedLine);
    }

    infile.close(); // ���� �ݱ�

    // �л��� �߰ߵ��� ���� ���
    if (!studentFound) {
        cerr << "�ش� �й��� �л��� ã�� �� �����ϴ�: " << studentNumber << endl;
        return;
    }

    // ������ ������ ���Ͽ� �ٽ� ����
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const string& fileLine : fileLines) {
            outfile << fileLine << "\n";
        }
        outfile.close();
        cout << "������ ���������� ������Ʈ�Ǿ����ϴ�." << endl;
    }
    else {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
    }
}

void rwcsv::PrintStudentsList(string subjectname) {
    string csvfilename = subjectname + ".csv";
    ifstream file(csvfilename); // ���� ����

    // ���� ���� ���� �� ���� �޽��� ��� �� ����
    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << csvfilename << endl;
        return;
    }

    string line;

    // ù ��° ���� (���) ���
    cout << "============================================�л� ���======================================" << endl;
    cout << "===========================================================================================" << endl;

    // ��� ���
    cout << left
        << setw(15) << "Name"
        << setw(15) << "Number"
        << setw(15) << "Attendance(10)"
        << setw(15) << "Midterm(30)"
        << setw(15) << "Final Exam(30)"
        << setw(15) << "Assignment(30)"
        << endl;
    cout << "===========================================================================================" << endl;

    getline(file, line);
    // ������ �� �پ� ����
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number, attendance, midterm, finalExam, assignment;

        // CSV ������ �Ľ�
        getline(ss, name, ',');
        getline(ss, number, ',');
        getline(ss, attendance, ',');
        getline(ss, midterm, ',');
        getline(ss, finalExam, ',');
        getline(ss, assignment, ',');

        // ������ ���
        cout << left
            << setw(15) << name
            << setw(15) << number
            << setw(15) << attendance
            << setw(15) << midterm
            << setw(15) << finalExam
            << setw(15) << assignment
            << endl;
    }

    cout << "===========================================================================================" << endl;
    file.close(); // ���� �ݱ�
}


