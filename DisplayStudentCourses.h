#ifndef DISPLAY_STUDENT_COURSES_H
#define DISPLAY_STUDENT_COURSES_H

#include <vector>
#include <string>

using namespace std;

vector<string> GetStudentCourses(const std::string& filename, const std::string& studentName);
vector<string> DisplayStudentCourses(const std::string& filename, const std::string& studentName);

#endif
