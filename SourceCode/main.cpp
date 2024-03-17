#pragma once
#include "Function.h"

int main() {
	/*Course NewCs;
	CourseNode* cshead=NULL;
	ifstream ip;
	InputCourse(NewCs, ip);
	AddStudent2Course(cshead, NewCs, ip);
	display(cshead);*/
	ifstream StuPassList;
	StuPassList.open("../database/Students_Password.csv");
	StudentNode* StuPass=NULL;
	StorePassWord(StuPass, StuPassList);
	string ID_Locate;
	Login(StuPass, ID_Locate);
	StuPassList.close();
}