#pragma once
#include "struct_and_library.h"
#include "../results.h"

bool importClassFromStaff(ifstream& fin, const string& filename, ClassNode*& class_list);
bool importResultFromStaff(ifstream& fin, const string& filename, CourseNode* courseNode);
bool importResultInCourse(ifstream& fin, CourseNode* courseNode);
