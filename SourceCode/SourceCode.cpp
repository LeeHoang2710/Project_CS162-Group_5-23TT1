#include "C:\Users\LEGION\Desktop\branches\Project_CS162\struct and function\struct_and_library.h"
#include "Function.h"
#include "../struct and function/student.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, Session teaching_session) {
	Course tmp;
	tmp.course_id = course_id;
	tmp.course_name = course_name;
	tmp.teacher_name = teacher_name;
	tmp.num_credit = num_credit;
	tmp.teaching_session[0] = teaching_session;
	return tmp;
};
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
	cout << "enter 1 if your want to input from file, enter 0 if your want to input by hand";
	bool choice;
	cin >> choice;
	cin.ignore();
	if (choice==1) {
		readStudentFromFile(ip, liststu);
	}
	else {
		cout << "enter info of student you want to add (enter 0 to stop) " << endl;
		while (readStudentFromTerminal(liststu)) {
		}
	}
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
		bool choice;
		cout << "enter 1 if you want to see students, 0 if not: ";
		cin >> choice;
		if (choice) displayStudent(tmp->student_list);
	}
}
CourseNode* findcourse(CourseNode* CourseHead, string course_find) {
	for (CourseNode* tmp = CourseHead; tmp != NULL; tmp = tmp->next) {
		if (tmp->course.course_id == course_find) {
			return tmp;
		}
	}
	return NULL;
}
void updatecourse(CourseNode* CourseHead,string updateCourse) {
	/*findCourse */
	CourseNode* target = findcourse(CourseHead, updateCourse);
	//ask user what they want to change
	//target.semesterid
	//....
	int choice;
	cout << "enter information you want to update: ";
	cout << "1. course id" << endl;
	cout << "2. course name" << endl;
	cout << "3. teacher name" << endl;
	cout << "4. numbers of credit " << endl;
	cout << "5. teaching session " << endl;
	cout << "6. student list" << endl; // not yet 
	while (1) {
		cout << endl << "enter your choice (enter 0 if you do not want to update anymore)";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "new course id: ";
			cin >> target->course.course_id;
			break;
		case 2:
			cout << "new course name: ";
			cin >> target->course.course_name;
			break;
		case 3:
			cout << "new teacher name: ";
			cin >> target->course.teacher_name;
			break;
		case 4:
			cout << "new course id: ";
			cin >> target->course.num_credit;
			break;
		case 5:
			cout << "new teaching session ";
			cout << endl << "day of the week: ";
			cin >> target->course.teaching_session[0].day_of_the_week;
			cout << endl << "session: ";
			cin >> target->course.teaching_session[0].session_no;
		case 0:
			return;
		}
	}
}
void deletecourse(CourseNode* CourseHead,string delCourse) {
	if (CourseHead->course.course_id == delCourse) {
		CourseNode* tmp = CourseHead;
		CourseHead = CourseHead->next;
		delete tmp;
	}
	for (CourseNode* tmp = CourseHead; tmp->next != nullptr; tmp = tmp->next) {
		if (tmp->next->course.course_id == delCourse) {
			CourseNode* del = tmp->next;
			tmp->next = tmp->next->next;
			delete del;
		}
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