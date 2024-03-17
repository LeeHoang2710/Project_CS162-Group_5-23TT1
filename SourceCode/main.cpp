#pragma once
#include "Function.h"

int main() {
	/*Course NewCs;
	CourseNode* cshead=NULL;
	ifstream ip;
	InputCourse(NewCs, ip);
	AddStudent2Course(cshead, NewCs, ip);
	display(cshead);*/
	bool role;
	cout << "enter 0 if staff, 1 if student: ";
	cin >> role;
	if (role) {
		ifstream StuPassList;
		StuPassList.open("../database/Students_Password.csv");
		StudentNode* StuPass = NULL;
		StorePassWord_Student(StuPass, StuPassList);
		string ID_Locate;
		StudentNode* ChangeStuPass;
		LoginForStudent(StuPass, ID_Locate, ChangeStuPass);
		StuPassList.close();
		bool change;
		cin >> change;
		if (change) {
			ChangePassStudent(ChangeStuPass);
			cout << ChangeStuPass->student.password << endl;
		}
	}
	else {
		ifstream StaffPassList;
		StaffPassList.open("../database/Staff_Password.csv");
		StaffNode* StaffPass = NULL;
		StorePassWord_Staff(StaffPass, StaffPassList);
		string Username_Locate;
		StaffNode* ChangeStaffPass;
		LoginForStaff(StaffPass, Username_Locate, ChangeStaffPass);
		bool change;
		cin >> change;
		if (change) {
			ChangePassStaff(ChangeStaffPass);
			cout << ChangeStaffPass->staff.password << endl;
		}
		StaffPassList.close();
	}
}