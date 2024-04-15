#pragma once
#include "struct_and_library.h"
#include "year.h"
#include "function_class.h"
#include "function_course.h"
#include "semester.h"

// ReadClassfromfile
// ExportCassTFile
// searchClassNode

bool importYear(YearNode*& year_list, ClassNode* allClass, string filename, ifstream& fin);
bool exportYear(YearNode*& year_list, string filename, ofstream& fout);

ClassSubNode* createClassSubNode(ClassNode* classNode);
void appendClassSubNode(ClassSubNode*& classSublist, ClassSubNode* classSubNode);
ClassNode* searchClassNode(ClassNode* allClass, string class_id);
bool importClassSubNode(ClassNode* allClass, Year& year, stringstream& ss);
void exportClassSubNode(ClassSubNode* classSublist, ofstream& fout);

void importSemester(ClassNode* allClass, SemesterNode*& sem_list, stringstream& is, ifstream& fin)
{
	string start_date, end_date, sem_id;
	getline(is, sem_id, ',');
	getline(is, start_date, ',');
	getline(is, end_date, '\n');

	// Create a new Semester
	Semester new_sem = createSemester(sem_id, start_date, end_date);
	importCourse(allClass, new_sem.course_list, fin);
	// Append the new Semester to the sem_list
	appendSemesterNode(sem_list, createSemesterNode(new_sem));
}
