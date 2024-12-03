#include "Professor.h"
#include "rwcsv.h"

void Professor::main()
{
    while (true) {
        system("cls");
        string filename = "professor.csv";
        int profMode;

        cout << "=======================내 강의실=======================\n";
        // 3.1. 과목 선택 : 과목 리스트 출력/과목명 입력
        // 교수한테 할당된 과목을 subject.csv에서 불러오기. 이를 위해 subject.csv에는 name, subject 형식으로 저장되어있다 가정
        string profName = this->getName(); //로그인 정보에서 교수 이름 가져와 변수 설정해야 함
        cout << getName() + "님 " + "환영합니다." << endl;

        rwcsv().PrintSubjectList(*this);
        cout << "입장할 강의실을 선택하세요." << endl;
        cout << ">> 입력(ex. 컴퓨터프로그래밍): ";

        string subjectName;
        cin >> subjectName;
        string subjectFilename = subjectName + '.csv';

        rwcsv().PrintStudentsList(subjectName);

        cout << "1. 평가 항목 선택 입력 " << "2. 학생별 성적 입력" << endl;
        cin >> profMode;

        if (profMode == 1) {
            inputGrade_selectedHeader(subjectFilename);
        }

        else if (profMode == 2) {
            inputGrade_searchStudent(subjectFilename);
        }
    }
}

//범위 내의 점수를 입력하게 하는 유효성 검사 함수
int inputScore(const string& prompt, int min, int max) {
    int score;
    while (true) {
        cout << prompt;
        cin >> score;

        if (cin.fail() || score < min || score > max) {
            cout << "유효하지 않은 입력입니다. " << min << "에서 " << max << " 사이의 값을 입력하세요." << endl;
            cin.clear(); // 입력 상태 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 잘못된 입력 버림

        }
        else {
            break; // 유효한 입력을 했을 때
        }
    }
    return score;
}

//파읽을 읽어 header와 students 벡터를 반환하는 함수
pair<string, vector<string>> readFile(const string& subjectFilename) {
    fstream file(subjectFilename, ios::in);  // 파일을 읽기 모드로 연다

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << subjectFilename << endl;
        return { "", {} };  
    }

    string line;
    string header;

    getline(file, header);  

    // 학생 데이터를 저장할 벡터
    vector<string> students;

    // 학생 데이터를 파일에서 읽어들인다
    while (getline(file, line)) {
        students.push_back(line);
    }

    file.close();  // 파일을 닫음
    return { header, students };  // 헤더와 학생 데이터가 담긴 벡터 반환
}

//학생 학번을 기준으로 검색해서 수정하는 함수
void inputGrade_searchStudent(string& subjectFilename) {

    auto [header, students] = readFile(subjectFilename);

    // 학번을 입력받아 검색
    string searchNumber;
    cout << "검색할 학생의 학번을 입력하세요: ";
    cin.ignore(); // 이전 입력 버퍼 제거
    getline(cin, searchNumber);

    bool studentFound = false;

    // 각 학생에 대해 검색 및 점수 입력
    for (auto& student : students) {
        stringstream ss(student);
        string name, numberStr;

        getline(ss, name, ',');       // 이름 추출
        getline(ss, numberStr, ','); // 학번 추출

        if (numberStr == searchNumber) {
            studentFound = true;

            // 검색 결과 출력
            cout << "검색 결과" << endl;
            cout << "이름: " << name << ", 학번: " << numberStr << endl;

            // 출석, 중간고사, 기말고사, 과제 점수를 입력받음
            vector<int> scores(4); 

            scores[0] = inputScore("출석 점수를 입력하세요: ", 0, 10);
            scores[1] = inputScore("중간고사 점수를 입력하세요: ", 0, 30);
            scores[2] = inputScore("기말고사 점수를 입력하세요: ", 0, 30);
            scores[3] = inputScore("과제 점수를 입력하세요: ", 0, 30);


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

    ofstream file(subjectFilename, ios::trunc); // 기존 파일 내용을 지우고 새로 씀
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << subjectFilename << endl;
        return;
    }

    // 고정된 헤더 쓰기
    file << header << endl;
    for (const auto& student : students) {
        file << student << endl;
    }

    file.close();

    cout << "성적 입력 완료" << endl;
}

//평가 항목을 선택해 일괄 입력하는 함수
void inputGrade_selectedHeader(string& subjectFilename) {

    auto [header, students] = readFile(subjectFilename);

    // 사용자에게 입력할 단일 헤더 선택
    vector<string> allHeaders = { "출석", "중간고사", "기말고사", "과제" };
    int selectedHeaderIndex;

    cout << "입력할 평가항목을 선택하세요: (1: 출석, 2: 중간고사, 3: 기말고사, 4: 과제)\n";
    while (true) {
        cout << "선택: ";
        cin >> selectedHeaderIndex;
        if (selectedHeaderIndex >= 1 and selectedHeaderIndex <= 4) {
            --selectedHeaderIndex; // 0부터 시작하도록 조정
            break;
        }
        cout << "잘못된 선택입니다. 다시 시도하세요.\n";
    }

    // 선택된 헤더 이름
    string selectedHeader = allHeaders[selectedHeaderIndex];
    cout << "현재 평가 항목: " << selectedHeader << endl;

    int minScore = 0;
    int maxScore = (selectedHeader == "출석") ? 10 : 30;

    // 각 학생에 대해 선택된 점수 입력
    for (auto& student : students) {
        stringstream ss(student);
        string name, numberStr;
        vector<string> scores(4, ""); // 출석, 중간고사, 기말고사, 과제 점수 초기화

        getline(ss, name, ',');       // 이름 추출
        getline(ss, numberStr, ','); // 학번 추출

        for (int i = 0; i < allHeaders.size(); ++i) {
            if (!getline(ss, scores[i], ',')) {
                scores[i] = "0"; // 값이 없으면 기본값 0으로 초기화
            }
        }

        // 점수 입력
        cout << "학생: " << name << " 학번: " << numberStr << endl;
        int newScore = inputScore(selectedHeader + " 점수를 입력하세요 (현재 점수: " + scores[selectedHeaderIndex] + "): ", minScore, maxScore);
        scores[selectedHeaderIndex] = to_string(newScore);

        // 수정된 학생 데이터 생성
        stringstream newStudent;
        newStudent << name << "," << numberStr;
        for (const auto& score : scores) {
            newStudent << "," << score;
        }

        student = newStudent.str(); // 수정된 학생 데이터로 갱신
    }

    ofstream file(subjectFilename, ios::trunc); // 기존 파일 내용을 지우고 새로 씀
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << subjectFilename << endl;
        return;
    }

    // 고정된 헤더 쓰기
    file << header << endl;
    for (const auto& student : students) {
        file << student << endl;
    }

    file.close();

    cout << "선택된 점수 입력이 완료되었습니다." << endl;
}
