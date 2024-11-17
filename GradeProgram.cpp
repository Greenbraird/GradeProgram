#include <iostream>
#include <cstring>
#include <windows.h>

#include "rwcsv.h"
#include "admin.h"
#include "Login.h"

using namespace std;
//ex
int main()
{
    system("cls");
    rwcsv csv;

    string num;
    string id;
    string pw;

    cout << "=======================================================\n";
    cout << "=====================Grade Program=====================\n";
    cout << "===================Team. Shakespeare===================\n";
    cout << "=======================================================\n\n";

    cout << "================숫자를 입력해 주세요.==================\n";
    cout << "1. 관리자  2. 교수 3. 학생 4. 프로그램 종료\n"; 
    

    while (true) {
        cin >> num;
        system("cls");


        //관리자로 로그인
        if (num == "1" || num == "관리자") {
            

            cout << "아이디: ";
            cin >> id;
            cout << "비밀번호: ";
            cin >> pw;
            
            if (id == "admin" && pw == "admin") { 
                cout << "관리자로 로그인 되었습니다.";
                admin ad = admin();
                ad.adminMain();
            }
            else { cout << "아이디 및 비밀번호가 틀렸습니다"; }
            break;
        }


        //교수로 로그인
        else if (num == "2" || num == "교수") {
            
            cout << "아이디: ";
            cin >> id;
            cout << "비밀번호: ";
            cin >> pw;

            //로그인에 성공하면 true, 실패하면 false
            User* my = csv.UserLogin("professor.csv", id, pw);
            my->main();
        }

        //학생으로 로그인
        else if (num == "3" || num == "학생") {

            cout << "아이디: ";
            cin >> id;
            cout << "비밀번호: ";
            cin >> pw;

            //로그인에 성공하면 true, 실패하면 false
            User* my = csv.UserLogin("student.csv", id, pw);
            my->main();

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

