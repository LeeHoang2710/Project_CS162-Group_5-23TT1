#pragma once
#include "struct_and_library.h"

string formatDOTW(int d);
string formatSessionNo(int s);
void exportCourseForDisplay(CourseNode* course_list, const string& filename, ofstream& fout);
