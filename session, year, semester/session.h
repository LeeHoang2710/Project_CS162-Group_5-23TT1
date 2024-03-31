#pragma once
#include "../struct and function/struct_and_library.h"

string itosDOTW(int d);
string itosSessionNo(int s);

int stoiDOTW(string d);
int stoiSessionNo(string s);

void exportCourseForDisplay(CourseNode* course_list, const string& filename, ofstream& fout);
