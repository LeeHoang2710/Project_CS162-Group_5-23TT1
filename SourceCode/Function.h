#pragma once
#include "C:\Users\LEGION\Desktop\branches\Project_CS162\struct and function\struct_and_library.h"
void InputCourse(Course& cs, ifstream& ip);
void OutputCourse(Course cs);
void AddStudent2Course(CourseNode*& csnode, Course cs, ifstream& ip);
void display(CourseNode* CourseHead);
//Login Session
void StorePassWord(StudentNode*& StuPass, ifstream& ip);
void Login(StudentNode* StuList, string& onstatus_ID);
void ChangePass(Student& current);
