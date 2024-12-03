#include "Professor.h"
#include "rwcsv.h"

void Professor::main() const
{
    string whichSubject;
    int profMode;

    while (true) {
        system("cls");
        string filename = "professor.csv";

        cout << "=======================내 강의실=======================\n";
        // 3.1. 과목 선택 : 과목 리스트 출력/과목명 입력
        // 교수한테 할당된 과목을 subject.csv에서 불러오기. 이를 위해 subject.csv에는 name, subject 형식으로 저장되어있다 가정
        string profName = this->getName(); //로그인 정보에서 교수 이름 가져와 변수 설정해야 함
        cout << getName() + "교수님 " + "환영합니다." << endl;

        rwcsv().PrintSubjectList(*this);
        cout << "입장할 강의실을 선택하세요." << endl;
        cout << ">> 입력(ex. 컴퓨터프로그래밍): ";

        string subjectName;
        cin >> subjectName;

        rwcsv().PrintStudentsList(subjectName);

        cout << "1. 전체 성적 입력 " << "2. 학생별 성적 입력 " << endl;
        cout << ">> 입력: ";
        cin >> profMode;
        
        int category, studentNumber, score;

        if (profMode == 1) {
            cout << "수정할 평가 항목을 입력하세요." << endl <<
                "1. attendance, 2.midtermTest, 3.finalTest, 4. assignment : " << endl;
            cout << ">> 입력: ";
            cin >> category;
            rwcsv().UpdateAllStudentsGrade(subjectName, category);
        }
        else if (profMode == 2) {
         
            cout << "학생 학번을 입력하세요: " << endl;
            cout << ">> 입력: ";
            cin >> studentNumber;

            cout << "수정할 평가 항목을 입력하세요." << endl <<
                "1. attendance, 2.midtermTest, 3.finalTest, 4. assignment : " << endl;
            cout << ">> 입력: ";
            cin >> category;
            while (true) {
                cout << "점수를 입력하세요: " << endl;
                cout << ">> 입력: ";
                cin >> score;
                if (category == 0 && score > 11) {
                    cout << "출석 점수는 10점을 초과 할 수 없습니다." << endl;
                }
                else if (category != 0 && score > 31) {
                    cout << "출석 점수는 30점을 초과 할 수 없습니다." << endl;
                }
                else {
                    break;
                }
            }
            
            cin >> score;

            rwcsv().UpdateStudentGrade(subjectName, studentNumber, category, score);
        }
    }
}