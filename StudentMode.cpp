#include <iostream>
#include <string>
#include <vector>
#include "DisplayStudentCourses.h"

using namespace std;

int main() {

    /**사용자로부터 학생 이름 입력받기(로그인 과정에서 입력받지 않으나.. 
    학생목록 csv에서 정보 불러오기 해야 할 것 같기도 합니다 
    로그인도 했는데 다시 이름 입력하라고 하는건 어색하니까요..!**/
    string studentName;
    cout << "학생의 이름을 입력하세요: ";
    cin >> studentName;

    // 학생 수강 과목 출력 및 해당 리스트 저장
    string filename = "StudentCourses.csv";
    vector<string> courses = DisplayStudentCourses(filename, studentName);

    if (courses.empty()) {
        cout << "수강 중인 과목이 없습니다.\n";
        return 0; // 수강 과목이 없으면 종료
    }

    // 학생이 성적을 조회할 과목 번호 입력
    int chooseCourse;
    while (true) {
        cout << "\n조회할 과목명을 입력하세요.";
        cin >> chooseCourse;

       // courses 벡터에서 입력한 과목명이 있는지 확인
        auto it = find(courses.begin(), courses.end(), selectedCourse);

        if (it != courses.end()) {
            // 과목명을 찾으면 종료
            break;
        } else {
            cout << "잘못된 과목명입니다. 다시 입력하세요.\n";
        }
    }
    cout << selectedCourse << "과목의 성적을 조회합니다."

    // 선택한 과목의 .csv 파일 찾기
    string courseFile = FindCourseFile(selectedCourse);

    if (courseFile.empty()) {
        cerr << "해당 과목의 .csv 파일을 시스템에서 찾을 수 없습니다.\n";
        return 0; // 종료
    }

    // 해당 과목의 세부 성적 출력
    DisplayCourseGrades(filename, studentName);

    return 0;
}
