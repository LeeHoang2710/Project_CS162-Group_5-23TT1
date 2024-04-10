#include "../struct and function/struct_and_library.h"

Class CreateClass(string classid, StudentNode* studenthead);
ClassNode* InitializeClassNode(Class newclass);
void AddClassNode(ClassNode*& head, Class newclass);
void DeleteClassNode(ClassNode*& head, Class del_class);
ClassNode* SearchClassNode(ClassNode*& head, Class searchclass);
void AddStudent(ClassNode*& head, string classid, string academicid, StudentNode* newstudent);