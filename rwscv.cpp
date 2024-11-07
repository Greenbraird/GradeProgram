#include "rwscv.h"
#include "student.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<student> readCSV(const string& filename) {
    ifstream csvFile(filename);
    vector<student> records;
    string line;

    if (csvFile.is_open()) {
        // Read each line and parse by comma
        while (getline(csvFile, line)) {
            stringstream ss(line); //���ٷ� �Ǿ��ִ� �� string
            student st(0,0,0,0,0,0);
            //getline(ss, st.name, ',');


            records.push_back(st);
        }
        csvFile.close();
    }
    else {
        cout << "������ �� �� �����ϴ�." << endl;
    }
    return records;
}