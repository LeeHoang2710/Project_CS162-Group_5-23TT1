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
bool LoginForStudent(StudentNode* StuPass, string input_ID, string input_Pass) {
		StudentNode* tmp = StuPass;
		for (tmp; tmp != NULL; tmp = tmp->next) {
			if (tmp->student.student_id == input_ID) {
				if (tmp->student.password == input_Pass) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		if (tmp == NULL) return false;
}
bool LoginForStaff(StaffNode* StaffPass, string input_UserName, string input_Pass) {
		StaffNode* tmp = StaffPass;
		for (tmp; tmp != NULL; tmp = tmp->next) {
			if (tmp->staff.username == input_UserName) {
				if (tmp->staff.password == input_Pass) {
					return true;
				}
				else {
					return false;
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
bool ChangePassStudent(StudentNode* current, string input_Pass, string newpass) {
	if (current->student.password == input_Pass) {
		current->student.password = newpass;
		return true;
		//remember to inform user
	}
	else {
		return false;
	}
}
bool ChangePassStaff(StaffNode* current, string input_Pass, string newpass) {
	if (current->staff.password == input_Pass) {
		current->staff.password = newpass;
		// remember to inform user
		return true;
	}
	else {
		return false;
	}
}
//new session
StaffNode* searchStaffNode(StaffNode* head, string staff_1_id)
{
	if (!head)
	{
		cout << "Cannot find the searched staff..." << endl;
		return nullptr;
	}
	StaffNode* list_staff = head;
	while (list_staff)
	{
		if (list_staff->staff.username == staff_1_id)
			return list_staff;
		else
			list_staff= list_staff->next;
	}
	cout << "Cannot find the searched staff..." << endl;
	return nullptr;
}
void profilestaff(ifstream& ip, string staff_id) {
	ip.open("../database/staff_list.csv");
	if (!ip.is_open())
		cout << "Can not open file" << endl;
	else
	{
		string line;
		while (getline(ip, line))
		{
			stringstream ss(line);
			string number;
			Staff person;
			getline(ss, person.username, ',');
			getline(ss, person.first_name, ',');
			getline(ss, person.last_name, ',');
			getline(ss, number, ',');
			person.gender = stoi(number);
			getline(ss, person.dob, ',');
			getline(ss, person.social_id, '\n');
			if (person.username == staff_id)
			{
				cout << person.username << endl;
				cout << person.last_name << " ";
				cout << person.first_name << endl;
				if (person.gender == 1) {
					cout << "Female" << endl;
				}
				else cout << "Male" << endl;
				cout << person.dob << endl;
				cout << person.social_id << endl;
				break;
			}
			
		}
	}
	ip.close();
}

void profilestudent(ifstream& ip, string stu_id) {
	ip.open("../database/student.csv");
	if (!ip.is_open())
		cout << "Can not open file" << endl;
	else
	{
		string line;
		while (getline(ip, line))
		{
			stringstream ss(line);
			string number;
			Student person;
			getline(ss, person.student_id, ',');
			getline(ss, person.first_name, ',');
			getline(ss, person.last_name, ',');
			getline(ss, number, ',');
			person.gender = stoi(number);
			getline(ss, person.dob, ',');
			getline(ss, person.social_id, ',');
			getline(ss, person.student_class, '\n');
			if (person.student_id == stu_id)
			{
				cout << person.student_id << endl;
				cout << person.last_name << " ";
				cout << person.first_name << endl;
				if (person.gender == 1) {
					cout << "Female" << endl;
				}
				else cout << "Male" << endl;
				cout << person.dob << endl;
				cout << person.social_id << endl;
				cout << person.student_class << endl;
				break;
			}

		}
	}
	ip.close();
}