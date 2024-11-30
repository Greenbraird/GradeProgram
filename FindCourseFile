#include <fstream>
#include <string>

using namespace std;

// 과목 이름을 받아 .csv 파일 존재 여부를 확인하고, 파일명을 반환
string FindCourseFile(const string& courseName) {
    string courseFile = courseName + ".csv";

    // 파일 존재 여부 확인
    ifstream file(courseFile);
    if (file.is_open()) {
        file.close();
        return courseFile; // 파일이 존재하면 파일명 반환
    } else {
        return ""; // 파일이 존재하지 않으면 빈 문자열 반환
    }
}
