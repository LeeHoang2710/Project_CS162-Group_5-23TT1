#pragma once
#include "struct_and_library.h"
#include "../function_class.h"
#include "../function_student.h"
#include "../function_course.h"

void importClassResults(ClassNode* class_list, const string& filename, ifstream& fin);
void importStudentResults(ClassNode* currClass, ifstream& fin);
void importCourseResults(StudentNode* currStudent, ifstream& fin);

void exportResults(ClassNode* class_list, const string& filename, ofstream& fout);

void inputScore(float& process, float& midterm, float& final);
void updateCourseOverall(Score& score);
void updateCurrentSemGpa(StudentNode* studentNode);
void updateTotalGpa(StudentNode* studentNode);

Results createResults(const string& course_id, const string& sem_id, const string& year_id);
ResultsNode* createResultsNode(const Results& results);
void appendResultsNode(ResultsNode*& results_list, ResultsNode* resultsNode);
void updateScore(Score& score, const float& process, const float& midterm, const float& final);
void addResultsNodeToClass(ClassNode* classNode, const string& year_id, const string& sem_id, const string& course_id);

ResultsNode* searchResultsNode(ResultsNode* results_list, string course_id);
string getCurrSemId(ResultsNode* results_list);
string getCurrYearId(ResultsNode* results_list);
ResultsNode* getCurrSemResultsNode(ResultsNode* results_list, const string& currSemId);
ResultsNode* getCurrYearResultsNode(ResultsNode* results_list, const string& currYearId);

bool removeResultsNode(ResultsNode*& results_list, string course_id);
void deleteResultsList(ResultsNode* results_list, string courseid);
