#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <iostream>

class Grade {
private:
    std::string studentName;
    int studentId;
    int attendance;
    int midtermTest;
    int finalTest;
    int assignment;

public:
    Grade(std::string name, int id, int att, int mid, int fin, int assign)
        : studentName(name), studentId(id), attendance(att), midtermTest(mid), finalTest(fin), assignment(assign) {}

    //학생 이름 반환
    std::string GetStudentName() const {
        return studentName;
    }

    //학생 학번 반환
    int GetStudentId() const {
        return studentId;
    }

    //이름, 학번, 항목별 점수, 총점 출력
    void DisplayGrades() const {
        std::cout << "학생 이름: " << studentName << '\n';
        std::cout << "학생 학번: " << studentId << '\n';
        std::cout << "출석 점수: " << attendance << '\n';
        std::cout << "중간고사: " << midtermTest << '\n';
        std::cout << "기말고사: " << finalTest << '\n';
        std::cout << "과제 점수: " << assignment << '\n';
        std::cout << "총점: " << CalculateTotalScore() << '\n';
    }

    //성적 합산 점수 계산
    int CalculateTotalScore() const {
        return attendance + midtermTest + finalTest + assignment;
    }
};

#endif // GRADE_H
