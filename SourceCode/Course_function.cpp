#include "../struct and function/struct_and_library.h"
#include "../struct and function/course.h"
#include "../struct and function/student.h"

Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, Session teaching_session) {
	Course tmp;
	tmp.course_id = course_id;
	tmp.course_name = course_name;
	tmp.teacher_name = teacher_name;
	tmp.num_credit = num_credit;
	tmp.teaching_session = teaching_session;
	return tmp;
};
CourseNode* initCourseNode(string new_year_id, string new_semester_id, Course new_course)
{
	CourseNode* new_course_node = new CourseNode;
	new_course_node->next = NULL;
	new_course_node->semester_id = new_semester_id;
	new_course_node->year_id = new_year_id;
	new_course_node->course = new_course;
	return new_course_node;
}
void addNewCourseNode(CourseNode*& head, string year_id, string semester_id, Course cs) {
	CourseNode* new_course_node = initCourseNode(year_id,semester_id, cs);
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
void InputCourse(CourseNode*& head) {
	string year="1";
	string semester="1";
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
	cout << endl << "Day of the week: "; //this should convert monday tuesday...
	cin >> cs.teaching_session.day_of_the_week;
	cout << "Session_no (time): ";//this should output the session to choose
	cin >> cs.teaching_session.session_no;
	ifstream ip;
	string filename;
	cout << "Students of this class: " << endl;
	cout << "Enter filename to add students: " <<endl;
	readStudentFromFile(ip,filename, cs.main_class.student_list);
	addNewCourseNode(head, semester, year, cs);
}
void OutputCourse(Course cs) {
	cout << cs.course_id << endl;
	cout << cs.course_name << endl;
	cout << cs.teacher_name << endl;
	cout << "Credits: "<< cs.num_credit  << endl;
	cout << "Day: " << cs.teaching_session.day_of_the_week  << endl;
	cout << "Sesion: "<< cs.teaching_session.session_no << endl;
}
void displayCourse(CourseNode* CourseHead) {
	for (CourseNode* tmp = CourseHead; tmp != NULL; tmp = tmp->next) {
		cout << "-----------" << endl;
		OutputCourse(tmp->course);
		cout << "Course students: " << endl;
		bool choice;
		cout << "enter 1 if you want to see students, 0 if not: ";
		cin >> choice;
		if (choice) displayStudent(tmp->course.main_class.student_list);
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
void updatecourse(CourseNode* CourseHead,string updateCourse, Course newone) {
	CourseNode* target = findcourse(CourseHead, updateCourse);
	target->course = newone;
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
// Import a lot courses from file without students, and export 
void importCourse(CourseNode*& Courselist,string year, string semester, string filename, ifstream& fin) {
	while (1) {
		Course cs;
		string line;
		string number;
		getline(fin, line);
		stringstream ss(line);
		getline(ss, cs.course_id, ',');
		if (cs.course_id == "*") break;
		getline(ss, cs.course_name, ',');
		getline(ss, cs.teacher_name, ',');
		getline(ss, number, ',');
		cs.num_credit = stoi(number);
		getline(ss, number, ',');
		cs.max_students = stoi(number);
		getline(ss, number, ',');
		cs.teaching_session.day_of_the_week = stoi(number);
		getline(ss, number, '\n');
		cs.teaching_session.session_no = stoi(number);
		addNewCourseNode(Courselist, year, semester, cs);
	}
}
void exportCourse(CourseNode* Courselist, string filename, ofstream& fout) {
	for (CourseNode* tmp = Courselist; tmp != NULL; tmp = tmp->next) {
		fout << tmp->course.course_id << ",";
		fout << tmp->course.course_name << ",";
		fout << tmp->course.teacher_name << ",";
		fout << tmp->course.num_credit << ",";
		fout << tmp->course.max_students << ",";
		fout << tmp->course.teaching_session.day_of_the_week << ",";
		fout << tmp->course.teaching_session.session_no << "\n";
	}
	fout << "*" << endl;
}

//Update mycourese whenever add a student into a course
Results createResults(string year_cur, string sem_cur, string cour_cur) {
	Results tmp;
	tmp.year_id = year_cur;
	tmp.semester_id = sem_cur;
	tmp.course_id = cour_cur;
	return tmp;
}
ResultsNode* initResultsNode(Results res)
{
	ResultsNode* new_result_node = new ResultsNode;
	new_result_node->next = NULL;
	new_result_node->results = res;
	return new_result_node;
}
void appendNewResultsNode(ResultsNode*& head, Results res) {
	ResultsNode* new_result_node = initResultsNode(res);
	if (!head)
		head = new_result_node;
	else {
		ResultsNode* list_result = head;
		while (list_result->next) {
			list_result = list_result->next;
		}
		list_result->next = new_result_node;
	}
}

void CourseEnroll(StudentNode*& student_list, CourseNode* curr) {
	if (student_list == nullptr) return;
	for (StudentNode* tmp = student_list; tmp != NULL; tmp = tmp->next) {
		Results res = createResults(curr->year_id, curr->semester_id, curr->course.course_id);
		appendNewResultsNode(tmp->student.my_course, res);
	}
}
//void ViewCourses(StudentNode* )