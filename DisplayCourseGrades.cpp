#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// 성적 정보를 처리하는 클래스
class StudentGrade {
    string studentName;
    string studentId;
    int attendance;
    int midtermTest;
    int finalTest;
    int assignment;

public:
    // 생성자
    StudentGrade(const string& name, const string& id, int att, int midterm, int finalExam, int assign)
        : studentName(name), studentId(id), attendance(att), midtermTest(midterm), finalTest(finalExam), assignment(assign) {}

    // 성적 출력
    void DisplayGrades() const {
        cout << "학생 이름: " << studentName << '\n';
        cout << "학생 학번: " << studentId << '\n';
        cout << "출석 점수: " << attendance << '\n';
        cout << "중간고사: " << midtermTest << '\n';
        cout << "기말고사: " << finalTest << '\n';
        cout << "과제 점수: " << assignment << '\n';
        cout << "총점: " << TotalScore() << '\n';
    }

    // 총점 계산
    int TotalScore() const {
        return attendance + midtermTest + finalTest + assignment;
    }
};

// CSV 파일에서 학생 정보를 검색하여 출력
void DisplayCourseGrades(const string& filename, const string& studentName) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << '\n';
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue; // 빈 줄 무시

        stringstream ss(line);
        string name, id;
        int att, midterm, finalExam, assign;

        // CSV 필드 읽기
        getline(ss, name, ',');
        getline(ss, id, ',');
        ss >> att;
        ss.ignore(); // 쉼표 무시
        ss >> midterm;
        ss.ignore();
        ss >> finalExam;
        ss.ignore();
        ss >> assign;

        // 학생 이름이 일치하면 정보를 출력
        if (name == studentName) {
            StudentGrade student(name, id, att, midterm, finalExam, assign);
            student.DisplayGrades();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "해당 학생의 정보를 찾을 수 없습니다.\n";
    }

    file.close();
}
