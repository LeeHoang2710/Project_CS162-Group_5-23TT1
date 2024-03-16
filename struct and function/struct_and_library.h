#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

struct Year;
struct YearNode;
struct Class;
struct ClassNode;
struct Course;
struct CourseNode;
struct MyCourse;
struct Semester;
struct SemesterNode;
struct Student;
struct StudentNode;
struct Session;
struct Score;

//Comments for ease of understand
//School years
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

//Each year has 3 semesters
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

//I don't know what this is
struct RegistrationSession
{
	string year;
	string sem;
	CourseNode* list_of_courses = nullptr;
	string start_date;
	string end_date;
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
	Session teaching_session[2];
};
struct CourseNode
{
	string semester_id;
	string year_id;
	Course course;
	StudentNode* student_list = nullptr;
	CourseNode* next;
};
struct MyCourse
{
	Score score;
	string subject_code;
	string sem;
	string year;
	CourseNode* course = nullptr;
	MyCourse* next;
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
	ClassNode* next;
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
	string password = "default";
	string student_class;
	MyCourse* my_course = nullptr;
	float cur_gpa = 0.0f;
	float total_gpa = 0.0f;
};
struct StudentNode
{
	Student student;
	StudentNode* next;
};

struct Score
{
	float process = 0.0f;
	float midterm = 0.0f;
	float final = 0.0f;
	float overall = 0.0f;
};