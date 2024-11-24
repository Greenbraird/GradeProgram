#include "DisplayStudentCourses.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// 학생 정보를 출력하는 함수
vector<string> DisplayStudentCourses(const string& filename, const string& studentName) {
    ifstream file(filename); // 파일 열기
    string line;
    vector<string> courses;

    // 파일이 열리지 않으면 오류 메시지 출력
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return courses; //빈 벡터 반환
    }

    bool found = false; // 학생 정보가 발견되었는지 확인

    while (getline(file, line)) {
        // 빈 줄이 있을 경우 건너뛰기
        if (line.empty())
            continue;

        stringstream ss(line);
        string name, id, course;

        getline(ss, name, ','); // 학생 이름 읽기
        if (name == studentName) { // 학생 이름이 일치하면
            getline(ss, id, ','); // 학번 읽기
            cout << "===========================\n";
            cout << "현재 수강 중인 과목 내역입니다.\n";

            // 수강 과목 읽고 출력
            int courseNumber = 1;
            while (getline(ss, course, ',')) {
                cout << courseNumber << ". " << course << '\n';
                courses.push_back(course);
                ++courseNumber;
            }

            found = true;
            break; // 반복 종료
        }
    }

    if (!found) {
        cout << "해당 학생 정보를 찾을 수 없습니다.\n";
    }

    return courses;
}
