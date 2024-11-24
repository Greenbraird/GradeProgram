#include "Professor.h"

void Professor::main() const
{
    cout << "1. 전체 입력 " << "2. 이름 검색" << endl;
    int num;
    cin >> num;

    if (num == 1){
        inputGrade_all(subjectName);
    }
    
    else if (num == 2){
        inputGrade_search(subjectName);
    }

}

void inputGrade_all(const string& subjectName) {
    /*(예시)subject.csv가 헤더: 이름, 학번으로 구성되어 있다고 가정
    헤더를 분리한 후 headers 벡터에 저장하고 앞의 두 개(이름, 학번)를 건너뛴 뒤
    각 헤더에 해당하는 점수를 입력받음*/

    //과목명 + .csv = 파일명
    string filename = subjectName + ".csv";

    fstream file(filename, ios::in | ios::out);

    // 파일이 열리지 않으면 오류 메시지 출력
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;
    string header;

    // 첫 번째 줄은 헤더이므로 건너뛰기
    getline(file, header);

    // 헤더에서 각 열의 이름을 분리하여 저장
    stringstream headerStream(header);
    vector<string> headers;
    string headerColumn;
    while (getline(headerStream, headerColumn, ',')) {
        headers.push_back(headerColumn);
    }

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
        vector<int> scores;  

        getline(ss, name, ',');
        getline(ss, numberStr, ',');

        // 이름과 학번 출력
        cout << "이름: " << name << "학번" << numberStr << endl;

        // 헤더의 첫 두 항목(이름, 학번)을 제외한 각 헤더에 대해 점수를 입력받고 scores 벡터에 저장
        for (int i = 2; i < headers.size(); ++i) {
            string headerName = headers[i];
            int score;
            cout << headerName << " 점수를 입력하세요: ";
            cin >> score;
            scores.push_back(score);
        }

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
string header;

// 첫 번째 줄은 헤더이므로 건너뛰기
getline(file, header);

// 헤더에서 각 열의 이름을 분리하여 저장
stringstream headerStream(header);
vector<string> headers;
string headerColumn;
while (getline(headerStream, headerColumn, ',')) {
    headers.push_back(headerColumn);
}

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

    getline(ss, name, ',');
    getline(ss, numberStr, ',');

    if (name == searchName) {
        studentFound = true;

        // 이름과 학번 출력
        cout << "검색 결과" << endl << "이름: " << name << ", 학번: " << numberStr << endl;

        // 각 헤더의 첫 두 항목(이름, 학번)을 제외한 점수 입력
        vector<int> scores;
        for (int i = 2; i < headers.size(); ++i) {
            string headerName = headers[i];
            int score;
            cout << headerName << " 점수를 입력하세요: ";
            cin >> score;
            scores.push_back(score);
        }

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

//일치하는 학생이 없을 경우
if (!studentFound) {
    cout << "해당 이름의 학생을 찾을 수 없습니다: " << searchName << endl;
    return;
}

// 파일에 수정된 데이터 저장
file.clear();  // 파일 상태 플래그 초기화
file.seekp(0); // 파일 시작으로 이동

// file 객체에 header 입력
file << header << endl;
for (const auto& student : students) {
    file << student << endl; 
}

file.close();

cout << "성적 입력 완료" << endl;

}

