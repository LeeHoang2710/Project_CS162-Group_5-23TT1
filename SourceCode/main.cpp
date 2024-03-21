#pragma once
#include "../struct and function/course.h"
#include "../struct and function/student.h"
#include "../struct and function/login.h"
int main() {
	//CourseNode* cshead=NULL;
	//InputCourse(cshead);
	////AddStudent2Course(cshead, NewCs, ip);
	//InputCourse(cshead);
	//displayCourse(cshead);
	bool role;
	cout << "enter 0 if staff, 1 if student: ";
	cin >> role;
	if (role) {
		ifstream StuPassList;
		ofstream op;
		StuPassList.open("../database/Students_Password.csv");
		StudentNode* StuPass = NULL;
		StorePassWordStudent(StuPass, StuPassList);
		string ID_Locate;
		StudentNode* ChangeStuPass;
		LoginForStudent(StuPass, ID_Locate, ChangeStuPass);
		bool change;
		cout << "If you want to change password, enter 1: ";
		cin >> change;
		if (change) {
			ChangePassStudent(ChangeStuPass);
			cout << ChangeStuPass->student.password << endl;
			UpdateStuPassFile(StuPass, op);
		}
		StuPassList.close();
	}
	else {
		ifstream StaffPassList;
		ofstream op;
		StaffPassList.open("../database/Staff_Password.csv");
		StaffNode* StaffPass = NULL;
		StorePassWordStaff(StaffPass, StaffPassList);
		string Username_Locate;
		StaffNode* ChangeStaffPass;
		LoginForStaff(StaffPass, Username_Locate, ChangeStaffPass);
		bool change;
		cout << "If you want to change password, enter 1: ";
		cin >> change;
		if (change) {
			ChangePassStaff(ChangeStaffPass);
			cout << ChangeStaffPass->staff.password << endl;
			UpdateStaffPassFile(StaffPass, op);
		}
		StaffPassList.close();
	}
}