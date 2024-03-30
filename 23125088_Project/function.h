#pragma once
#include "function.h"
#include "struct_and_library.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <time.h>
//Class
Class CreateClass(string classid, string headteacher, StudentNode* studenthead);
ClassNode* InitializeClassNode(Class newclass);
void AddClassNode(ClassNode*& head, Class newclass);
void DeleteClassNode(ClassNode*& head, Class del_class);
ClassNode* SearchClassNode(ClassNode*& head, Class searchclass);
void AddStudent(ClassNode*& head, string classid, StudentNode* newstudent);
void ReadClassfromfile(ClassNode* Listclass[], ifstream& fin);
void ReadStudentfromfile(StudentNode*& ListStu, ifstream& fin);
//Student
Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_class);
StudentNode* initStudentNode(Student new_student);
void addNewStudentNode(StudentNode*& head, Student new_student);
void removeStudentNode(StudentNode*& head, Student student_1);
void displayStudent(StudentNode* StuHead);
StudentNode* searchStudentNode(StudentNode* head, string student_1_id);
void readStudentFromFile(ifstream& file, StudentNode*& list_student);
bool readStudentFromTerminal(StudentNode*& liststu);
void exportStudentToFile(ofstream& file, StudentNode*& list_student);

//course
CourseNode* initCourseNode(Course new_course, StudentNode* liststu);
void addNewCourseNode(CourseNode*& head, Course cs, StudentNode* liststu);
void InputCourse(CourseNode*& head); // still missing course
void OutputCourse(Course cs);
void displayCourse(CourseNode* CourseHead);
CourseNode* findcourse(CourseNode* CourseHead, string course_find); // it has to update the list everytime the program no need to 
void updatecourse(CourseNode* CourseHead, string updateCourse); // use findcourse above
void deletecourse(CourseNode* CourseHead, string delCourse); // usefindcourse above
void StorePassWordStudent(StudentNode*& StuPass, ifstream& ip); //These 2 fucntions will load password file to a linked list
//login
void StorePassWordStudent(StudentNode*& StuPass, ifstream& ip); //These 2 fucntions will load password file to a linked list
void StorePassWordStaff(StaffNode*& StaffPass, ifstream& ip);
bool LoginForStudent(StudentNode* StuList, string& onstatus_ID, StudentNode*& ChangeStuPass); // 1st parameter is the linked list, 2nd parameter is the ID of student who is onl
bool LoginForStaff(StaffNode* StaffPass, string& onstatus_UserName, StaffNode*& ChangeStaffPass); // 3rd parameter is the node store the current id, used it only for changing password
void UpdateStuPassFile(StudentNode* List, ofstream& op); //Update the password file when someone change password;
void UpdateStaffPassFile(StaffNode* List, ofstream& op);
void ChangePassStudent(StudentNode* current); //get the node of user who is online and change password in it;
void ChangePassStaff(StaffNode* current);
//Semester
YearNode* importYearSemester(const string& filename, ifstream& fin);
void exportYearSemester(YearNode* year_list, const string& filename, ofstream& fout);

void inputSemester(string& sem_id, string& start_date, string& end_date);

Semester createSemester(const string& sem_id, const string& start_date, const string& end_date);
SemesterNode* createSemesterNode(const Semester& new_sem);
void addCourseListToSemester(SemesterNode* semNode, CourseNode* course_list);
void addSemesterNode(SemesterNode*& sem_list, SemesterNode* new_sem_node);
void removeSemesterNode(YearNode* year_list, const string& year_id, int sem_num);
SemesterNode* searchSemesterNode(YearNode* year_list, const string& year_id, int sem_num);
void updateSemester(SemesterNode* sem, const string& new_sem_id, const string& new_start_date, const string& new_end_date);

void deleteYearList(YearNode*& year_list);
void deleteSemesterList(SemesterNode*& sem_list);
//Session
string itosDOTW(int d);
string itosSessionNo(int s);

int stoiDOTW(string d);
int stoiSessionNo(string s);

void exportCourseForDisplay(CourseNode* course_list, const string& filename, ofstream& fout);
//Year
Year createYear(string p_year_id);
YearNode* initYearNode(Year school_year);
void addNewYearNode(YearNode*& head, YearNode* year);
void removeNewYearNode(YearNode*& head, Year year);
YearNode* searchYearNode(YearNode* head, string year_id);
// View
void Viewallmyscore(Student stu);
void Findoverall(StudentNode* stu);
void Viewgpaallstudent(StudentNode* stuhead);//adding mycourse
