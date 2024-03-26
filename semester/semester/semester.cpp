#include "../semester.h"

//database/semester.csv

void importYearSemester(YearNode*& year_list, string filename, ifstream& fin)
{
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Cannot open " << filename << " to import school year and semester information." << endl;
		return;
	}

	YearNode* currYear = year_list;
	string line;
	while (getline(fin, line))
	{
		istringstream ss(line);
		string year_id, sem_id, start_date, end_date;
		getline(ss, year_id, ',');
		getline(ss, sem_id, ',');
		getline(ss, start_date, ',');
		getline(ss, end_date, ',');

		if (!currYear || currYear->school_year.year_id != year_id)
		{
			YearNode* newYearNode = initYearNode(createYear(year_id));
			if (!currYear)
				year_list = newYearNode;
			else
				currYear->next = newYearNode;

			currYear = newYearNode;
		}

			Semester newSem = createSemester(sem_id, start_date, end_date);
			SemesterNode* newSemNode = createSemesterNode(newSem);
			appendSemesterNode(currYear->school_year.list_sem, newSemNode);
	}

	fin.close();
}

void exportYearSemester(YearNode* year_list, string filename, ofstream& fout)
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
		SemesterNode* currSem = year_list->school_year.list_sem;
		while (currSem)
		{
			fout << year_list->school_year.year_id << ","
				<< currSem->sem.semester_id << ","
				<< currSem->sem.start_date << ","
				<< currSem->sem.end_date << endl;
			currSem = currSem->next;
		}

		year_list = year_list->next;
	}

	fout.close();
}

void inputSemester(string& sem_id, string& start_date, string& end_date)
{
	int sem_num;
	cout << "Enter semester number (1, 2, or 3): ";
	cin >> sem_num;
	sem_id = "Semester " + to_string(sem_num);
	cout << "Enter start date (dd/mm/yyyy): ";
	cin >> start_date;
	cout << "Enter end date (dd/mm/yyyy): ";
	cin >> end_date;
}

Semester createSemester(const string& sem_id, const string& start_date, const string& end_date)
{
	// In this order: semester_id, start_date, end_date, course_list
	return Semester{ sem_id, start_date, end_date, nullptr };
}

SemesterNode* createSemesterNode(const Semester& new_sem)
{
	return new SemesterNode{ new_sem, nullptr };
}

void addCourseListToSemester(SemesterNode*& semNode, CourseNode* course_list)
{
	semNode->sem.course_list = course_list;
}

void appendSemesterNode(SemesterNode*& sem_list, SemesterNode* new_sem_node)
{
	if (!sem_list)
		sem_list = new_sem_node;
	else
	{
		SemesterNode* curr = sem_list;
		while (curr->next)
			curr = curr->next;

		curr->next = new_sem_node;
	}
}

void updateSemesterInfo(SemesterNode* semNode, const string& new_sem_id, const string& new_start_date, const string& new_end_date)
{
	if (semNode->sem.semester_id != new_sem_id)
		semNode->sem.semester_id = new_sem_id;

	if (semNode->sem.start_date != new_start_date)
		semNode->sem.start_date = new_start_date;

	if (semNode->sem.end_date != new_end_date)
		semNode->sem.end_date = new_end_date;
}

SemesterNode* searchSemesterNode(YearNode* year_list, const string& year_id, int sem_num)
{
	YearNode* yearNode = searchYearNode(year_list, year_id);
	if (!yearNode)
		return nullptr;

	SemesterNode* semNode = yearNode->school_year.list_sem;
	if (!semNode)
	{
		cout << "There are no semesters in school year " << year_id << "." << endl;
		return nullptr;
	}

	string sem_id = "Semester " + to_string(sem_num);
	while (semNode)
	{
		if (semNode->sem.semester_id == sem_id)
			return semNode;

		semNode = semNode->next;
	}

	cout << sem_id << " does not exist in school year " << year_id << endl;
	return nullptr;
}

bool removeSemesterNode(YearNode* year_list, const string& year_id, int sem_num)
{
	SemesterNode* semNode = searchSemesterNode(year_list, year_id, sem_num);
	if (!semNode)
	{
		//cout << "Semester does not exist." << endl;
		return false;
	}

	YearNode* yearNode = searchYearNode(year_list, year_id);

	if (yearNode->school_year.list_sem == semNode)
		yearNode->school_year.list_sem = semNode->next;
	else
	{
		SemesterNode* prev = yearNode->school_year.list_sem;
		while (prev->next != semNode)
			prev = prev->next;

		prev->next = semNode->next;
	}

	// delete inside
	// deleteCourseList(semNode->sem.course_list);
	delete semNode;
	return true;
}

void deleteYearList(YearNode*& year_list)
{
	while (year_list)
	{
		YearNode* temp = year_list;
		year_list = year_list->next;
		deleteSemesterList(temp->school_year.list_sem);
		delete temp;
	}
}

void deleteSemesterList(SemesterNode*& sem_list)
{
	while (sem_list)
	{
		SemesterNode* temp = sem_list;
		sem_list = sem_list->next;
		// deleteCourseList function, and more...
		// deleteCourseList(temp->sem.course_list);...
		delete temp;
	}
}

void deleteResultsList(ResultsNode* results_list)
{
	while (results_list)
	{
		ResultsNode* temp = results_list;
		results_list = results_list->next;
		delete temp;
	}
}

void deleteStudentList(StudentNode*& student_list)
{
	while (student_list)
	{
		StudentNode* temp = student_list;
		student_list = student_list->next;
		deleteResultsList(temp->student.results_list);
		delete temp;
	}
}
