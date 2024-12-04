#include <iostream>
#include <algorithm>
#include "Professor.h"
#include "rwcsv.h"


using namespace std;

void Professor::main() const
{
    string whichSubject;
    int profMode;

    while (true) {
        system("cls");
        string filename = "professor.csv";

        cout << "=======================�� ���ǽ�=======================\n";
        // 3.1. ���� ���� : ���� ����Ʈ ��°���� �Է�
        // �������� �Ҵ�� ������ subject.csv���� �ҷ�����. �̸� ���� subject.csv���� name, subject �������� ����Ǿ��ִ� ����
        string profName = this->getName(); //�α��� �������� ���� �̸� ������ ���� �����ؾ� ��
        cout << getName() + "������ " + "ȯ���մϴ�." << endl;

        //--������ �ִ��� üũ�ϱ�--
        vector<string> subjects = rwcsv().PrintSubjectList(*this);
        cout << "=================================================================\n";

        cout << "������ ���ǽ��� �����ϼ���." << endl << endl;

        string subjectName;
        while (true) {
            cout << ">> �Է�(ex. ��ǻ�����α׷���): ";
            cin >> subjectName;
            if (find(subjects.begin(), subjects.end(), subjectName) != subjects.end())
            {
                break;
            }
            else
            {
                cout << "�Է��Ͻ� ������� �������� �ʽ��ϴ�: " << subjectName << endl << endl;
            }
        }
        
        

        rwcsv().PrintStudentsList(subjectName);

        cout << "1. ��ü ���� �Է� " << "2. �л��� ���� �Է� " << endl;
        cout << ">> �Է�: ";
        cin >> profMode;
        
        int category, studentNumber, score;

        if (profMode == 1) {
            cout << "������ �� �׸��� �Է��ϼ���." << endl <<
                "1. attendance, 2.midtermTest, 3.finalTest, 4. assignment" << endl;
            cout << ">> �Է�: ";
            cin >> category;
            rwcsv().UpdateAllStudentsGrade(subjectName, category);
        }
        else if (profMode == 2) {
         
            cout << "�л� �й��� �Է��ϼ���." << endl;
            cout << ">> �Է�: ";
            cin >> studentNumber;
            cout << endl;

            cout << "������ �� �׸��� �Է��ϼ���." << endl <<
                "1. attendance, 2.midtermTest, 3.finalTest, 4. assignment" << endl;
            cout << ">> �Է�: ";
            cin >> category;
            while (true) {
                cout << "������ �Է��ϼ���. " << endl;
                cout << ">> �Է�: ";
                cin >> score;
                cout << endl;
                if (category == 1 && score > 10) {
                    cout << "�⼮ ������ 10���� �ʰ� �� �� �����ϴ�." << endl;
                }
                else if (category != 1 && score > 30) {
                    cout << "�⼮ ������ 30���� �ʰ� �� �� �����ϴ�." << endl;
                }
                else {
                    break;
                }
            }
            rwcsv().UpdateStudentGrade(subjectName, studentNumber, category, score);
        }
    }
}