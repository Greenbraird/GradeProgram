#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "DisplayCourseGrade.h"

using namespace std;

// CSV 파일에서 성적 출력
void DisplayCourseGrades(const string& filename, const string& studentName) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << '\n';
        return;
    }

    vector<StudentGrade> students; // 학생 성적 정보 저장
    StudentGrade* currentStudent = nullptr; // 현재 학생을 가리키는 포인터
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue; // 빈 줄 무시

        stringstream ss(line);
        string name, id;
        int attend, midterm, finalExam, assign;

        // CSV 필드 읽기
        getline(ss, name, ',');
        getline(ss, id, ',');
        ss >> attend;
        ss.ignore(); // 쉼표 무시
        ss >> midterm;
        ss.ignore();
        ss >> finalExam;
        ss.ignore();
        ss >> assign;

        // 학생 정보를 vector에 추가
        StudentGrade student(name, id, attend, midterm, finalexam, assign);
        students.push_back(student);

        // 현재 학생을 확인
        if (name == studentName) {
            currentStudent = &students.back();
        }
    }

    // 학생을 찾을 수 없는 경우
    if (!currentStudent) {
        cout << "해당 학생의 정보를 찾을 수 없습니다.\n";
        return;
    }

    // 평균 점수 계산
    int totalScores = 0;
    for (const auto& student : students) {
        totalScores += student.CalculateTotalScore();
    }
    double averageScore = static_cast<double>(totalScores) / students.size();

    // 석차 계산
    sort(students.begin(), students.end(), [](const StudentGrade& a, const StudentGrade& b) {
        return a.CalculateTotalScore() > b.CalculateTotalScore();
    });

    int rank = 1;
    for (const auto& student : students) {
        if (student.studentName == studentName) break;
        ++rank;
    }
    
    // 성적 출력
    currentStudent->DisplayGrades(averageScore, rank, students.size());
}
