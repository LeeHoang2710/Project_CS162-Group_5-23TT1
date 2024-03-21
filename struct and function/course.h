#pragma once
#include "../struct and function/struct_and_library.h"
CourseNode* initCourseNode(Course new_course, StudentNode* liststu);
void addNewCourseNode(CourseNode*& head, Course cs, StudentNode* liststu);
void InputCourse(CourseNode*& head); // still missing course
void OutputCourse(Course cs); 
void displayCourse(CourseNode* CourseHead);
CourseNode* findcourse(CourseNode* CourseHead, string course_find); // it has to update the list everytime the program no need to 
void updatecourse(CourseNode* CourseHead, string updateCourse); // use findcourse above
void deletecourse(CourseNode* CourseHead, string delCourse); // usefindcourse above
