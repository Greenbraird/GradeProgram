#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 학생 정보를 출력하는 함수
void DisplayStudentCourses(const string& filename, const string& studentName) {
    ifstream file(filename); // 파일 열기

    // 파일이 열리지 않으면 오류 메시지 출력
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return; //빈 벡터 반환
    }
    
    string line;
    vector<string> courses; // 학생의 수강 과목을 저장할 벡터
    bool studentFound = false;  // 해당 학생의 데이터가 있는지 확인
    bool isFirstline = true; // 헤더인지 확인

    while (getline(file, line)) {
        // 빈 줄이 있을 경우 건너뛰기
        if (line.empty())
            continue;
        
        //첫 줄은 헤더(학생명, 학번, course1, course2, course3 ..)로 간주하고 무시
        if (isFirstLine){
            isFirstLine = false;
            continue;
        }

        stringstream ss(line);
        string name, id, course;
        getline(ss, name, ','); // 학생 이름 읽기
        getline(ss, id, ','); // 학생 학번 읽기

        // 학생 이름이 일치하면 수강 중인 과목 읽기
        if (name == studentName) { 
            while (getline(ss, course, ',')) {
                courses.push_back(course);
            }
            studentFound = true;
            break;
        }
    }

    file.close();

    if (!studentFound) {
        cout << "해당 학생 정보를 찾을 수 없습니다.\n";
        return;
    }

    if (couses.empty()){
        cout << "수강 중인 과목이 없습니다.\n";
        return;
    }

    // 수강 과목 출력
    cout << "===================================\n";
    cout << "현재 수강 중인 과목 내역입니다.\n";
    for (size_t i = 0; i < courses.size(); ++i) {
        cout << i + 1 << ". " << courses[i] << '\n';
    }
}
