#include <iostream>
#include <algorithm>
#include "Professor.h"
#include "rwcsv.h"

using namespace std;

void Professor::main() const
{
    string whichSubject;
    int profMode;

    system("cls");
    while (true) {
        string filename = "professor.csv";

        cout << "=======================내 강의실=======================\n";
        // 3.1. 과목 선택 : 과목 리스트 출력과목명 입력
        // 교수한테 할당된 과목을 subject.csv에서 불러오기. 이를 위해 subject.csv에는 name, subject 형식으로 저장되어있다 가정
        string profName = this->getName(); //로그인 정보에서 교수 이름 가져와 변수 설정해야 함
        cout << getName() + "교수님 " + "환영합니다.\n\n";
        cout << "이번 학기에 맡고 계신 강의 목록입니다.\n";

        //--과목이 있는지 체크하기--
        vector<string> subjects = rwcsv().PrintSubjectList(*this);
        cout << "=================================================================\n";

        cout << "입장할 강의실을 선택하세요." << endl << endl;

        string subjectName;
        while (true) {
            cout << ">> 입력(ex. 객체지향프로그래밍1반): ";
            cin >> subjectName;
            if (find(subjects.begin(), subjects.end(), subjectName) != subjects.end()) {
                break;
            }
            else {
                cout << "입력하신 과목명이 존재하지 않습니다: " << subjectName << endl << endl;
            }
        }

        rwcsv().PrintStudentsList(subjectName);

        while (true) {
            cout << "1. 전과목 성적 조회 " << "2. 학생별 성적 입력 " << endl;
            cout << ">> 입력: ";
            cin >> profMode;

            if (cin.fail() || (profMode != 1 && profMode != 2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
            }
            else {
                break;
            }
        }

        int category, studentNumber, score;

        if (profMode == 1) {
            while (true) {
                cout << "수정할 평가 항목을 입력하세요." << endl
                    << "1. attendance, 2. midtermTest, 3. finalTest, 4. assignment" << endl;
                cout << ">> 입력: ";
                cin >> category;

                if (cin.fail() || category < 1 || category > 4) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "잘못된 입력입니다. 1~4 사이의 숫자를 입력하세요." << endl;
                }
                else {
                    break;
                }
            }

            rwcsv().UpdateAllStudentsGrade(subjectName, category);
        }
        else if (profMode == 2) {
            while (true) {
                cout << "학생 학번을 입력하세요." << endl;
                cout << ">> 입력: ";
                cin >> studentNumber;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "잘못된 입력입니다. 숫자를 입력하세요." << endl;
                }
                else {
                    break;
                }
            }

            while (true) {
                cout << "수정할 평가 항목을 입력하세요." << endl
                    << "1. attendance, 2. midtermTest, 3. finalTest, 4. assignment" << endl;
                cout << ">> 입력: ";
                cin >> category;

                if (cin.fail() || category < 1 || category > 4) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "잘못된 입력입니다. 1~4 사이의 숫자를 입력하세요." << endl;
                }
                else {
                    break;
                }
            }

            while (true) {
                cout << "점수를 입력하세요." << endl;
                cout << ">> 입력: ";
                cin >> score;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "잘못된 입력입니다. 숫자를 입력하세요." << endl;
                }
                else if (category == 1 && score > 10) {
                    cout << "출석 점수는 10점을 초과 할 수 없습니다." << endl;
                }
                else if (category != 1 && score > 30) {
                    cout << "시험 및 과제 점수는 30점을 초과 할 수 없습니다." << endl;
                }
                else {
                    break;
                }
            }

            rwcsv().UpdateStudentGrade(subjectName, studentNumber, category, score);
        }
    }
}
