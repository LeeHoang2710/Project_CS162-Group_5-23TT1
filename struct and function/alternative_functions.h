#pragma once
#include "struct_and_library.h"
#include "../semester.h"
#include "../function_course.h"

void importYear(YearNode*& year_list, const string& filename, ifstream& fin);
void importSemester(SemesterNode* sem_list, ifstream& fin, const string& year_id);

void exportYear(YearNode* year_list, string filename, ofstream& fout);
void exportSemester(SemesterNode* sem_list, ofstream& fout);

void importCourseInSem(CourseNode*& Courselist, ifstream& fin, const string& semester_id, const string& year_id);
void appendCourseNode(CourseNode*& head, Course cs, const string& semester_id, const string& year_id);
