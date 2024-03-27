#include "../struct and function/struct_and_library.h"
#include "../struct and function/login.h"
void StorePassWordStudent(StudentNode*& StuPass) {
	ifstream ip;
	ip.open("../database/Students_Password.csv");
	StudentNode* cur = StuPass;
	Student tmp;
	getline(ip, tmp.student_id, ',');
	getline(ip, tmp.password, '\n');
	while (1) {
		if (StuPass == NULL) {
			StuPass = new StudentNode;
			cur = StuPass;
		}
		else {
			cur->next = new StudentNode;
			cur = cur->next;
		}
		cur->student = tmp;
		cur->next = NULL;
		if (ip.eof()) {
			ip.close();
			return;
		}
		getline(ip, tmp.student_id, ',');
		getline(ip, tmp.password, '\n');
	}
}
void StorePassWordStaff(StaffNode*& StaffPass) {
	ifstream ip;
	ip.open("../database/Staff_Password.csv");
	StaffNode* cur = StaffPass;
	Staff tmp;
	getline(ip, tmp.username, ',');
	getline(ip, tmp.password, '\n');
	while (1) {
		if (StaffPass == NULL) {
			StaffPass = new StaffNode;
			cur = StaffPass;
		}
		else {
			cur->next = new StaffNode;
			cur = cur->next;
		}
		cur->staff = tmp;
		cur->next = NULL;
		if (ip.eof()) {
			ip.close();
			return;
		}
		getline(ip, tmp.username, ',');
		getline(ip, tmp.password, '\n');
	}
}
bool LoginForStudent(StudentNode* StuPass, string& onstatus_ID, StudentNode*& ChangeStuPass, string input_ID, string input_Pass) {
		StudentNode* tmp = StuPass;
		for (tmp; tmp != NULL; tmp = tmp->next) {
			if (tmp->student.student_id == input_ID) {
				if (tmp->student.password == input_Pass) {
					onstatus_ID = input_ID;
					ChangeStuPass = tmp;
					return true;
				}
				else {
					return false;
					break;
				}
			}
		}
		if (tmp == NULL) return false;
}
bool LoginForStaff(StaffNode* StaffPass, string& onstatus_UserName, StaffNode*& ChangeStaffPass, string input_UserName, string input_Pass) {
		StaffNode* tmp = StaffPass;
		for (tmp; tmp != NULL; tmp = tmp->next) {
			if (tmp->staff.username == input_UserName) {
				if (tmp->staff.password == input_Pass) {
					onstatus_UserName = input_UserName;
					ChangeStaffPass = tmp;
					return true;
				}
				else {
					return false;
					break;
				}
			}
		}
		if (tmp == NULL) return false;
}
void UpdateStuPassFile(StudentNode* List, ofstream& op) {
	op.open("../database/Students_Password.csv");
	for (StudentNode* tmp = List; tmp != NULL; tmp = tmp->next) {
		op << tmp->student.student_id << ",";
		op << tmp->student.password;
		if (tmp->next != NULL) op << endl;
	}
	op.close();
}
void UpdateStaffPassFile(StaffNode* List, ofstream& op) {
	op.open("../database/Staff_Password.csv");
	for (StaffNode* tmp = List; tmp != NULL; tmp = tmp->next) {
		op << tmp->staff.username << ",";
		op << tmp->staff.password;
		if (tmp->next != NULL) op << endl;
	}
	op.close();
}
bool ChangePassStudent(StudentNode* current, string input_Pass) {
	if (current->student.password == input_Pass) {
		cin >> input_Pass;
		current->student.password = input_Pass;
		return true;
	}
	else {
		return false;
	}
}
bool ChangePassStaff(StaffNode* current, string input_Pass) {
	if (current->staff.password == input_Pass) {
		cin >> input_Pass;
		current->staff.password = input_Pass;
		return true;
	}
	else {
		return false;
	}
}
//new session