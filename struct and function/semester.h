#pragma once
#include "struct_and_library.h"

void inputSemester(string sem_id, string start_date, string end_date, CourseNode* course_list);

Semester createSemester(string sem_id, string start_date, string end_date, CourseNode* course_list);
SemesterNode* initSemesterNode(Semester new_sem);
void addSemesterNode(SemesterNode*& sem_list, Semester new_sem);
void removeSemesterNode(SemesterNode*& sem_list, int sem_num);
SemesterNode* searchSemesterNode(SemesterNode* sem_list, string year_id, int sem_num);

void importFileSemester();
void exportFileSemester();