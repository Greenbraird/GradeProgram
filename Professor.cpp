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
        cout << getName() + "�� " + "ȯ���մϴ�." << endl;

        rwcsv().PrintSubjectList(*this);
        cout << "������ ���ǽ��� �����ϼ���." << endl;
        cout << ">> �Է�(ex. ��ǻ�����α׷���): ";

        string subjectName;
        cin >> subjectName;

        cout << "1. ���׸� ���� " << "2. ���� �Է� " << endl;
        cin >> profMode;
        if (profMode == 1) {
            
        }
        else if (profMode == 2) {
            // ���� �Է� �Լ� ����
        }
    }
}