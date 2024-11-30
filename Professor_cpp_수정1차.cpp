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

// Subject 클래스 정의 (Score 상속) ++ 과목 생성될 때마다 상속받을수있도록 해야
class Subject : public Score {
public:
    string name;
    Subject(const string& subjectName) : name(subjectName) {}
};




void displaySubjects(int professorNum) {
    ifstream file("subjectList.csv");
    if (!file.is_open()) {
        cout << "subjectList.csv 파일을 열 수 없습니다." << endl;
        return;
    }
    string line;
    int count = 0;

    // 파일에서 한 줄씩 읽기
    while (getline(file, line)) {
        string subject;
        int num;

        // CSV 파일의 한 줄을 ','로 구분하여 파싱
        stringstream ss(line);
        getline(ss, subject, ','); // subject 읽기
        ss >> num; // professorNum 읽기

        // 입력받은 professorNum과 일치하면 출력
        if (num == professorNum) {
            cout << ++count << ". " << subject << endl;
        }
    }
    file.close();

    if (count == 0) {
        cout << professorNum << "에 해당하는 정보가 없습니다." << endl;
    }
}


void editSubject(const string& whichSubject) {
    string fileName = whichSubject + ".csv";

    fstream file(fileName, ios::in | ios::out);
    if (!file.is_open()) {
        cout << fileName << " 파일을 열 수 없습니다." << endl;
        return;
    }

    void pointSetting(Subject & whichSubject) {
        cout << "과목: " << whichSubject.name << endl;

        // 배점 설정
        cout << "attendance의 % 배점을 입력하세요: ";
        cin >> whichSubject.attendance;

        cout << "midtermTest의 % 배점을 입력하세요: ";
        cin >> whichSubject.midtermTest;

        cout << "finalTest의 % 배점을 입력하세요: ";
        cin >> whichSubject.finalTest;

        cout << "assignment의 % 배점을 입력하세요: ";
        cin >> whichSubject.assignment;

        cout << endl;
        cout << "=======================배점 설정=======================" << endl;
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

        // 과목 리스트 출력 : 교수한테 할당된 과목을 subjectList.csv에서 불러오기. 이를 위해 subjectList.csv에는 '과목명','교수번호' 형식으로 저장되어있다 가정
        cout << "=======================내 강의실=======================\n";
        displaySubjects(professornum);

        cout << "입장할 강의실을 입력하세요. (ex. 객체지향프로그래밍)" << endl;
        cin >> whichSubject;
        editSubject(whichSubject);

        system("cls");
        cout << "1. 평가항목 배점 설정 " << "2. 성적 입력 " << "3. 성적 변경 " << endl;
        cin >> num;
        if (num == 1) {
            pointSetting(whichSubject);
            // int 변수 point를 설정해둠. 근데 언제 보여줘야 하는가?? 성적출력할때??
        }
        else if (num == 2) {

        }
        else if (num == 3) {

        }
        return 0;
    }
}
