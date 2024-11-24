#include <iostream>
#include "DisplayStudentCourses.h"

using namespace std;

int main() {
    string studentName;

    /**사용자로부터 학생 이름 입력받기(로그인 과정에서 입력받지 않으나.. 
    학생목록 csv에서 정보 불러오기 해야 할 것 같기도 합니다)**/
    cout << "학생 이름을 입력하세요: ";
    cin >> studentName;

    // 파일 경로 설정 및 학생 수강 과목 출력
    string filename = "StudentCourses.csv";
    DisplayStudentCourses(filename, studentName);

    if (courses.empty()) {
        std::cout << "수강 중인 과목이 없습니다.\n";
        return 0; // 수강 과목이 없으면 종료
    }

    int chooseCourse;
    cout << "\n조회할 과목 번호를 입력하세요";
    cin >> chooseCourse;

    // 입력 값 검증
    if (chooseCourse < 1 || chooseCourse > courses.size()) {
        cerr << "잘못된 선택입니다. 프로그램을 종료합니다.\n";
        return 0;
    }

    // 선택한 과목의 이름 가져오기
    string selectedCourse = courses[chooseCourse - 1];

    // 선택한 과목을 문자열로 바꿔서 .csv 로 바꾸고 .csv 목록 중 해당 파일을 찾는 코드 추가 필요

    // 해당 과목의 세부 성적 출력
    DisplayCourseGrades(filename, studentName);

    return 0;
}