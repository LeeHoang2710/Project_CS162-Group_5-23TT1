#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Year;
struct YearNode;
struct Semester;
struct SemesterNode;

struct Session;
struct Course;
struct CourseNode;

struct Class;
struct ClassNode;
struct ClassSubNode;

struct Score;
struct Student;
struct StudentNode;
struct StudentSubNode;

struct Results;
struct ResultsNode;

struct Year
{
	string year_id;
	ClassSubNode *classSublist = nullptr;
	SemesterNode *list_sem = nullptr;
};

struct YearNode
{
	Year school_year;
	YearNode *next = nullptr;
};

struct Semester
{
	string start_date;
	string end_date;
	string semester_id;
	CourseNode *course_list = nullptr;
};

struct SemesterNode
{
	Semester sem;
	SemesterNode *next = nullptr;
};

struct Session
{
	int day_of_the_week; // MON / TUE / WED / THU / FRI / SAT
	int session_no;		 // S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)
};

struct Course
{
	string course_id;
	string course_name;
	string teacher_name;
	int num_credit;
	int max_students = 50;
	Session teaching_session;
	ClassNode *main_class = nullptr;
	StudentSubNode *extra_stu = nullptr;
};

struct CourseNode
{
	Course course;
	CourseNode *next = nullptr;
};

struct Class
{
	string class_id;
	StudentNode *student_list = nullptr;
};

struct ClassNode
{
	Class my_class;
	ClassNode *next = nullptr;
};

struct ClassSubNode // for Year, classNode Containter
{
	ClassNode *class_node = nullptr;
	ClassSubNode *next = nullptr;
};

struct Score
{
	float process = 0.0f;
	float midterm = 0.0f;
	float final = 0.0f;
	float overall = 0.0f;
};

struct Student
{
	int num = 0;
	string student_id;
	string first_name;
	string last_name;
	bool gender; // male(0), female(1)
	string dob;
	string social_id;
	string class_id;
	string password = "123456";
	ResultsNode *results_list = nullptr;
	float cur_gpa = 0.0f;
	float total_gpa = 0.0f;
};

struct StudentNode
{
	Student student;
	StudentNode *next = nullptr;
};

struct StudentSubNode
{
	StudentNode *student_node = nullptr;
	StudentSubNode *next = nullptr;
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
	ResultsNode *next = nullptr;
};

struct Staff
{
	string username;
	string first_name;
	string last_name;
	bool gender;
	string dob;
	string social_id;
	string password = "123";
};
struct StaffNode
{
	Staff staff;
	StaffNode *next = nullptr;
};
