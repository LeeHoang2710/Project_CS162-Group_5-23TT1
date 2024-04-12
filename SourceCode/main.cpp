#pragma once
#include "../struct and function/course.h"
#include "../struct and function/student.h"
#include "../struct and function/login.h"
int main() {

	bool role;
	cout << "enter 0 if staff, 1 if student: ";
	cin >> role;
	if (role) {
		ifstream ip;
		ofstream op;
		StudentNode* StuPass = NULL;
		StorePassWordStudent(StuPass);
		string id, pass;
		do {
			cout << "ID: "; cin >> id;
			cout << "Pass: "; cin >> pass;
		} while (!LoginForStudent(StuPass, id, pass));
		if (LoginForStudent(StuPass, id, pass)) cout << "Succesful" << endl;
		bool change;
		cout << "If you want to change password, enter 1: ";
		cin >> change;
		if (change) {
			StudentNode* curr = searchStudentNode(StuPass, id);
			string passedit, newpass;
			cout << "Reenter pass: ";
			cin >> passedit;
			cout << "New pass: ";
			cin >> newpass;
			while (!ChangePassStudent(curr, passedit, newpass)) {
				cout << "Reenter pass: ";
				cin >> passedit;
			};
			if (ChangePassStudent(curr, passedit, newpass)) {
				cout << "Changed successfully" << endl;
			}
			UpdateStuPassFile(StuPass, op);
		}
		cout << "view profile: ";
		profilestudent(ip, id);
	}
	else {
		ifstream ip;
		ofstream op;
		StaffNode* StaffPass = NULL;
		StorePassWordStaff(StaffPass);
		string id, pass;
		do {
			cout << "ID: "; cin >> id;
			cout << "Pass: "; cin >> pass;
		} while (!LoginForStaff(StaffPass, id, pass));
		if(LoginForStaff(StaffPass, id, pass)) cout << "successful" << endl;
		bool change;
		cout << "If you want to change password, enter 1: ";
		cin >> change;
		if (change) {
			StaffNode* curr = searchStaffNode(StaffPass, id);
			string passedit, newpass;
			cout << "Reenter pass: ";
			cin >> passedit;
			cout << "New pass: ";
			cin >> newpass;
			while (!ChangePassStaff(curr, passedit, newpass)) {
				cout << "Reenter pass: ";
				cin >> passedit;
			};
			if (ChangePassStaff(curr, passedit, newpass)) {
				cout << "Changed successfully" << endl;
			}
			UpdateStaffPassFile(StaffPass, op);
		}
		cout << "view profile: ";
		profilestaff(ip, id);
	}
}

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

