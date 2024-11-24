#include <iostream>
#include <string>
#include <windows.h> 
#include "rwcsv.h" // 가정: rwcsv 클래스와 관련된 헤더 파일
#include "admin.h" // 가정: admin 클래스와 관련된 헤더 파일
using namespace std;
int main() {
    
    system("cls");

    rwcsv csv; // rwcsv 객체 생성

    string num; // 사용자 입력 저장
    string id, pw; // 로그인 정보 저장

    // 프로그램 헤더 출력
    cout << "+---------------------------------------------------------+\n";
    cout << "|                   Grade Management Program              |\n";
    cout << "|                     Team: Shakespeare                   |\n";
    cout << "+---------------------------------------------------------+\n\n";



    while (true) {
        // 메뉴 출력
        cout << "==================== Select Your Role ====================\n";
        cout << "1. 관리자(Admin)   2. 교수(Professor)   3. 학생(Student)\n";
        cout << "4. 프로그램 종료(Exit)\n";
        cout << "==========================================================\n";
        cout << ">> 입력: ";
        cin >> num;
        system("cls");

        // 관리자 로그인
        if (num == "1" || num == "관리자") {
            cout << "==================== Admin Login =======================\n";
            cout << "아이디: ";
            cin >> id;
            cout << "비밀번호: ";
            cin >> pw;

            if (id == "admin" && pw == "admin") {
                
                admin ad;
                ad.adminMain(); // 관리자로 로그인 후 메인 화면
            }
            else {
                cout << "\n아이디 또는 비밀번호가 틀렸습니다. 다시 시도하세요.\n\n";
            }
            break;
        }

        // 교수 로그인
        else if (num == "2" || num == "교수") {
            cout << "=================== Professor Login ====================\n";
            cout << "아이디: ";
            cin >> id;
            cout << "비밀번호: ";
            cin >> pw;

            User* my = csv.UserLogin("professor.csv", id, pw);
            if (my != nullptr) {
                cout << "\n교수 로그인 성공!\n\n";
                my->main(); // 교수 메인 화면
            }
            else {
                cout << "로그인 실패. 아이디 또는 비밀번호를 확인하세요.\n\n";
            }
        }

        // 학생 로그인
        else if (num == "3" || num == "학생") {
            cout << "==================== Student Login =====================\n";
            cout << "아이디: ";
            cin >> id;
            cout << "비밀번호: ";
            cin >> pw;

            User* my = csv.UserLogin("student.csv", id, pw);
            if (my != nullptr) {
                cout << "학생 로그인 성공!\n\n";
                my->main(); // 학생 메인 화면
            }
            else {
                cout << "로그인 실패. 아이디 또는 비밀번호를 확인하세요.\n\n";
            }
            break;
        }

        // 프로그램 종료
        else if (num == "4" || num == "exit" || num == "Exit") {
            cout << "================= Program Terminated ===================\n";
            cout << "프로그램을 종료합니다. 감사합니다.\n";
            cout << "=======================================================\n";
            break;
        }

        // CSV 테스트 출력 (디버깅용 옵션)
        else if (num == "test") {
            cout << "================= Student CSV Data =====================\n";
            rwcsv().PrintUserCSV("student");
        }

        // 잘못된 입력 처리
        else {
            cout << "❌ 유효하지 않은 선택입니다. 다시 시도해주세요.\n\n";
        }
    }

    return 0;
}
