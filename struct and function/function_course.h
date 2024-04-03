#pragma once
#include "struct_and_library.h"

Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, Session teaching_session);
CourseNode* initCourseNode(Course new_course);
// void addNewCourseNode(CourseNode *&head, Course cs, StudentNode *liststu);
void appendNewCourseNode(CourseNode*& head, Course cs);
void deletecourse(CourseNode* CourseHead, string delCourse);
void importCourse(CourseNode*& Courselist, ifstream& fin);
void exportCourse(CourseNode*& Courselist, ofstream& fout);
void comparecourse(Course& old, Course& newone);
void updatecourse(CourseNode*& curr, Course newone);
