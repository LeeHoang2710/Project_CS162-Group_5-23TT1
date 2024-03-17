#include "C:\Users\LEGION\Desktop\branches\Project_CS162\struct and function\struct_and_library.h"
#include "Function.h"
#include <fstream>
#include <iostream>
void InputCourse(Course& cs, ifstream& ip) {
	cout << "Course id: ";
	cin >> cs.course_id; 
	cout << "Course name: ";
	cin.ignore();
	getline(cin, cs.course_name);
	cout << "Teacher name: ";
	getline(cin, cs.teacher_name);
	cout << "Nums of credits: ";
	cin >> cs.num_credit;
	cout << "Teaching time ";
	cout << endl << "Day of the week: "; //this shoulde convert monday tuesday...
	cin >> cs.teaching_session[0].day_of_the_week;
	cout << "Session_no (time): ";//this should output the session to choose
	cin >> cs.teaching_session[0].session_no;
}
void AddStudent2Course(CourseNode*& csnode, Course cs,ifstream& ip) {
	ip.open("../database/testcourse.csv");
	if (csnode == NULL) {
		csnode = new CourseNode();
		csnode->next = NULL;
		csnode->course = cs;
	}
	//input student list from file
	StudentNode* cur = csnode->student_list;
	Student tmp;
	ip >> tmp.num;
	ip.ignore();
	getline(ip, tmp.student_id, ',');
	getline(ip, tmp.first_name,',');
	getline(ip, tmp.last_name,',');
	ip >> tmp.gender;
	ip.ignore();
	getline(ip, tmp.dob,',');
	getline(ip, tmp.social_id,',');
	getline(ip, tmp.password, ',');
	getline(ip, tmp.student_class,'\n');
	int loop = 5;
	while(!ip.eof()) {
		if (csnode->student_list == nullptr) {
			csnode->student_list = new StudentNode;
			cur = csnode->student_list;
		}
		else {
			cur->next = new StudentNode();
			cur = cur->next;
		}
		cur->student = tmp;
		cur->next = NULL;
		ip >> tmp.num;
		ip.ignore();
		getline(ip, tmp.student_id, ',');
		getline(ip, tmp.first_name, ',');
		getline(ip, tmp.last_name, ',');
		ip >> tmp.gender;
		ip.ignore();
		getline(ip, tmp.dob, ',');
		getline(ip, tmp.social_id, ',');
		getline(ip, tmp.password, ',');
		getline(ip, tmp.student_class, '\n');
	}
	ip.close();
}
void OutputCourse(Course cs) {
	cout << "-----VIEWING INFORMATION------" << endl;
	cout << cs.course_id << endl;
	cout << cs.course_name << endl;
	cout << cs.teacher_name << endl;
	cout << "Credits: "<< cs.num_credit  << endl;
	cout << "Day: " << cs.teaching_session[0].day_of_the_week << " (Mon)" << endl;
	cout << "Sesion: "<< cs.teaching_session[0].session_no << endl;

}
void display(CourseNode* CourseHead) {
	for (CourseNode* tmp = CourseHead; tmp != NULL; tmp = tmp->next) {
		OutputCourse(tmp->course);
		cout << "Course students: " << endl;
		StudentNode* tmpstu = tmp->student_list;
		while (tmpstu != NULL) {
			cout << tmpstu->student.num << ", ";
			cout << tmpstu->student.student_id << ", ";
			cout << tmpstu->student.first_name << " ";
			cout << tmpstu->student.last_name << ", ";
			if (tmpstu->student.gender==0) {
				cout << "male, ";
			}
			else cout << "female, ";
			cout << tmpstu->student.dob << ", ";
			cout << tmpstu->student.social_id << ", ";
			cout << tmpstu->student.password << ", ";
			cout << tmpstu->student.student_class << "\n";
			tmpstu = tmpstu->next;
		}
	}
}
//Login session
void StorePassWord_Student(StudentNode*& StuPass, ifstream& ip) {
	StudentNode* cur=StuPass;
	Student tmp;
	getline(ip, tmp.student_id, ',');
	getline(ip, tmp.password, '\n');
	while (1) {
		if (StuPass==NULL) {
			StuPass = new StudentNode;
			cur = StuPass;
		}
		else {
			cur->next = new StudentNode;
			cur = cur->next;
		}
		cur->student = tmp;
		cur->next = NULL;
		if (ip.eof()) return;
		getline(ip, tmp.student_id, ',');
		getline(ip, tmp.password, '\n');
	}
}
void StorePassWord_Staff(StaffNode*& StaffPass, ifstream& ip) {
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
		if (ip.eof()) return;
		getline(ip, tmp.username, ',');
		getline(ip, tmp.password, '\n');
	}
}
void LoginForStudent(StudentNode* StuPass, string& onstatus_ID, StudentNode*& ChangeStuPass) {
	while (1) {
		string input_ID;
		string input_Pass;
		cout << "Enter your username: ";
		cin >> input_ID;
		cout << "Enter your password: ";
		cin >> input_Pass;
		for (StudentNode* tmp = StuPass; tmp != NULL; tmp = tmp->next) {
			if (tmp->student.student_id == input_ID) {
				if (tmp->student.password == input_Pass) {
					onstatus_ID = input_ID;
					ChangeStuPass = tmp;
					cout << "Login Succesfully" << endl;
					return;
				}
				else {
					cout << "wrong username or password, please try again" << endl;
				}
			}
		}
		cout << "This account is not signed up yet" <<endl;
		return;
	}
}
void LoginForStaff(StaffNode* StaffPass, string& onstatus_UserName, StaffNode*& ChangeStaffPass) {
	while (1) {
		string input_UserName;
		string input_Pass;
		cout << "Enter your username: ";
		cin >> input_UserName;
		cout << "Enter your password: ";
		cin >> input_Pass;
		for (StaffNode* tmp = StaffPass; tmp != NULL; tmp = tmp->next) {
			if (tmp->staff.username == input_UserName) {
				if (tmp->staff.password == input_Pass) {
					onstatus_UserName = input_UserName;
					ChangeStaffPass = tmp;
					cout << "Login Succesfully" << endl;
					return;
				}
				else {
					cout << "wrong username or password, please try again" << endl;
				}
			}
		}
		cout << "This account is not signed up yet" << endl;
		return;
	}
}
void UpdateStuPassFile(StudentNode* List, ofstream& op) {
	op.open();
	for (qStudentNode* tmp = List; tmp != NULL; tmp = tmp->next) {
		op << tmp->student.student_id <<;
		op << tmp->student.dob;
	}
	op.close();
}
void ChangePassStudent(StudentNode* current, ofstream& op) {
	while (1) {
		string input_Pass;
		cout << "Enter your current password: ";
		cin >> input_Pass;
		if (current->student.password == input_Pass) {
			cout << "Enter your new password: ";
			cin >> input_Pass;
			current->student.password = input_Pass;
			cout << "Password changed successfully " <<endl;
			return;
		}
		else {
			cout << "current password is wrong, please try again" << endl;
		}
	}
}
void ChangePassStaff(StaffNode* current) {
	while (1) {
		string input_Pass;
		cout << "Enter your current password: ";
		cin >> input_Pass;
		if (current->staff.password == input_Pass) {
			cout << "Enter your new password: ";
			cin >> input_Pass;
			current->staff.password = input_Pass;
			cout << "Password changed successfully" << endl;
			return;
		}
		else {
			cout << "current password is wrong, please try again" << endl;
		}
	}
}
void 
//new session