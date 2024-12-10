#include "rwcsv.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iomanip>

using namespace std;
#pragma region User와 관련된 CSV 저장 및 삭제 함수

// user data를 csv에 저장하는 함수
void rwcsv::AddUserDataCSV(const string& filename, User& user) {

    //append 모드로 파일을 연다
    ofstream csvfile(filename, ios::app);
    if (csvfile.is_open()) {
        csvfile << user.getName() << "," << user.getMajor() << ","
            << user.getNumber() << "," << user.getId() << ","
            << user.getPassword() << "," << user.getEmail() << "\n";
        csvfile.close();

        cout << "성공적으로 추가가 완료되었습니다." << endl;
    }
    else
    {
        cerr << "파일을 찾을 수 없습니다." << endl;
    }
}

/// <summary>
/// 파일이름에서 id와 password가 같은 user를 찾아
/// 있으면 각 Professor 혹은 Student 객체 반환
/// </summary>
/// <param name="filename">student.csv와 professor.csv</param>
/// <param name="id"></param>
/// <param name="password"></param>
/// <returns>Professor 혹은 Student 객체 반환</returns>
User* rwcsv::UserLogin(const string& filename, const string& id, const string& password) {
    ifstream csvFile(filename);

    if (!csvFile.is_open()) {
        cout << "파일을 열 수 없습니다: " << filename << endl;
        return nullptr; // 파일이 열리지 않으면 nullptr 반환
    }

    string line;
    getline(csvFile, line); // 헤더 건너뛰기

    while (getline(csvFile, line)) {
        stringstream ss(line); // 한 줄로 되어 있는 것을 stringstream으로 처리

        string _name, _major, _number;
        string _id, _password, _email;

        getline(ss, _name, ',');    // name
        getline(ss, _major, ',');   // major
        getline(ss, _number, ',');  // number
        getline(ss, _id, ',');      // id
        getline(ss, _password, ','); // password
        getline(ss, _email, ',');   // email

        int number = stoi(_number); // string -> int 변환

        if (id == _id && password == _password) {
            csvFile.close(); // 파일 닫기
            if (filename == "student.csv") {
                return new Student(_name, _major, number, _id, _password, _email);
            }
            else {
                return new Professor(_name, _major, number, _id, _password, _email);
            }
        }
        
    }

    csvFile.close(); // 파일 닫기
    cout << "로그인에 실패했습니다." << endl;
    return nullptr; // 로그인 실패 시 nullptr 반환
}

/// <summary>
/// student나 professor를 입력하면
/// 각 해당되는 .csv를 읽어서 vector로 반환함.
/// </summary>
/// <param name="user">student나 professor중 하나의 값을 입력받음.</param>
/// <returns></returns>
vector<User*> rwcsv::ReadUserCSV(const string& user) {
    string filename = user + ".csv";
    ifstream csvFile(filename);

    vector<User*> users; // 반환할 User 포인터 벡터

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // 헤더 건너뛰기

        while (getline(csvFile, line)) {
            stringstream ss(line);

            string name, major, numberStr, id, password, email;
            getline(ss, name, ',');     // 이름
            getline(ss, major, ',');    // 전공
            getline(ss, numberStr, ','); // 학번 (문자열로 읽기)
            getline(ss, id, ',');       // 아이디
            getline(ss, password, ','); // 비밀번호
            getline(ss, email, ',');    // 이메일

            int number = stoi(numberStr); // 학번을 정수로 변환

            // 역할에 따라 Student 또는 Professor 객체 생성
            if (user == "student") {
                users.push_back(new Student(name, major, number, id, password, email));
            }
            else if (user == "professor") {
                users.push_back(new Professor(name, major, number, id, password, email));
            }
        }

        csvFile.close();
    }
    else {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
    }

    return users;
}

/// <summary>
/// user의 이름을 받아 user의 csv 내용을 콘솔창 출력하는 함수.
/// </summary>
/// <param name="printuser">professor 혹은 student</param>
void rwcsv::PrintUserCSV(const string& printuser) {
    // 헤더 출력
    cout << "===========================================" << endl;
    cout << "|                " << printuser << "                |" << endl;
    cout << "===========================================" << endl;
    cout << "| Num      | Number     | Name            |" << endl;
    cout << "===========================================" << endl;

    vector<User*> uservector = this->ReadUserCSV(printuser);

    int numbering = 0;
    // 각 User 정보를 출력
    for (const User* user : uservector) {
        numbering += 1;
        // 사용자 정보 출력
        cout << "| " << setw(10) << left << numbering
            << "| " << setw(11) << left << user->getNumber()
            << "| " << setw(15) << left << user->getName()
            << "|" << endl;
    }
    // 각 User 정보를 출력


    // 테이블 하단 장식
    cout << "===========================================" << endl;
}
#pragma endregion


#pragma region 과목에 대한 CSV 저장 및 삭제 함수
void rwcsv::RemoveSubjectCSVFile(const string& subjectname) {
    string filename = "subjectList.csv";
    ifstream inputFile(filename);
    ofstream tempFile("temp.csv"); // 임시 파일 생성

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "파일 열기에 실패했습니다." << endl;
        return;
    }

    string line;
    bool found = false;

    // 헤더 복사
    if (getline(inputFile, line)) {
        tempFile << line << endl; // 헤더를 임시 파일로 복사
    }

    // 각 줄을 읽으면서 subjectname과 일치하지 않는 줄을 임시 파일로 복사
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string currentSubject;
        getline(ss, currentSubject, ','); // subject 이름 추출 (첫 번째 값)

        if (currentSubject != subjectname) {
            tempFile << line << endl; // 다른 이름은 그대로 복사
        }
        else {
            found = true; // 삭제 대상 발견
        }
    }

    inputFile.close();
    tempFile.close();

    // 삭제 완료 후 원본 파일을 임시 파일로 대체
    if (found) {
        if (remove(filename.c_str()) != 0 || rename("temp.csv", filename.c_str()) != 0) {
            cerr << "파일 처리 중 오류가 발생했습니다." << endl;
        }
        else {
            remove((subjectname + ".csv").c_str());
            cout << "과목 \"" << subjectname << "\"가 성공적으로 삭제되었습니다." << endl;
        }
    }
    else {
        remove("temp.csv"); // 임시 파일 삭제
        cout << "과목 \"" << subjectname << "\"를 찾을 수 없습니다." << endl;
    }
}
/// <summary>
/// 과목명과 교본, 학번들을 입력 받아 data들 subjectList.csv에 저장하는 함수
/// </summary>
/// <param name="subjectname">과목명</param>
/// <param name="professornum">당담교수 교번</param>
/// <param name="studentnums">수강하는 학생들 학번들</param>
void rwcsv::AddSubjectDataCSV(string subjectname, int professornum) {

    //append 모드로 파일을 연다
    ofstream csvfile("subjectList.csv", ios::app);
    if (csvfile.is_open()) {
        csvfile << endl << subjectname << "," << professornum;
        cout << "성공적으로 저장하였습니다." << endl;
    }
    else
    {
        cerr << "파일을 찾을 수 없습니다." << endl;
    }
}
void rwcsv::RemoveSubjectDataCSV(string subjectname) {
    ifstream csvfile("subjectList.csv"); // 읽기 모드로 파일을 연다
    if (!csvfile.is_open()) {
        cerr << "파일을 찾을 수 없습니다." << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    // 파일에서 한 줄씩 읽어와서 lines 벡터에 저장
    while (getline(csvfile, line)) {
        stringstream ss(line);
        string subject;
        getline(ss, subject, ','); // 과목명 읽기

        // 과목명이 일치하면 해당 줄을 삭제
        if (subject == subjectname) {
            found = true;
            continue; // 일치하는 줄은 넘어간다
        }

        lines.push_back(line); // 일치하지 않는 줄은 벡터에 저장
    }

    csvfile.close();

    // 과목명이 발견되었다면 파일을 덮어쓰기 모드로 열어 삭제된 데이터를 반영
    if (found) {
        ofstream outfile("subjectList.csv", ios::trunc); // 덮어쓰기 모드
        if (!outfile.is_open()) {
            cerr << "파일을 열 수 없습니다." << endl;
            return;
        }

        // 남은 데이터를 파일에 다시 저장
        for (const string& newLine : lines) {
            outfile << newLine << endl;
        }

        cout << "성공적으로 과목을 삭제하였습니다." << endl;
    }
    else {
        cout << "해당 과목을 찾을 수 없습니다." << endl;
    }
}

void rwcsv::MakeSubjectCSVFile(string subjectname, vector<string> studentNameVector, vector<int> studentNums) {
    // 파일 이름 설정
    string filename = subjectname + ".csv";

    // 파일 생성
    ofstream csvfile(filename);

    // 파일 열기 성공 여부 확인
    if (csvfile.is_open()) {
        // 헤더 작성
        csvfile << "studentname,studentnumber,attendance,midtermTest,finalTest,assignment\n";

        // 학생 정보 기록
        for (size_t i = 0; i < studentNameVector.size(); ++i) {
            csvfile << studentNameVector[i] << "," // 이름
                << studentNums[i] << ","     // 학번
                << "," << "," << "," << "\n"; // 점수는 빈 상태로
        }

        csvfile.close(); // 파일 닫기
        cout << "CSV 파일이 생성되었습니다: " << filename << endl;
    }
    else {
        cerr << "CSV 파일을 생성할 수 없습니다: " << filename << endl;
    }
}

void rwcsv::AddSubjectToStudent(const string& subjectToAdd, const vector<int>& studentNumbers) {
    ifstream infile("studentsSubjects.csv"); // 기존 CSV 파일 열기
    vector<string> fileLines; // 전체 파일 데이터를 저장
    bool changesMade = false; // 변경 여부 확인

    // 파일 열기 실패 처리
    if (!infile.is_open()) {
        cerr << "파일을 열 수 없습니다" << endl;
        return;
    }

    string line;
    // 첫 줄(헤더) 복사
    if (getline(infile, line)) {
        fileLines.push_back(line);
    }

    // 나머지 줄(학생 데이터) 처리
    while (getline(infile, line)) {
        stringstream lineStream(line);
        vector<string> row;
        string token;

        // 각 열을 읽어 벡터에 저장
        while (getline(lineStream, token, ',')) {
            row.push_back(token);
        }

        // 학번(두 번째 열) 확인
        if (row.size() > 1) {
            int studentNumber = stoi(row[1]); // 학번
            // 학생 번호가 vector에 포함된 경우 과목 추가
            if (find(studentNumbers.begin(), studentNumbers.end(), studentNumber) != studentNumbers.end()) {
                // 과목 추가
                row.push_back(subjectToAdd);
                changesMade = true;
            }
        }

        // 변경된 데이터를 다시 한 줄로 조합
        string updatedLine;
        for (size_t i = 0; i < row.size(); ++i) {
            updatedLine += row[i];
            if (i < row.size() - 1) updatedLine += ",";
        }
        fileLines.push_back(updatedLine);
    }

    infile.close(); // 파일 닫기

    // 변경 사항이 없으면 종료
    if (!changesMade) {
        cout << "변경된 내용이 없습니다." << endl;
        return;
    }

    // 변경된 데이터를 파일에 다시 쓰기
    ofstream outfile("studentsSubjects.csv");
    if (outfile.is_open()) {
        for (const string& line : fileLines) {
            outfile << line << "\n";
        }
        outfile.close();
        cout << "과목이 성공적으로 추가되었습니다." << endl;
    }
    else {
        cerr << "파일을 열 수 없습니다" << endl;
    }
}
void rwcsv::RemoveSubjectFromStudents(const string& subjectToRemove) {
    ifstream infile("studentsSubjects.csv"); // 기존 CSV 파일 열기
    vector<string> fileLines; // 전체 파일 데이터를 저장
    bool changesMade = false; // 변경 여부 확인

    // 파일 열기 실패 처리
    if (!infile.is_open()) {
        cerr << "파일을 열 수 없습니다" << endl;
        return;
    }

    string line;
    // 첫 줄(헤더) 복사
    if (getline(infile, line)) {
        fileLines.push_back(line);
    }

    // 나머지 줄(학생 데이터) 처리
    while (getline(infile, line)) {
        stringstream lineStream(line);
        vector<string> row;
        string token;

        // 각 열을 읽어 벡터에 저장
        while (getline(lineStream, token, ',')) {
            row.push_back(token);
        }

        // 과목들에서 삭제할 과목이 있는지 확인
        if (row.size() > 2) { // 과목이 있는지 확인
            bool subjectRemoved = false;
            for (size_t i = 2; i < row.size(); ++i) {
                if (row[i] == subjectToRemove) {
                    // 과목을 삭제하고 나머지 과목을 앞으로 당긴다
                    row.erase(row.begin() + i);
                    subjectRemoved = true;
                    changesMade = true;
                    break;
                }
            }

            // 과목 삭제가 이루어졌다면 업데이트된 행을 기록
            if (subjectRemoved) {
                string updatedLine;
                for (size_t i = 0; i < row.size(); ++i) {
                    updatedLine += row[i];
                    if (i < row.size() - 1) updatedLine += ",";
                }
                fileLines.push_back(updatedLine);
            }
            else {
                fileLines.push_back(line); // 과목이 없으면 기존 줄을 그대로 저장
            }
        }
    }

    infile.close(); // 파일 닫기

    // 변경 사항이 없으면 종료
    if (!changesMade) {
        cout << "삭제된 과목이 없습니다." << endl;
        return;
    }

    // 변경된 데이터를 파일에 다시 쓰기
    ofstream outfile("studentsSubjects.csv");
    if (outfile.is_open()) {
        for (const string& line : fileLines) {
            outfile << line << "\n";
        }
        outfile.close();
        cout << "과목이 성공적으로 삭제되었습니다." << endl;
    }
    else {
        cerr << "파일을 열 수 없습니다" << endl;
    }
}
string rwcsv::adjustSubjectName(const string& subjectName) {
    string adjustedName;
    vector<string> existingSubjects; // 존재하는 과목명을 저장할 벡터

    // subjectList.csv 파일 읽기
    ifstream subjectFile("subjectList.csv");
    if (subjectFile.is_open()) {
        string line, subject;
        getline(subjectFile, line); // 헤더 건너뛰기

        // CSV 파일에서 과목명만 읽어서 저장
        while (getline(subjectFile, line)) {
            stringstream ss(line);
            getline(ss, subject, ','); // 과목명 읽기
            existingSubjects.push_back(subject);
        }
        subjectFile.close();
    }
    else {
        cerr << "subjectList.csv 파일을 열 수 없습니다." << endl;
        return subjectName + "1반"; // 기본적으로 "1반" 추가
    }

    // "1반", "2반", ..., N반을 순차적으로 확인하여 없는 번호를 찾음
    int suffix = 1; // 반 번호 시작
    while (true) {
        adjustedName = subjectName + to_string(suffix) + "반";
        if (find(existingSubjects.begin(), existingSubjects.end(), adjustedName) == existingSubjects.end()) {
            break; // 중복되지 않는 과목명을 찾으면 종료
        }
        suffix++; // 다음 반 번호 확인
    }

    return adjustedName;
}

#pragma endregion


#pragma region 과목에 대한 콘솔 print 함수
vector<string> rwcsv::PrintSubjectList(const Professor& prof) {

    string filename = "subjectList.csv";
    ifstream csvFile(filename);

    vector<string> subjects;

    cout << "=================================================================" << endl;
    cout << "|                         Subject List                          |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num     |  Subject             |        Professor Num         |" << endl;
    cout << "=================================================================" << endl;

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // 헤더 건너뛰기
        // cout numbering
        int numbering = 0;
        // 교과목 이름
        string subject;
        //교번
        string professornum;

        while (getline(csvFile, line)) {
            stringstream ss(line);

            getline(ss, subject, ',');     // 이름
            getline(ss, professornum, ',');    // 교번

            numbering += 1;
            if (prof.getNumber() == stoi(professornum)) {
                cout << "| " << setw(8) << left << numbering
                    << "| " << setw(21) << left << subject
                    << "| " << setw(29) << left << professornum
                    << "|" << endl;
            }
            subjects.push_back(subject);
        }
    }
    csvFile.close();
    return subjects;
    cout << "=================================================================" << endl;
}

/// <summary>
/// 과목의 전체 List를 출력
/// </summary>
void rwcsv::PrintSubjectList() {
    string filename = "subjectList.csv";
    ifstream csvFile(filename);

    cout << "=================================================================" << endl;
    cout << "|                         Subject List                          |" << endl;
    cout << "=================================================================" << endl;
    cout << "| Num     |  Subject             |        Professor Num         |" << endl;
    cout << "=================================================================" << endl;

    if (csvFile.is_open()) {
        string line;
        getline(csvFile, line); // 헤더 건너뛰기
        int numbering = 0;      // 출력 번호
        string subject, professornum;

        while (getline(csvFile, line)) {
            stringstream ss(line);
            getline(ss, subject, ',');      // 과목명
            getline(ss, professornum, ','); // 교번

            numbering++;
            cout << "| " << setw(8) << left << numbering
                << "| " << setw(21) << left << subject
                << "| " << setw(29) << left << professornum
                << "|" << endl;
        }
    }
    else {
        cerr << "Failed to open file: " << filename << endl;
    }
    cout << "=================================================================" << endl;
}

/// <summary>
/// 새로운 과목에 대한 새로운 .csv를 생성하고 거기에 학번들을 저장하는 함수
/// </summary>
/// <param name="subjectname">과목명, 과목명 + "csv"로 .csv 생성</param>
/// <param name="studentsnum">header로 들어갈 학번들</param>
#pragma endregion

/// <summary>
/// 교수의 이름을 받으면 그 교수가 배정된 과목만 출력
/// </summary>
/// <param name="prof"></param>


/// <summary>
/// 특정 학생의 이름을 입력 받아 학생이 수강중인 과목을 조회하는 함수
/// </summary>
/// <param name="filename"></param>
/// <param name="studentName"></param>
/// <returns></returns>
vector<string> rwcsv::PrintStudentSubject(const string & filename, const string & studentName) {
    ifstream file(filename); // 파일 열기

    // 파일이 열리지 않으면 오류 메시지 출력
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return {}; //빈 벡터 반환
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
        if (isFirstline) {
            isFirstline = false;
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
        return {};
    }

    if (courses.empty()) {
        cout << "수강 중인 과목이 없습니다.\n";
        return {};
    }

    // 수강 과목 출력
    cout << "===================================\n";
    cout << "현재 수강 중인 과목 내역입니다.\n";
    for (size_t i = 0; i < courses.size(); ++i) {
        cout << i + 1 << ". " << courses[i] << '\n';
    }
    cout << "===================================\n";
    return courses;
}

/// <summary>
/// 학생과 과목명을 입력 받아서 성적을 산출하는 함수
/// </summary>
/// <param name="filename"></param>
/// <param name="studentName"></param>
void rwcsv::PrintStudentGrade(const string& filename, const string& studentName) {
    string csvfilename = filename + ".csv";
    ifstream file(csvfilename); // 파일 열기

    // 파일 열기 실패 시 오류 메시지 출력 후 종료
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << csvfilename << endl;
        return;
    }

    string line;
    bool studentFound = false;

    // CSV 파일의 헤더를 읽어서 출력
    if (getline(file, line)) {
        cout << left << setw(20) << "학생 이름"
            << setw(15) << "학번"
            << setw(20) << "과목"
            << setw(20) << "출석 점수"
            << setw(20) << "중간고사 점수"
            << setw(20) << "기말고사 점수"
            << setw(20) << "과제 점수" << endl;
    }
    else {
        cerr << "CSV 파일의 헤더를 읽을 수 없습니다: " << csvfilename << endl;
        return;
    }

    // 파일을 한 줄씩 읽음
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number, attendance, midterm, finalExam, assignment;

        // CSV 데이터 파싱
        getline(ss, name, ',');
        getline(ss, number, ',');
        getline(ss, attendance, ',');
        getline(ss, midterm, ',');
        getline(ss, finalExam, ',');
        getline(ss, assignment, ',');

        // 학생 이름이 매개변수와 일치하면 출력
        if (name == studentName) {
            cout << left
                << setw(20) << name
                << setw(15) << number
                << setw(20) << filename
                << setw(20) << attendance
                << setw(20) << midterm
                << setw(20) << finalExam
                << setw(20) << assignment
                << endl;
            studentFound = true;
            break;
        }
    }

    // 학생을 찾지 못한 경우
    if (!studentFound) {
        cout << "해당 학생을 찾을 수 없습니다: " << studentName << endl;
    }

    file.close(); // 파일 닫기

    // 사용자 입력 요청 (루프와 무관하게 위치 조정)
    int num;
    cout << "확인하셨다면 -1를 입력해주세요: ";
    cin >> num;
}

/// <summary>
/// 학생의 모든 과목의 성적을 조회하는 함수
/// </summary>
/// <param name="filenames"></param>
/// <param name="studentName"></param>
void rwcsv::PrintALLStudentGrade(vector<string> filenames, string studentName) {
    cout << left
        << setw(20) << "학생 이름" << setw(15) << "학번" << setw(20) << "과목 " << setw(20)
        << setw(20) << "출석 점수" << setw(20) << "중간고사 점수" << setw(20) << "기말고사 점수" << setw(20) << "과제 점수" << endl;

    vector<string> noGradeSubject;
    for (string filename : filenames) {
        string csvfilename = filename + ".csv";
        ifstream file(csvfilename); // 파일 열기

        // 파일 열기 실패 시 오류 메시지 출력 후 종료
        // 파일 열기 실패 시 오류 메시지 출력 후 종료
        if (!file.is_open()) {
            cerr << "파일을 열 수 없습니다: " << csvfilename << endl;
            return;
        }

        string line;
        bool studentFound = false;

        // 파일을 한 줄씩 읽음
        while (getline(file, line)) {
            // 비어 있는 줄은 건너뜀
            if (line.empty()) continue;

            stringstream ss(line);
            string name, number, attendance, midterm, finalExam, assignment;

            // CSV 데이터 파싱
            if (!getline(ss, name, ',') || !getline(ss, number, ',') ||
                !getline(ss, attendance, ',') || !getline(ss, midterm, ',') ||
                !getline(ss, finalExam, ',') || !getline(ss, assignment, ',')) {
                noGradeSubject.push_back(filename);
            }

            // 학생 이름이 매개변수와 일치하면 출력
            if (name == studentName) {
                cout << left
                    << setw(20) << name
                    << setw(15) << number
                    << setw(20) << filename
                    << setw(20) << attendance
                    << setw(20) << midterm
                    << setw(20) << finalExam
                    << setw(20) << assignment
                    << endl;
                studentFound = true;
                break;
            }
        }

        // 학생을 찾지 못한 경우
        if (!studentFound) {
            cout << "해당 학생을 찾을 수 없습니다: " << studentName << endl;
        }

       
        file.close(); // 파일 닫기
    }
    for (string i : noGradeSubject) {
        cout << i << ", ";
    }
    cout << "이 아직 성적이 입력되어지지 않았습니다." << endl;
    int num;
    cout << "확인하셨다면 -1를 입력해주세요" << endl;
    cin >> num;
}
void rwcsv::UpdateAllStudentsGrade(const string& subjectName, const int& categorynum) {
    string filename = subjectName + ".csv"; // 과목에 해당하는 파일 이름
    ifstream infile(filename); // 기존 파일 읽기
    vector<string> fileLines; // 파일의 모든 줄을 저장
    vector<string> head;
    int categoryIndex = categorynum - 1; // 수정할 평가 항목의 인덱스 (0-based)

    // 파일 열기 실패 시 처리
    if (!infile.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;
    // 첫 줄(헤더) 읽기
    if (getline(infile, line)) {
        fileLines.push_back(line);
        stringstream lineStream(line);
        string token;
        while (getline(lineStream, token, ',')) {
            head.push_back(token); // 헤더를 그대로 유지
        }
    }
    else {
        cerr << "CSV 파일이 비어 있거나 헤더를 읽을 수 없습니다: " << filename << endl;
        infile.close();
        return;
    }

    // 나머지 파일 줄 읽기
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string token;
        vector<string> row;

        // 한 줄을 ',' 기준으로 파싱
        while (getline(lineStream, token, ',')) {
            row.push_back(token); // 비어 있는 필드도 빈 문자열로 추가
        }

        // 필드 개수 부족 시 빈 문자열 추가
        while (row.size() < head.size()) {
            row.push_back(""); // 부족한 필드만큼 빈 값 추가
        }

        // 평가 항목의 유효성 검사
        if (row.size() <= categoryIndex + 2) {
            cerr << "CSV 데이터 형식이 올바르지 않습니다: " << line << endl;
            fileLines.push_back(line); // 원본 줄 유지
            continue;
        }

        int newScore;
        while (true) {
            cout << row[0] << " 학생의 " << head[categoryIndex + 2] << " 점수를 입력해주세요." << endl;
            cout << ">> 입력: ";
            cin >> newScore;
            if (categoryIndex == 0 && newScore > 10) {
                cout << "출석 점수는 10점을 초과할 수 없습니다." << endl;
            }
            else if (categoryIndex != 0 && newScore > 30) {
                cout << "점수는 30점을 초과할 수 없습니다." << endl;
            }
            else {
                break;
            }
        }

        // 해당 항목의 점수를 새로운 값으로 업데이트
        row[categoryIndex + 2] = to_string(newScore);

        // 업데이트된 줄을 재구성해서 저장
        string updatedLine;
        for (size_t i = 0; i < row.size(); ++i) {
            updatedLine += row[i];
            if (i < row.size() - 1) updatedLine += ","; // 마지막이 아닌 경우 ',' 추가
        }
        fileLines.push_back(updatedLine);
    }

    infile.close(); // 파일 닫기

    // 수정된 내용을 파일에 다시 저장
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const string& fileLine : fileLines) {
            outfile << fileLine << "\n";
        }
        outfile.close();
        cout << "모든 학생의 점수가 성공적으로 업데이트되었습니다." << endl;
    }
    else {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
    }
}




void rwcsv::UpdateStudentGrade(const string& subjectName, int studentNumber, const int& categorynum, int score) {
    string filename = subjectName + ".csv"; // 과목에 해당하는 파일 이름
    ifstream infile(filename); // 기존 파일 읽기
    vector<string> fileLines; // 파일의 모든 줄을 저장
    bool studentFound = false; // 학생이 발견되었는지 여부
    int categoryIndex = categorynum -1; // 수정할 평가 항목의 인덱스

    // 파일 열기 실패 시 처리
    if (!infile.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;
    // 첫 줄(헤더) 읽기
    if (getline(infile, line)) {
        fileLines.push_back(line);
        stringstream headerStream(line);
        string columnName;
        int index = 0;
    }

    // 평가 항목이 헤더에 없을 경우 에러 처리
    if (categoryIndex == -1) {
        cerr << "평가 항목을 찾을 수 없습니다: " << categoryIndex << endl;
        infile.close();
        return;
    }

    // 나머지 파일 줄 읽기
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string token;
        vector<string> row;
        while (getline(lineStream, token, ',')) {
            row.push_back(token);
        }

        // 학번이 일치하는 학생 발견 시 점수 업데이트
        if (stoi(row[1]) == studentNumber) { // 1번 인덱스에 학번이 있다고 가정
            if (row.size() > categoryIndex) {
                row[categoryIndex +2] = to_string(score); // 점수 업데이트
            }
            studentFound = true;
        }

        // 업데이트된 줄을 재구성해서 저장
        string updatedLine;
        for (size_t i = 0; i < row.size(); ++i) {
            updatedLine += row[i];
            if (i < row.size() - 1) updatedLine += ",";
        }
        fileLines.push_back(updatedLine);
    }

    infile.close(); // 파일 닫기

    // 학생이 발견되지 않은 경우
    if (!studentFound) {
        cerr << "해당 학번의 학생을 찾을 수 없습니다: " << studentNumber << endl;
        return;
    }

    // 수정된 내용을 파일에 다시 저장
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const string& fileLine : fileLines) {
            outfile << fileLine << "\n";
        }
        outfile.close();
        cout << "점수가 성공적으로 업데이트되었습니다." << endl;
    }
    else {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
    }
}

void rwcsv::PrintStudentsList(string subjectname) {
    string csvfilename = subjectname + ".csv";
    ifstream file(csvfilename); // 파일 열기

    // 파일 열기 실패 시 오류 메시지 출력 후 종료
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << csvfilename << endl;
        return;
    }

    string line;

    // 첫 번째 라인 (헤더) 출력
    cout << "============================================학생 목록======================================" << endl;
    cout << "===========================================================================================" << endl;

    // 헤더 출력
    cout << left
        << setw(15) << "Name"
        << setw(15) << "Number"
        << setw(15) << "Attendance(10)"
        << setw(15) << "Midterm(30)"
        << setw(15) << "Final Exam(30)"
        << setw(15) << "Assignment(30)"
        << endl;
    cout << "===========================================================================================" << endl;

    getline(file, line);
    // 파일을 한 줄씩 읽음
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number, attendance, midterm, finalExam, assignment;

        // CSV 데이터 파싱
        getline(ss, name, ',');
        getline(ss, number, ',');
        getline(ss, attendance, ',');
        getline(ss, midterm, ',');
        getline(ss, finalExam, ',');
        getline(ss, assignment, ',');

        // 데이터 출력
        cout << left
            << setw(15) << name
            << setw(15) << number
            << setw(15) << attendance
            << setw(15) << midterm
            << setw(15) << finalExam
            << setw(15) << assignment
            << endl;
    }

    cout << "===========================================================================================" << endl;
    file.close(); // 파일 닫기
}


