#include "struct_and_library.h"
void Loadcoursescorefromfile(ifstream& fin,StudentNode* &Studentlist) {
	StudentNode* tmp1 = nullptr;
	string Line;
	while (getline(fin, Line, '\n') && Line != "") {
		if (Line != "*") {
			StudentNode* tmp = nullptr;
			if (!Studentlist) {
				Studentlist = new StudentNode();
				Studentlist->next = nullptr;
				stringstream ss1(Line);
				string s1;
				getline(ss1, s1, ',');
				Studentlist->student.student_id = s1;
				getline(ss1, s1, ',');
				Studentlist->student.first_name = s1;
				getline(ss1, s1, ',');
				Studentlist->student.last_name = s1;
				tmp1 = Studentlist;
				tmp = Studentlist;
			}
			else {
				StudentNode* newstudent = new StudentNode();
				newstudent->next = nullptr;
				stringstream ss1(Line);
				string s1;
				getline(ss1, s1, ',');
				newstudent->student.student_id = s1;
				getline(ss1, s1, ',');
				newstudent->student.first_name = s1;
				getline(ss1, s1, ',');
				newstudent->student.last_name = s1;
				tmp1->next = newstudent;
				tmp1 = tmp1->next;
				tmp = newstudent;
			}
			ResultsNode* Resulist = nullptr;
			ResultsNode* tmp2 = nullptr;
			while (getline(fin, Line, '\n')) {
				if (Line != "*") {
					if (!Resulist) {
						Resulist = new ResultsNode();
						Resulist->next = nullptr;
						stringstream ss2(Line);
						string s2;
						getline(ss2, s2, ',');
						Resulist->results.course_id = s2;
						getline(ss2, s2, ',');
						Resulist->results.year_id = s2;
						getline(ss2, s2, ',');
						Resulist->results.sem_id = s2;
						float fl;
						getline(ss2, s2, ',');
						if (s2.size() == 3) {
							fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
							Resulist->results.score.process = fl;
						}
						else
							Resulist->results.score.process = (float)(s2[0] - '0');
						getline(ss2, s2, ',');
						if (s2.size() == 3) {
							fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
							Resulist->results.score.midterm = fl;
						}
						else
							Resulist->results.score.midterm = (float)(s2[0] - '0');
						getline(ss2, s2, ',');
						if (s2.size() == 3) {
							fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
							Resulist->results.score.final = fl;
						}
						else
							Resulist->results.score.final = (float)(s2[0] - '0');
						tmp2 = Resulist;
					}
					else {
						ResultsNode* newResulist = new ResultsNode();
						newResulist->next = nullptr;
						stringstream ss2(Line);
						string s2;
						getline(ss2, s2, ',');
						newResulist->results.course_id = s2;
						getline(ss2, s2, ',');
						newResulist->results.year_id = s2;
						getline(ss2, s2, ',');
						newResulist->results.sem_id = s2;
						float fl;
						getline(ss2, s2, ',');
						if (s2.size() == 3) {
							fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
							newResulist->results.score.process = fl;
						}
						else
							newResulist->results.score.process = (float)(s2[0] - '0');
						getline(ss2, s2, ',');
						if (s2.size() == 3) {
							fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
							newResulist->results.score.midterm = fl;
						}
						else
							newResulist->results.score.midterm = (float)(s2[0] - '0');
						getline(ss2, s2, ',');
						if (s2.size() == 3) {
							fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
							newResulist->results.score.final = fl;
						}
						else
							newResulist->results.score.final = (float)(s2[0] - '0');
						tmp2->next = newResulist;
						tmp2 = tmp2->next;
					}
				}
				else
					break;
			}

			tmp->student.results_list = Resulist;
		}
	}
}
void Viewallscore(StudentNode* Studentlist)
{
	while (Studentlist) {
		ResultsNode* resulist = Studentlist->student.results_list;
		cout << Studentlist->student.student_id << ' ';
		cout << Studentlist->student.last_name << ' ' << Studentlist->student.first_name << "\n";
		cout << setw(15) << left << "Course id";
		cout << setw(15) << left << "Year";
		cout << setw(15) << left << "Semester";
		cout << setw(15) << left << "Process";
		cout << setw(15) << left << "Midterm";
		cout << setw(15) << left << "Final";
		cout << setw(15) << left << "Overall";
		cout << "\n";
		while (resulist)
		{
			cout << setw(15) << left << resulist->results.course_id;
			cout << setw(15) << left << resulist->results.year_id;
			cout << setw(15) << left << resulist->results.sem_id;
			cout << setw(15) << left << resulist->results.score.process;
			cout << setw(15) << left << resulist->results.score.midterm;
			cout << setw(15) << left << resulist->results.score.final;
			cout << setw(15) << left << fixed << setprecision(1) << resulist->results.score.overall;
			resulist = resulist->next;
			cout << "\n";
		}
		Studentlist = Studentlist->next;
	}
}
void Findoverall(StudentNode* stu)
{
	while (stu)
	{
		stu->student.results_list->results.score.overall = stu->student.results_list->results.score.process * 0.35 + stu->student.results_list->results.score.midterm * 0.25 + stu->student.results_list->results.score.final * 0.35;
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
		if (!stuhead->student.gender)
			cout << setw(15) << left << "Male";

		else
			cout << setw(15) << left << "Female";
		cout << setw(15) << left << stuhead->student.social_id;
		cout << setw(15) << left << stuhead->student.cur_gpa;
		cout << setw(15) << left << stuhead->student.total_gpa << "\n";
		stuhead = stuhead->next;
	}
}
