#pragma once
#include "../struct and function/course.h"
#include "../struct and function/student.h"
#include "../struct and function/login.h"
//int main() {
//	//CourseNode* cshead=NULL;
//	//InputCourse(cshead);
//	////AddStudent2Course(cshead, NewCs, ip);
//	//InputCourse(cshead);
//	//displayCourse(cshead);
//	bool role;
//	cout << "enter 0 if staff, 1 if student: ";
//	cin >> role;
//	if (role) {
//		ifstream StuPassList;
//		ofstream op;
//		StuPassList.open("../database/Students_Password.csv");
//		StudentNode* StuPass = NULL;
//		StorePassWordStudent(StuPass, StuPassList);
//		string ID_Locate;
//		StudentNode* ChangeStuPass;
//		if (LoginForStudent(StuPass, ID_Locate, ChangeStuPass)) cout << "successful" <<endl;
//		bool change;
//		cout << "If you want to change password, enter 1: ";
//		cin >> change;
//		if (change) {
//			ChangePassStudent(ChangeStuPass);
//			cout << ChangeStuPass->student.password << endl;
//			UpdateStuPassFile(StuPass, op);
//		}
//		StuPassList.close();
//	}
//	else {
//		ifstream StaffPassList;
//		ofstream op;
//		StaffPassList.open("../database/Staff_Password.csv");
//		StaffNode* StaffPass = NULL;
//		StorePassWordStaff(StaffPass, StaffPassList);
//		string Username_Locate;
//		StaffNode* ChangeStaffPass;
//		if(LoginForStaff(StaffPass, Username_Locate, ChangeStaffPass)) cout << "successful" << endl;
//		bool change;
//		cout << "If you want to change password, enter 1: ";
//		cin >> change;
//		if (change) {
//			ChangePassStaff(ChangeStaffPass);
//			cout << ChangeStaffPass->staff.password << endl;
//			UpdateStaffPassFile(StaffPass, op);
//		}
//		StaffPassList.close();
//	}
//}

//int main() {
//	CourseNode* cslist = NULL;
//	ifstream fin;
//	ofstream fout;
//	fin.open("../database/course.csv");
//	fout.open("../database/testcourse.csv", ios::app);
//	importCourse(cslist, "year ", "seme", ".. /database/course.csv", fin);
//	exportCourse(cslist, "../database/testcourse.csv", fout);
//	fin.close();
//	fout.close();
//}