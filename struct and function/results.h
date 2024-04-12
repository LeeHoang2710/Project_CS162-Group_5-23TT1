#pragma once
#include "struct_and_library.h"
#include "../function_class.h"
#include "../function_student.h"

void importClassResult(ClassNode* class_list, const string& filename, ifstream& fin);
void importStudentResult(ClassNode* currClass, ifstream& fin);
void importCourseResult(StudentNode* currStudent, ifstream& fin);

void exportResult(ClassNode* class_list, const string& filename, ofstream& fout);

void inputScore(float& process, float& midterm, float& final);
void updateCourseOverall(Score& score);
void updateCurrentSemGpa(StudentNode* studentNode);
void updateTotalGpa(StudentNode* studentNode);

Result createResult(const string& course_id, const string& sem_id, const string& year_id);
ResultNode* createResultNode(const Result& result);
void appendResultNode(ResultNode*& result_list, ResultNode* resultNode);
void updateScore(Score& score, const float& process, const float& midterm, const float& final);

ResultNode* searchResultNode(ResultNode* result_list, string course_id);
string getCurrSemId(ResultNode* result_list);
string getCurrYearId(ResultNode* result_list);
ResultNode* getCurrSemResultNode(ResultNode* result_list, const string& currSemId);
ResultNode* getCurrYearResultNode(ResultNode* result_list, const string& currYearId);

bool removeResultNode(ResultNode*& result_list, string course_id);
void deleteResultList(ResultNode* result_list, string courseid);
