#include <iostream>
#include <cstring>

#include "rwscv.h"
#include "Login.h"

using namespace std;

int main()
{
    string num;

    cout << "=======================================================\n";
    cout << "=====================Grade Program=====================\n";
    cout << "=======================================================\n\n";

    cout << "================숫자를 입력해 주세요.==================\n";
    cout << "1. 관리자  2. 교수 3. 학생 4. 프로그램 종료\n";
    
    while (true) {
        cin >> num;
        if (num == "1" || num == "관리자") {
            string id;
            string pw;

            cout << "아이디: ";
            cin >> id;
            cout << "비밀번호: ";
            cin >> pw;
            
            if (id == "admin" && pw == "admin") { cout << "관리자로 로그인 되었습니다.";}
            else { cout << "아이디 및 비밀번호가 틀렸습니다"; }
            break;
        }
        else if (num == "2" || num == "교수") {
            cout << "회원가입\n";
            //회원가입
            break;
        }
        else if (num == "3" || num == "학생\n") {
            cout << "프로그래밍 종료\n";
            break;
        }
        else if(num == "4" || num == "test")
        {

        }
        else{ 
            cout << "다시 시도해주세요. \n";
        }
    }

    
}

