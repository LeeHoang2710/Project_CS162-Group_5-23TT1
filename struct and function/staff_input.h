#pragma once
#include "struct_and_library.h"
#include "../results.h"

bool importClassFromStaff(ifstream& fin, const string& filename, ClassNode*& class_list);

bool importResultsFromStaff(ifstream& fin, const string& filename, CourseNode* courseNode);
bool importResultsInCourse(ifstream& fin, CourseNode* courseNode);

bool importCoursesFromStaff(ifstream& fin, const string& filename, YearNode* year_list, YearNode* yearNode, SemesterNode* semNode);
bool importCourses(ifstream& fin, YearNode* year_list, CourseNode*& course_list, const string& year_id, const string& sem_id);
ClassNode* searchClassNodeFromAllYears(YearNode* year_list, const string& class_id);