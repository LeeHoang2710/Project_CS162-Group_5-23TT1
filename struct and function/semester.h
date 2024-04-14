#pragma once
#include "struct_and_library.h"
#include "year.h"
#include "function_course.h"

void importSemesterInYear(SemesterNode* sem_list, ifstream& fin);
void importYearSemester(YearNode*& year_list, string filename, ifstream& fin);
void exportSemesterInYear(SemesterNode* sem_list, ofstream& fout);
void exportYearSemester(YearNode* year_list, string filename, ofstream& fout);

void inputSemesterInfo(string& sem_id, string& start_date, string& end_date);
Semester createSemester(const string& sem_id, const string& start_date, const string& end_date);
SemesterNode* createSemesterNode(const Semester& new_sem);
void addCourseListToSemester(SemesterNode*& semNode, CourseNode* course_list);
void appendSemesterNode(SemesterNode*& sem_list, SemesterNode* new_sem_node);
void createAndAddSemesterNode(YearNode*& currYear, const string& sem_id, const string& start_date, const string& end_date);
void createThreeSemesterNode(SemesterNode*& sem_list);

void inputSemesterDates(string& start_date, string& end_date);
void updateSemesterInfo(SemesterNode* semNode, const string& new_start_date, const string& new_end_date);
SemesterNode* searchSemesterNode(YearNode* yearNode, int sem_num);
bool removeSemesterNode(YearNode* yearNode, int sem_num);

void deleteYearList(YearNode*& year_list);
void deleteSemesterList(SemesterNode*& sem_list);
void deleteResultsList(ResultsNode* results_list);
void deleteStudentList(StudentNode*& student_list);
