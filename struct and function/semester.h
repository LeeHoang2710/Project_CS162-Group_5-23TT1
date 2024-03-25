#pragma once
#include "struct_and_library.h"
#include "year_LeeHoang.h" //LeeHoang's Year functions

void importYearSemester(YearNode*& year_list, string filename, ifstream& fin);
void exportYearSemester(YearNode* year_list, string filename, ofstream& fout);

void inputSemester(string& sem_id, string& start_date, string& end_date);
Semester createSemester(const string& sem_id, const string& start_date, const string& end_date);
SemesterNode* createSemesterNode(const Semester& new_sem);

void appendSemesterNode(SemesterNode*& sem_list, SemesterNode* new_sem_node);
void updateSemesterInfo(SemesterNode* semNode, const string& new_sem_id, const string& new_start_date, const string& new_end_date);
void removeSemesterNode(YearNode* year_list, const string& year_id, int sem_num);
SemesterNode* searchSemesterNode(YearNode* year_list, const string& year_id, int sem_num);

void deleteYearList(YearNode*& year_list);
void deleteSemesterList(SemesterNode*& sem_list);
