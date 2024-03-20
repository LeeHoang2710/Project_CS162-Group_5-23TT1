#include "../session.h"

string itosDOTW(int d)
{
	switch (d)
	{
	case 2:
		return "MON";
	case 3:
		return "TUE";
	case 4:
		return "WED";
	case 5:
		return "THU";
	case 6:
		return "FRI";
	case 7:
		return "SAT";
	default:
		return "invalid day";
	}
}
string itosSessionNo(int s)
{
	switch (s)
	{
	case 1:
		return "S1 (07:30)";
	case 2:
		return "S2 (09:30)";
	case 3:
		return "S3 (13:30)";
	case 4:
		return "S4 (15:30)";
	default:
		return "invalid session";
	}
}

int stoiDOTW(string d)
{
	if (d == "MON") return 2;
	if (d == "TUE") return 3;
	if (d == "WED") return 4;
	if (d == "THU") return 5;
	if (d == "FRI") return 6;
	if (d == "SAT") return 7;
	return -1;
}
int stoiSessionNo(string s)
{
	if (s == "S1 (07:30)") return 1;
	if (s == "S2 (09:30)") return 2;
	if (s == "S3 (13:30)") return 3;
	if (s == "S4 (15:30)") return 4;
	return -1;
}

void exportCourseForDisplay(CourseNode* course_list, const string& filename, ofstream& fout)
{
	fout.open(filename);
	if (!fout.is_open())
	{
		cout << "Cannot open " << filename << " to export courses for display." << endl;
		fout.close();
		return;
	}

	while (course_list)
	{
		Course* course = &course_list->course;
		fout << course->course_id << ","
			<< course->course_name << ","
			<< course->teacher_name << ","
			<< course->num_credit << ","
			<< course->max_students << ","
			<< itosDOTW(course->teaching_session.day_of_the_week) << ","
			<< itosSessionNo(course->teaching_session.session_no) << endl;
		course_list = course_list->next;
	}

	fout.close();
}
