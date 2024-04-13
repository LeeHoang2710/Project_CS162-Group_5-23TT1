#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

struct Score;
struct Results;
struct ResultsNode;

struct Student;//c
struct StudentNode;

struct Class;//p
struct ClassNode;

struct Session;
struct Course;
struct CourseNode;

struct Semester;//n
struct SemesterNode;

struct Year;//h
struct YearNode;

struct Score
{
	float process = 0.0f;
	float midterm = 0.0f;
	float final = 0.0f;
	float overall = 0.0f;
};

struct Results
{
	Score score;
	string course_id;
	string sem_id;
	string year_id;
};

struct ResultsNode
{
	Results results;
	ResultsNode* next = nullptr;
};

struct Student
{
	int num;
	string student_id;
	string first_name;
	string last_name;
	bool gender; // male(0), female(1)
	string dob;
	string social_id;
	string password = "123456";
	string student_class;
	ResultsNode* results_list = nullptr;
	float cur_gpa = 0.0f;
	float total_gpa = 0.0f;
};

struct StudentNode
{
	Student student;
	StudentNode* next = nullptr;
};

struct Class
{
	string class_id;
	string head_teacher;
	StudentNode* student_list = nullptr;
};

struct ClassNode
{
	Class my_class;
	ClassNode* next = nullptr;
};

struct Session
{
	int day_of_the_week; // MON / TUE / WED / THU / FRI / SAT
	int session_no;      // S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)
};

struct Course
{
	string course_id;
	string course_name;
	string teacher_name;
	int num_credit;
	int max_students = 50;
	Session teaching_session;
};

struct CourseNode
{
	string semester_id;
	string year_id;
	Course course;
	ClassNode* main_class;
	StudentNode* student_list = nullptr;
	CourseNode* next = nullptr;
};

struct Semester
{
	string semester_id;
	string start_date;
	string end_date;
	CourseNode* course_list = nullptr;
};

struct SemesterNode
{
	Semester sem;
	SemesterNode* next = nullptr;
};

struct Year
{
	string year_id;
	SemesterNode* list_sem = nullptr;
};

struct YearNode
{
	Year school_year;
	YearNode* next = nullptr;
};



{
	Staff staff;
	StaffNode *next;
};
