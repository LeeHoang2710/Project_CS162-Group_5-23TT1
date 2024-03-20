#include "../session.h"

string formatDOTW(int d)
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
string formatSessionNo(int s)
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
			<< formatDOTW(course->teaching_session.day_of_the_week) << ","
			<< formatSessionNo(course->teaching_session.session_no) << endl;
		course_list = course_list->next;
	}
}
