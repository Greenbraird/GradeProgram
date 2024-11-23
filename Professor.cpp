#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Professor.h"

using namespace std;

// 구조체 정의: 학생 CSV 데이터 저장
struct Student {
    string name;
    string number;
};

// 구조체 정의: 교수 CSV 데이터 저장
struct Professor {
    string name;
    string subject;
};



/* 3.1. 과목 선택 */
// 읽을 filename(csv 파일) 경로를 받아, 파일 내 데이터를 professor 객체로 저장
vector<Professor> readCSV(const string& filename) {
    vector<Professor> professors;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return professors;
    }

    // 첫 번째 라인은 건너뜀
    string line;
    getline(file, line);

    // 파일 내 문자열 데이터 처리, 추출한 데이터를 문자열 변수로 저장
    while (getline(file, line)) {
        stringstream ss(line);
        string name, subject;

        // ','로 분리
        getline(ss, name, ',');
        getline(ss, subject, ',');

        // 교수 정보를 저장
        professors.push_back({ name, subject });
    }

    file.close();
    return professors;
}

// 입력된 이름에 해당하는 과목 출력 함수
void displaySubjects(const vector<Professor>& professors, const string& targetName) {
    int count = 0;

    for (const auto& professor : professors) {
        if (professor.name == targetName) {
            cout << ++count << ". " << professor.subject << endl;
        }
    }

    if (count == 0) {
        cout << targetName << "에 해당하는 정보가 없습니다." << endl;
    }
}
// 입력된 교수가 아니라 로그인 정보를 바탕으로 과목을 출력해야함 //
// 로그인한 교수의 과목 가져오기로 수정해야함//




/* 3.2. 평가항목 생성 */

// CSV 파일 읽기
vector<Student> readCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return students;
    }

    string line;
    // 헤더는 건너뛰기
    getline(file, line);

    // 데이터 읽기
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number;

        // ','로 분리하여 데이터 읽기
        getline(ss, name, ',');
        getline(ss, number, ',');

        // 구조체에 데이터 저장
        students.push_back({ name, number });
    }

    file.close();
    return students;
}

// CSV 파일 쓰기 함수
void writeCSV(const string& filename, const vector<Student>& students, const string& newColumn) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    // 헤더 쓰기
    file << "name,number," << newColumn << endl;

    // 데이터 쓰기
    for (const auto& student : students) {
        file << student.name << "," << student.number << ",0" << endl; // 새 열은 기본값 0
    }

    file.close();
}



void createAssignment() {
    string filename = "subjectCalculus.csv"; // 임시로 해놓은 것... 사용자가 선택한 과목이 들어가는 변수로 만들어야

    // CSV 파일 읽기
    vector<Student> students = readCSV(filename);
    if (students.empty()) {
        cerr << "CSV 파일에서 데이터를 읽지 못했습니다." << endl;
        return;
    }

    cout << "추가할 평가항목 이름을 입력하세요: ";
    string newColumn;
    cin >> newColumn;

    // 새 열 추가
    writeCSV(filename, students, newColumn);

    cout << "CSV 파일이 성공적으로 수정되었습니다: " << filename << endl;
}







void Professor::main() const
{
    string whichSubject;
    int profMode;

    while (true) {
        system("cls");
        cout << "=======================내 강의실=======================\n";
        // 3.1. 과목 선택 : 과목 리스트 출력/과목명 입력
        // 교수한테 할당된 과목을 subject.csv에서 불러오기. 이를 위해 subject.csv에는 name, subject 형식으로 저장되어있다 가정
        string profName = ; //로그인 정보에서 교수 이름 가져와 변수 설정해야 함
        string filename = "professor.csv";
        vector<Professor> professors = readCSV(filename);

        if (professors.empty()) {
            cerr << "CSV 데이터를 읽는 데 실패했습니다." << endl;
            return 1;
        }

        cout << "입장할 강의실을 선택하세요." << endl;
        displaySubjects(professors, profName);

        cin >> whichSubject;
        if (whichSubject == ) {
            system("cls");
            string csv = ? ? ; //일케 넣어서 설정해야 하나...
            // 그 과목 csv로 이동
        }

        cout << "1. 평가항목 생성 " << "2. 성적 입력 " << endl;
        cin >> profMode;
        if (profMode == 1) {
            createAssignment();
        }
        else if (profMode == 2) {
            // 성적 입력 함수 삽입
        }
        return 0;
    }
}
