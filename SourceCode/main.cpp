#pragma once
#include "Function.h"

int main() {
	Course NewCs;
	CourseNode* cshead=NULL;
	ifstream ip;
	InputCourse(NewCs, ip);
	AddStudent2Course(cshead, NewCs, ip);
	display(cshead);
}