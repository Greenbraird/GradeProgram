#ifndef FIND_COURSE_FILE_H
#define FIND_COURSE_FILE_H

#include <string>

// 과목 이름을 받아 .csv 파일 존재 여부를 확인하고, 파일명을 반환
std::string FindCourseFile(const std::string& courseName);

#endif // FIND_COURSE_FILE_H
