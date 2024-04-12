#pragma once
#include "struct_and_library.h"
#include "../function_student.h"

Class CreateClass(string classid);
ClassNode* InitClassNode(Class newclass);
void AddClassNode(ClassNode*& head, Class newclass);
// void DeleteClassNode(ClassNode *&head, Class del_class);
// ClassNode *SearchClassNode(ClassNode *&head, string searchclassid1, string searchclassid2);
// void AddStudent(ClassNode *&head, string classid, string academicid, StudentNode *newstudent);
void ReadClassfromfile(ClassNode*& Listclass, string file_name, ifstream& fin);
void ExportClassTFile(ClassNode*& Listclass, string file_name, ofstream& fout);
ClassNode* findClass(ClassNode* head, string input);
void importClass(ClassNode*& classes, stringstream& ss, ifstream& fin);
void exportClass(ClassNode* class_list, ofstream& fout);
