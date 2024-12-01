#ifndef STUDENT_GRADES_H
#define STUDENT_GRADES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 성적 정보를 처리하는 클래스
class StudentGrade {
private:
    string studentName;
    string studentId;
    int attendance;
    int midtermTest;
    int finalTest;
    int assignment;

public:
    // 생성자
    StudentGrade(const string& name, const string& id, int attend, int midterm, int finalExam, int assign)
        : studentName(name), studentId(id), attendance(attend), midtermTest(midterm), finalTest(finalExam), assignment(assign) {}

    // Getter 메서드
    string GetStudentName() const { return studentName; }
    string GetStudentId() const { return studentId; }
    int GetAttendance() const { return attendance; }
    int GetMidtermTest() const { return midtermTest; }
    int GetFinalTest() const { return finalTest; }
    int GetAssignment() const { return assignment; }

    // 총점 계산
    int TotalScore() const {
        return attendance + midtermTest + finalTest + assignment;
    }

    // 성적 출력
    void DisplayGrades(double averageScore, int rank, int totalStudents) const {
        cout << "학생 이름: " << studentName << '\n';
        cout << "학생 학번: " << studentId << '\n';
        cout << "출석 점수: " << attendance << '\n';
        cout << "중간고사: " << midtermTest << '\n';
        cout << "기말고사: " << finalTest << '\n';
        cout << "과제 점수: " << assignment << '\n';
        cout << "총점: " << TotalScore() << '\n';
        cout << "전체 평균 점수: " << averageScore << '\n';
        cout << "석차: " << rank << " / " << totalStudents << '\n';
    }

};

// 함수 선언
void DisplayCourseGrades(const string& filename, const string& studentName);

#endif
