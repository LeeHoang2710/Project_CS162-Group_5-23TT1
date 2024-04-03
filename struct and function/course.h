#pragma once
#include "../struct and function/struct_and_library.h"
CourseNode* initCourseNode(string new_year_id, string new_semester_id, Course new_course);
void addNewCourseNode(CourseNode*& head, string year_id, string semester_id, Course cs);
void InputCourse(CourseNode*& head); // still missing course
void OutputCourse(Course cs); 
void displayCourse(CourseNode* CourseHead);
CourseNode* findcourse(CourseNode* CourseHead, string course_find); // it has to update the list everytime the program no need to 
void updatecourse(CourseNode* CourseHead, string updateCourse, Course newone); // use findcourse above
void deletecourse(CourseNode* CourseHead, string delCourse); // usefindcourse above
void importCourse(CourseNode*& Courselist, string year, string semester, string filename, ifstream& fin);
void exportCourse(CourseNode* Courselist, string filename, ofstream& fout);
