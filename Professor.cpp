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
        cout << getName() + "님 " + "환영합니다." << endl;

        rwcsv().PrintSubjectList(*this);
        cout << "입장할 강의실을 선택하세요." << endl;
        cout << ">> 입력(ex. 컴퓨터프로그래밍): ";

        string subjectName;
        cin >> subjectName;

        cout << "1. 평가항목 생성 " << "2. 성적 입력 " << endl;
        cin >> profMode;
        if (profMode == 1) {
            
        }
        else if (profMode == 2) {
            // 성적 입력 함수 삽입
        }
    }
}