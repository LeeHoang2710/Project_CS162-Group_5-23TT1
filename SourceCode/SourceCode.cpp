#include "C:\Users\LEGION\Desktop\branches\Project_CS162\struct and function\struct_and_library.h"
#include "Function.h"
#include "../struct and function/student.h"
#include <fstream>
#include <iostream>
CourseNode* initCourseNode(Course new_course, StudentNode* liststu)
{
	CourseNode* new_course_node = new CourseNode;
	new_course_node->next = NULL;
	new_course_node->course = new_course;
	new_course_node->student_list = liststu;
	return new_course_node;
}
void addNewCourseNode(CourseNode*& head, Course cs, StudentNode* liststu) {
	//semester id 
	// year id
	CourseNode* new_course_node = initCourseNode(cs, liststu);
	if (!head)
		head = new_course_node;
	else {
		CourseNode* list_course = head;
		while (list_course->next) {
			list_course = list_course->next;
		}
		list_course->next = new_course_node;
	}
}
void InputCourse(CourseNode*& head ) {
	Course cs;
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
	ifstream ip;
	StudentNode* liststu = NULL;
	readStudentFromFile(ip, liststu);
	addNewCourseNode(head, cs, liststu);
}
void OutputCourse(Course cs) {
	cout << cs.course_id << endl;
	cout << cs.course_name << endl;
	cout << cs.teacher_name << endl;
	cout << "Credits: "<< cs.num_credit  << endl;
	cout << "Day: " << cs.teaching_session[0].day_of_the_week  << endl;
	cout << "Sesion: "<< cs.teaching_session[0].session_no << endl;

}
void displayCourse(CourseNode* CourseHead) {
	for (CourseNode* tmp = CourseHead; tmp != NULL; tmp = tmp->next) {
		cout << "-----------" << endl;
		OutputCourse(tmp->course);
		cout << "Course students: " << endl;
		displayStudent(tmp->student_list);
	}
}









//Login session
void StorePassWordStudent(StudentNode*& StuPass, ifstream& ip) {
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
void StorePassWordStaff(StaffNode*& StaffPass, ifstream& ip) {
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
		StudentNode* tmp = StuPass;
		for (tmp; tmp != NULL; tmp = tmp->next) {
			if (tmp->student.student_id == input_ID) {
				if (tmp->student.password == input_Pass) {
					onstatus_ID = input_ID;
					ChangeStuPass = tmp;
					cout << "Login Succesfully" << endl;
					return;
				}
				else {
					cout << "wrong username or password, please try again" << endl;
					break;
				}
			}
		}
		if (tmp==NULL) cout << "This account is not signed up yet" <<endl;
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
		StaffNode* tmp = StaffPass;
		for (tmp; tmp != NULL; tmp = tmp->next) {
			if (tmp->staff.username == input_UserName) {
				if (tmp->staff.password == input_Pass) {
					onstatus_UserName = input_UserName;
					ChangeStaffPass = tmp;
					cout << "Login Succesfully" << endl;
					return;
				}
				else {
					cout << "wrong username or password, please try again" << endl;
					break;
				}
			}
		}
		if (tmp == NULL) cout << "This account is not signed up yet" << endl;
	}
}
void UpdateStuPassFile(StudentNode* List, ofstream& op) {
	op.open("../database/Students_Password.csv");
	for (StudentNode* tmp = List; tmp != NULL; tmp = tmp->next) {
		op << tmp->student.student_id <<",";
		op << tmp->student.password;
		if (tmp->next != NULL) op << endl;
	}
	op.close();
}
void UpdateStaffPassFile(StaffNode* List, ofstream& op) {
	op.open("../database/Staff_Password.csv");
	for (StaffNode* tmp = List; tmp != NULL; tmp = tmp->next) {
		op << tmp->staff.username << ",";
		op << tmp->staff.password ;
		if (tmp->next != NULL) op << endl;
	}
	op.close();
}
void ChangePassStudent(StudentNode* current) {
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
//new session