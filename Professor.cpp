#include "Professor.h"
#include "rwcsv.h"

void Professor::main() const
{
    string whichSubject;
    int profMode;

    while (true) {
        system("cls");
        string filename = "professor.csv";

        cout << "=======================�� ���ǽ�=======================\n";
        // 3.1. ���� ���� : ���� ����Ʈ ���/����� �Է�
        // �������� �Ҵ�� ������ subject.csv���� �ҷ�����. �̸� ���� subject.csv���� name, subject �������� ����Ǿ��ִ� ����
        string profName = this->getName(); //�α��� �������� ���� �̸� ������ ���� �����ؾ� ��
        cout << getName() + "������ " + "ȯ���մϴ�." << endl;

        rwcsv().PrintSubjectList(*this);
        cout << "������ ���ǽ��� �����ϼ���." << endl;
        cout << ">> �Է�(ex. ��ǻ�����α׷���): ";

        string subjectName;
        cin >> subjectName;

        rwcsv().PrintStudentsList(subjectName);

        cout << "1. ��ü ���� �Է� " << "2. �л��� ���� �Է� " << endl;
        cout << ">> �Է�: ";
        cin >> profMode;
        
        int category, studentNumber, score;

        if (profMode == 1) {
            cout << "������ �� �׸��� �Է��ϼ���." << endl <<
                "1. attendance, 2.midtermTest, 3.finalTest, 4. assignment : " << endl;
            cout << ">> �Է�: ";
            cin >> category;
            rwcsv().UpdateAllStudentsGrade(subjectName, category);
        }
        else if (profMode == 2) {
         
            cout << "�л� �й��� �Է��ϼ���: " << endl;
            cout << ">> �Է�: ";
            cin >> studentNumber;

            cout << "������ �� �׸��� �Է��ϼ���." << endl <<
                "1. attendance, 2.midtermTest, 3.finalTest, 4. assignment : " << endl;
            cout << ">> �Է�: ";
            cin >> category;
            while (true) {
                cout << "������ �Է��ϼ���: " << endl;
                cout << ">> �Է�: ";
                cin >> score;
                if (category == 0 && score > 11) {
                    cout << "�⼮ ������ 10���� �ʰ� �� �� �����ϴ�." << endl;
                }
                else if (category != 0 && score > 31) {
                    cout << "�⼮ ������ 30���� �ʰ� �� �� �����ϴ�." << endl;
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