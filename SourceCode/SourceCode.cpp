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
void test(Student& x, ifstream& ip) {
	ip.open("C:/Users/LEGION/Desktop/branches/Project_CS162/database/testcourse.csv");
	Student tmp;
	ip >> tmp.num;
	ip.ignore();
	getline(ip, tmp.student_id, ',');
	getline(ip, tmp.first_name, ',');
	getline(ip, tmp.last_name, ',');
	ip >> tmp.gender;
	ip.ignore();
	getline(ip, tmp.dob, ',');
	getline(ip, tmp.social_id, ',');
	getline(ip, tmp.student_class, ',');
	ip.close();
	x = tmp;
	cout << x.num << endl;
	cout << x.student_id << endl; 
	cout << x.first_name << endl;
	cout << x.last_name << endl;
	cout << x.dob << endl;
	cout << x.social_id << endl;
	cout << x.student_class << endl;
	ip.close();
}