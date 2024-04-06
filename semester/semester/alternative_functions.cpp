#include "../alternative_functions.h"

void importYear(YearNode*& year_list, const string& filename, ifstream& fin)
{
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Cannot open " << filename << " to import school year and semester information." << endl;
		return;
	}

	string line;
	while (getline(fin, line))
	{
		Year new_year = createYear(line);
		for (int i = 0; i < 3; ++i)
		{
			if (fin.eof() || line == "#")
				break;

			importSemester(new_year.list_sem, fin, new_year.year_id);
		}
		appendYearNode(year_list, initYearNode(new_year));
	}

	fin.close();
}

void importSemester(SemesterNode* sem_list, ifstream& fin, const string& year_id)
{
	string line;
	getline(fin, line);
	istringstream is(line);
	string start_date, end_date, sem_id;
	getline(is, sem_id, ',');
	getline(is, start_date, ',');
	getline(is, end_date, '\n');

	// Create a new Semester
	Semester new_sem = createSemester(sem_id, start_date, end_date);
	//import course, class year, class, extra students, extra students' results
	importCourseInSem(new_sem.course_list, fin, new_sem.semester_id, year_id);
	// Append the new Semester to the sem_list
	appendSemesterNode(sem_list, createSemesterNode(new_sem));
}

void exportYear(YearNode* year_list, string filename, ofstream& fout)
{
	fout.open(filename);
	if (!fout.is_open())
	{
		cout << "Cannot open " << filename << " to export school year and semester information." << endl;
		fout.close();
		return;
	}

	while (year_list)
	{
		fout << year_list->school_year.year_id << endl;
		exportSemesterInYear(year_list->school_year.list_sem, fout);
		year_list = year_list->next;
		if (year_list)
			fout << endl;
	}

	fout.close();
}

void exportSemester(SemesterNode* sem_list, ofstream& fout)
{
	while (sem_list)
	{
		fout << sem_list->sem.semester_id << ","
			<< sem_list->sem.start_date << ","
			<< sem_list->sem.end_date << endl;
		sem_list = sem_list->next;
	}
}

void importCourseInSem(CourseNode*& Courselist, ifstream& fin, const string& semester_id, const string& year_id)
{
	string number;
	while (getline(fin, number))
	{
		Course cs;

		stringstream line(number);
		getline(line, cs.course_id, ',');
		getline(line, cs.course_name, ',');
		getline(line, cs.teacher_name, ',');
		getline(line, number, ',');
		cs.num_credit = stoi(number);
		getline(line, number, ',');
		cs.max_students = stoi(number);
		getline(line, number, ',');
		cs.teaching_session.day_of_the_week = stoi(number);
		getline(line, number, '\n');
		cs.teaching_session.session_no = stoi(number);


		
		appendCourseNode(Courselist, cs, semester_id, year_id);
	}
}

void appendCourseNode(CourseNode*& head, Course cs, const string& semester_id, const string& year_id)
{
	CourseNode* new_course_node = initCourseNode(cs);
	new_course_node->semester_id = semester_id;
	new_course_node->year_id = year_id;
	if (!head)
		head = new_course_node;
	else
	{
		CourseNode* list_course = head;
		while (list_course->next)
			list_course = list_course->next;
		list_course->next = new_course_node;
	}
}
