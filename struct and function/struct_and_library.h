#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime>

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

struct Score;
struct Student;
struct StudentNode;
struct Result;
struct ResultsNode;

struct Year
{
    string year_id;
    SemesterNode* list_sem = nullptr;
};
struct YearNode
{
    Year school_year;
    YearNode* next;
};
struct Semester
{
    string start_date;
    string end_date;
    string semester_id;
    CourseNode* course_list = nullptr;
};
struct SemesterNode
{
    Semester sem;
    SemesterNode* next;
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
    ClassNode* main_class = nullptr;
    StudentNode* student_list = nullptr;
};
struct CourseNode
{
    string semester_id;
    string year_id;
    Course course;
    CourseNode* next;
};
struct Class
{
    string class_id;
    StudentNode* student_list = nullptr;
};
struct ClassNode
{
    Class my_class;
    ClassNode* next;
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
    int num;
    string student_id;
    string first_name;
    string last_name;
    bool gender; // male(0), female(1)
    string dob;
    string social_id;
    string password = "123456";
    string student_class;
    ResultNode* my_course = nullptr;
    float cur_gpa = 0.0f;
    float total_gpa = 0.0f;
};
struct StudentNode
{
    Student student;
    StudentNode* next;
};
struct Results
{
    Score score;
    CourseNode* course = nullptr;
    SemesterNode* sem = nullptr;
    YearNode* year = nullptr;
};

struct ResultNode
{
    Results results;
    ResultNode* next = nullptr;
};

struct Staff
{
    string username;
    string first_name;
    string last_name;
    bool gender;
    string dob;
    string social_id;
    string password;
};
struct StaffNode
{
    Staff staff;
    StaffNode* next;
};

// input year, init year node, yearlist head, 2023-2024
// input 1 semester, insert into semester node, semester list 
// input course, append courselist,
// input list of students,
// iterate student 
// duyet qua course.class.student
// tao resultnode,
// resultnode.result.yearnode= cur year node;
// semnode= cur semnode;
// coursenode=cur course
// append resultnode;

//view course of one student
// 
// display 


// staff :
// year -> semester -> listcourse -> course -> studentlist -> 
// 