#include "Professor.h"
#include <iostream>
using namespace std;

void Professor::main() const
    {
    cout << "1. 전체 입력 " << "2. 이름 검색" << endl;
    int num;
    cin >> num;

    if (num == 1){
        cout << "1. 전체 성적 입력" << "2. 평가 항목 선택 입력" << endl;
        cin >> num;

        if ( num == 1){
            inputGrade_all(subjectName);
        }

        else if (num == 2){
            inputGrade_selectedHeader(subjectName);
        }
    }
    
    else if (num == 2){
        inputGrade_search(subjectName);
    }

}

void inputGrade_all(const string& subjectName) {
    // 과목명 + .csv = 파일명
    string filename = subjectName + ".csv";

    fstream file(filename, ios::in | ios::out);

    // 파일이 열리지 않으면 오류 메시지 출력
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;

    // 첫 번째 줄은 헤더이므로 고정
    string header = "이름,학번,중간고사,기말고사,출석";
    getline(file, line);  // 헤더 건너뛰기

    // 학생 데이터를 저장할 벡터
    vector<string> students;

    // 학생 데이터를 파일에서 읽어들인다
    while (getline(file, line)) {
        students.push_back(line);
    }

    // 각 학생에 대해 점수를 입력받고, 수정된 데이터를 저장
    for (auto& student : students) {
        stringstream ss(student);
        string name, numberStr;

        // 각 학생의 점수를 저장할 벡터
        vector<int> scores(3);  // 중간고사, 기말고사, 출석 점수를 저장

        getline(ss, name, ',');
        getline(ss, numberStr, ',');

        // 이름과 학번 출력
        cout << "이름: " << name << ", 학번: " << numberStr << endl;

        // 중간고사, 기말고사, 출석 점수를 입력받음
        cout << "중간고사 점수를 입력하세요: ";
        cin >> scores[0];
        cout << "기말고사 점수를 입력하세요: ";
        cin >> scores[1];
        cout << "출석 점수를 입력하세요: ";
        cin >> scores[2];

        // newStudent에 이름과 학번, 그 뒤에 scores 벡터의 내용 추가
        stringstream newStudent;
        newStudent << name << "," << numberStr;

        for (const auto& score : scores) {
            newStudent << "," << score;
        }

        student = newStudent.str();  // 수정된 학생 데이터로 갱신
    }

    // 파일에 수정된 데이터 저장
    file.clear();  // 파일 상태 플래그 초기화
    file.seekp(0); // 파일 시작으로 이동

    // 파일에 고정된 헤더 입력
    file << header << endl;
    for (const auto& student : students) {
        file << student << endl; // 수정된 학생 데이터 저장
    }

    file.close(); 

    cout << "성적 입력 완료" << endl;
}


    // 파일에 수정된 데이터 저장
    file.clear();  // 파일 상태 플래그 초기화
    file.seekp(0); // 파일 시작으로 이동

    // file 객체에 header 입력
    file << header << endl;
    for (const auto& student : students) {
        file << student << endl; // 수정된 학생 데이터 저장
    }

    file.close(); 

    cout << "성적 입력 완료" << endl;
}

void inputGrade_search(const string& subjectName) {
    // 과목명 + .csv = 파일명
    string filename = subjectName + ".csv";

    fstream file(filename, ios::in | ios::out);

    // 파일이 열리지 않으면 오류 메시지 출력
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;

    // 첫 번째 줄은 고정된 헤더이므로 건너뛰기
    string header = "이름,학번,중간고사,기말고사,출석";
    getline(file, line); // 헤더를 읽어서 버림

    // 학생 데이터를 저장할 벡터
    vector<string> students;

    while (getline(file, line)) {
        students.push_back(line);
    }

    // 이름을 입력받아 검색
    string searchName;
    cout << "검색할 학생의 이름을 입력하세요: ";
    cin.ignore(); // 이전 입력 버퍼 제거
    getline(cin, searchName);

    bool studentFound = false;

    // 각 학생에 대해 검색 및 점수 입력
    for (auto& student : students) {
        stringstream ss(student);
        string name, numberStr;

        getline(ss, name, ',');       // 이름 추출
        getline(ss, numberStr, ','); // 학번 추출

        if (name == searchName) {
            studentFound = true;

            // 검색 결과 출력
            cout << "검색 결과" << endl;
            cout << "이름: " << name << ", 학번: " << numberStr << endl;

            // 중간고사, 기말고사, 출석 점수를 입력받음
            vector<int> scores(3); // 중간고사, 기말고사, 출석
            cout << "중간고사 점수를 입력하세요: ";
            cin >> scores[0];
            cout << "기말고사 점수를 입력하세요: ";
            cin >> scores[1];
            cout << "출석 점수를 입력하세요: ";
            cin >> scores[2];

            // 수정된 학생 데이터 생성
            stringstream newStudent;
            newStudent << name << "," << numberStr;
            for (const auto& score : scores) {
                newStudent << "," << score;
            }

            student = newStudent.str(); // 수정된 학생 데이터로 갱신
            break;
        }
    }

    // 일치하는 학생이 없을 경우
    if (!studentFound) {
        cout << "해당 이름의 학생을 찾을 수 없습니다: " << searchName << endl;
        return;
    }

    // 파일에 수정된 데이터 저장
    file.clear();  // 파일 상태 플래그 초기화
    file.seekp(0); // 파일 시작으로 이동

    // 고정된 헤더 쓰기
    file << header << endl;
    for (const auto& student : students) {
        file << student << endl;
    }

    file.close();

    cout << "성적 입력 완료" << endl;
}

void inputGrade_selectedHeader(const string& subjectName) {
    // 과목명 + .csv = 파일명
    string filename = subjectName + ".csv";

    fstream file(filename, ios::in | ios::out);

    // 파일이 열리지 않으면 오류 메시지 출력
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;

    // 첫 번째 줄은 고정된 헤더이므로 건너뛰기
    string header = "이름,학번,중간고사,기말고사,출석";
    getline(file, line); // 헤더를 읽어서 버림

    // 학생 데이터를 저장할 벡터
    vector<string> students;
    while (getline(file, line)) {
        students.push_back(line);
    }

    // 사용자에게 입력할 단일 헤더 선택
    vector<string> allHeaders = { "중간고사", "기말고사", "출석" };
    int selectedHeaderIndex = -1;

    cout << "입력할 평가항목을 선택하세요: (1: 중간고사, 2: 기말고사, 3: 출석)\n";
    while (true) {
        cout << "선택: ";
        cin >> selectedHeaderIndex;
        if (selectedHeaderIndex >= 1 && selectedHeaderIndex <= 3) {
            --selectedHeaderIndex; // 0부터 시작하도록 조정
            break;
        }
        cout << "잘못된 선택입니다. 다시 시도하세요.\n";
    }

    // 선택된 헤더 이름
    string selectedHeader = allHeaders[selectedHeaderIndex];
    cout << "현재 평가 항목: " << selectedHeader << endl;

    // 각 학생에 대해 선택된 점수 입력
    for (auto& student : students) {
        stringstream ss(student);
        string name, numberStr;
        vector<string> scores(3, ""); // 중간고사, 기말고사, 출석 점수 초기화

        getline(ss, name, ',');       // 이름 추출
        getline(ss, numberStr, ','); // 학번 추출

        for (int i = 0; i < allHeaders.size(); ++i) {
            if (!getline(ss, scores[i], ',')) {
                scores[i] = "0"; // 값이 없으면 기본값 0으로 초기화
            }
        }

        cout << "학생: " << name << "학번: " << numberStr << endl;
        cout << selectedHeader << " 점수를 입력하세요 (현재 점수: " << scores[selectedHeaderIndex] << "): ";
        cin >> scores[selectedHeaderIndex];

        // 수정된 학생 데이터 생성
        stringstream newStudent;
        newStudent << name << "," << numberStr;
        for (const auto& score : scores) {
            newStudent << "," << score;
        }

        student = newStudent.str(); // 수정된 학생 데이터로 갱신
    }

    // 파일에 수정된 데이터 저장
    file.clear();  // 파일 상태 플래그 초기화
    file.seekp(0); // 파일 시작으로 이동

    // 고정된 헤더 쓰기
    file << header << endl;
    for (const auto& student : students) {
        file << student << endl;
    }

    file.close();

    cout << "선택된 점수 입력이 완료되었습니다." << endl;
}