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

        cout << "=======================�� ���ǽ�=======================\n";
        // 3.1. ���� ���� : ���� ����Ʈ ��°���� �Է�
        // �������� �Ҵ�� ������ subject.csv���� �ҷ�����. �̸� ���� subject.csv���� name, subject �������� ����Ǿ��ִ� ����
        string profName = this->getName(); //�α��� �������� ���� �̸� ������ ���� �����ؾ� ��
        cout << getName() + "������ " + "ȯ���մϴ�.\n\n";
        cout << "�̹� �б⿡ �ð� ��� ���� ����Դϴ�.\n";

        //--������ �ִ��� üũ�ϱ�--
        vector<string> subjects = rwcsv().PrintSubjectList(*this);
        cout << "=================================================================\n";

        cout << "������ ���ǽ��� �����ϼ���." << endl << endl;

        string subjectName;
        while (true) {
            cout << ">> �Է�(ex. ��ü�������α׷���1��): ";
            cin >> subjectName;
            if (find(subjects.begin(), subjects.end(), subjectName) != subjects.end()) {
                break;
            }
            else {
                cout << "�Է��Ͻ� ������� �������� �ʽ��ϴ�: " << subjectName << endl << endl;
            }
        }

        rwcsv().PrintStudentsList(subjectName);

        while (true) {
            cout << "1. ������ ���� ��ȸ " << "2. �л��� ���� �Է� " << endl;
            cout << ">> �Է�: ";
            cin >> profMode;

            if (cin.fail() || (profMode != 1 && profMode != 2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "�߸��� �Է��Դϴ�. 1 �Ǵ� 2�� �Է��ϼ���." << endl;
            }
            else {
                break;
            }
        }

        int category, studentNumber, score;

        if (profMode == 1) {
            while (true) {
                cout << "������ �� �׸��� �Է��ϼ���." << endl
                    << "1. attendance, 2. midtermTest, 3. finalTest, 4. assignment" << endl;
                cout << ">> �Է�: ";
                cin >> category;

                if (cin.fail() || category < 1 || category > 4) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "�߸��� �Է��Դϴ�. 1~4 ������ ���ڸ� �Է��ϼ���." << endl;
                }
                else {
                    break;
                }
            }

            rwcsv().UpdateAllStudentsGrade(subjectName, category);
        }
        else if (profMode == 2) {
            while (true) {
                cout << "�л� �й��� �Է��ϼ���." << endl;
                cout << ">> �Է�: ";
                cin >> studentNumber;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���." << endl;
                }
                else {
                    break;
                }
            }

            while (true) {
                cout << "������ �� �׸��� �Է��ϼ���." << endl
                    << "1. attendance, 2. midtermTest, 3. finalTest, 4. assignment" << endl;
                cout << ">> �Է�: ";
                cin >> category;

                if (cin.fail() || category < 1 || category > 4) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "�߸��� �Է��Դϴ�. 1~4 ������ ���ڸ� �Է��ϼ���." << endl;
                }
                else {
                    break;
                }
            }

            while (true) {
                cout << "������ �Է��ϼ���." << endl;
                cout << ">> �Է�: ";
                cin >> score;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���." << endl;
                }
                else if (category == 1 && score > 10) {
                    cout << "�⼮ ������ 10���� �ʰ� �� �� �����ϴ�." << endl;
                }
                else if (category != 1 && score > 30) {
                    cout << "���� �� ���� ������ 30���� �ʰ� �� �� �����ϴ�." << endl;
                }
                else {
                    break;
                }
            }

            rwcsv().UpdateStudentGrade(subjectName, studentNumber, category, score);
        }
    }
}
