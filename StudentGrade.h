#ifndef STUDENT_GRADES_H
#define STUDENT_GRADES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ���� ������ ó���ϴ� Ŭ����
class StudentGrade {
private:
    string studentName;
    string studentId;
    int attendance;
    int midtermTest;
    int finalTest;
    int assignment;

public:
    // ������
    StudentGrade(const string& name, const string& id, int attend, int midterm, int finalExam, int assign)
        : studentName(name), studentId(id), attendance(attend), midtermTest(midterm), finalTest(finalExam), assignment(assign) {}

    // Getter �޼���
    string GetStudentName() const { return studentName; }
    string GetStudentId() const { return studentId; }
    int GetAttendance() const { return attendance; }
    int GetMidtermTest() const { return midtermTest; }
    int GetFinalTest() const { return finalTest; }
    int GetAssignment() const { return assignment; }

    // ���� ���
    int TotalScore() const {
        return attendance + midtermTest + finalTest + assignment;
    }

    // ���� ���
    void DisplayGrades() const {
        cout << "�л� �̸�: " << studentName << endl;
        cout << "�л� �й�: " << studentId << endl;
        cout << "�⼮ ����: " << attendance << endl;
        cout << "�߰����: " << midtermTest << endl;
        cout << "�⸻���: " << finalTest << endl;
        cout << "���� ����: " << assignment << endl;
        cout << "����: " << TotalScore() << '\n';
        //cout << "��ü ��� ����: " << averageScore << '\n';
        //cout << "����: " << rank << " / " << totalStudents << '\n';
    }
};

// �Լ� ����
void DisplayCourseGrades(const string& filename, const string& studentName);

#endif