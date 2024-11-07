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
            stringstream ss(line); //한줄로 되어있는 것 string
            student st(0,0,0,0,0,0);
            //getline(ss, st.name, ',');


            records.push_back(st);
        }
        csvFile.close();
    }
    else {
        cout << "파일을 열 수 없습니다." << endl;
    }
    return records;
}