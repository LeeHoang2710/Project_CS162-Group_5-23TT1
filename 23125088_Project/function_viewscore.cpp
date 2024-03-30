#include "function.h"
void Viewallmyscore(Student stu)
{
	cout << setw(15) << left << "Course id";
	cout << setw(15) << left << "Year";
	cout << setw(15) << left << "Semester";
	cout << setw(15) << left << "Process";
	cout << setw(15) << left << "Midterm";
	cout << setw(15) << left << "Final";
	cout << setw(15) << left << "Overall";
	cout << "\n";
	MyCourse* mycourse = stu.my_course;
	while (mycourse)
	{
		cout << setw(15) << left << mycourse->subject_code;
		cout << setw(15) << left << mycourse->year;
		cout << setw(15) << left << mycourse->sem;
		cout << setw(15) << left << mycourse->score.process;
		cout << setw(15) << left << mycourse->score.midterm;
		cout << setw(15) << left << mycourse->score.final;
		cout << setw(15) << left <<fixed<<setprecision(1) <<  mycourse->score.overall;
		mycourse = mycourse->next;
		cout << "\n";
	}
	cout << "Your curren gpa is: " << stu.cur_gpa << "\n";
	cout << "Your total gpa is: " << stu.total_gpa << "\n";
}
void Findoverall(StudentNode* stu) 
{
	while (stu) 
	{
		stu->student.my_course->score.overall = stu->student.my_course->score.final * 0.40 + stu->student.my_course->score.midterm * 0.25 + stu->student.my_course->score.process * 0.35;
		stu = stu->next;
	}
}
void Viewgpaallstudent(StudentNode* stuhead) 
{
	cout << setw(15) << left << "Student-id";
	cout << setw(15) << left << "lastname" << setw(15) << left << "firstname";
	cout << setw(20) << left << "date of birth" << setw(15) << left << "gender";
	cout << setw(15) << left << "social-id" << setw(15) << left << "current-gpa";
	cout << setw(15) << left << "total-gpa";
	cout << "\n";
	while (stuhead)
	{
		cout << setw(15) << left << stuhead->student.student_id;
		cout << setw(15) << left << stuhead->student.last_name;
		cout << setw(15) << left << stuhead->student.first_name;
		cout << setw(20) << left << stuhead->student.dob;
		if (stuhead->student.gender)
			cout << setw(15) << left << "Male";

		else
			cout << setw(15) << left << "Female";
		cout << setw(15) << left << stuhead->student.social_id;
		cout << setw(15) << left << stuhead->student.cur_gpa;
		cout << setw(15) << left << stuhead->student.total_gpa << "\n";
		stuhead = stuhead->next;
	}
}