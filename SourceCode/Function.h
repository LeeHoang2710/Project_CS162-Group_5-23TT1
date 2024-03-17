#pragma once
#include "C:\Users\LEGION\Desktop\branches\Project_CS162\struct and function\struct_and_library.h"
void InputCourse(Course& cs, ifstream& ip);
void OutputCourse(Course cs);
void AddStudent2Course(CourseNode*& csnode, Course cs, ifstream& ip);
void display(CourseNode* CourseHead);
//Login Session
void StorePassWord_Student(StudentNode*& StuPass, ifstream& ip);
void StorePassWord_Staff(StaffNode*& StaffPass, ifstream& ip);
void LoginForStudent(StudentNode* StuList, string& onstatus_ID, StudentNode*& ChangeStuPass);
void LoginForStaff(StaffNode* StaffPass, string& onstatus_UserName, StaffNode*& ChangeStaffPass);
void ChangePassStudent(StudentNode* current);
void ChangePassStaff(StaffNode* current);
