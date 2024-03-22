#include "../semester.h"

//database/semester.csv
//ignore C6011 and C28182 warnings

YearNode* importYearSemester(const string& filename, ifstream& fin)
{
	YearNode* year_list = nullptr;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Cannot open " << filename << " to import school year and semester information." << endl;
		fin.close();
		return nullptr;
	}

	YearNode* currYear = nullptr;
	SemesterNode* currSem = nullptr;
	string line;
	while (getline(fin, line))
	{
		istringstream ss(line);
		//Process YearNode
		string year_id;
		getline(ss, year_id, ',');
		if (!year_list)
		{
			year_list = initYearNode(createYear(year_id));
			currYear = year_list;
		}
		else if (currYear->school_year.year_id != year_id)
		{
			currYear->next = initYearNode(createYear(year_id));
			currYear = currYear->next;
		}
		//Process SemesterNode
		if (!currYear->school_year.list_sem)
		{
			currYear->school_year.list_sem = new SemesterNode;
			currSem = currYear->school_year.list_sem;
		}
		else if (currSem)
		{
			currSem->next = new SemesterNode;
			currSem = currSem->next;
		}

		getline(ss, currSem->sem.semester_id, ',');
		getline(ss, currSem->sem.start_date, ',');
		getline(ss, currSem->sem.end_date, ',');
	}

	fin.close();
	return year_list;
}
void exportYearSemester(YearNode* year_list, const string& filename, ofstream& fout)
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
	fout.flush();
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
	Semester sem;
	sem.semester_id = sem_id;
	sem.start_date = start_date;
	sem.end_date = end_date;
	return sem;
}
SemesterNode* createSemesterNode(const Semester& new_sem)
{
	SemesterNode* newSemNode = new SemesterNode;
	newSemNode->sem = new_sem;
	return newSemNode;
}
void addCourseListToSemester(SemesterNode*& semNode, CourseNode* course_list)
{
	semNode->sem.course_list = course_list;
}
void addSemesterNode(SemesterNode*& sem_list, SemesterNode* new_sem_node)
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
//add case of removing the first semester node
void removeSemesterNode(YearNode* year_list, const string& year_id, int sem_num)
{
	SemesterNode* semNode = searchSemesterNode(year_list, year_id, sem_num);
	if (!semNode)
	{
		cout << "Semester does not exist." << endl;
		return;
	}

	// Delete the course list inside the semester node
	//deleteCourseList(semNode->sem.course_list);

	// Find the prev semester node
	YearNode* yearNode = searchYearNode(year_list, year_id);
	if (yearNode->school_year.list_sem == semNode)
		yearNode->school_year.list_sem = semNode->next;
	else
	{
		SemesterNode* curr = yearNode->school_year.list_sem;
		while (curr->next != semNode)
			curr = curr->next;

		curr->next = semNode->next;
	}

	delete semNode;
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
void updateSemester(SemesterNode* sem, const string& new_sem_id, const string& new_start_date, const string& new_end_date)
{
	if (sem->sem.semester_id != new_sem_id)
		sem->sem.semester_id = new_sem_id;

	if (sem->sem.start_date != new_start_date)
		sem->sem.start_date = new_start_date;

	if (sem->sem.end_date != new_end_date)
		sem->sem.end_date = new_end_date;
}

void deleteYearList(YearNode*& year_list)
{
	YearNode* curr = year_list;
	while (curr)
	{
		deleteSemesterList(curr->school_year.list_sem);
		YearNode* temp = curr;
		curr = curr->next;
		delete temp;
	}

	year_list = nullptr;
}
void deleteSemesterList(SemesterNode*& sem_list)
{
	SemesterNode* curr = sem_list;
	while (curr)
	{
		// Delete the course list inside the semester node
		//deleteCourseList(curr->sem.course_list);
		SemesterNode* temp = curr;
		curr = curr->next;
		delete temp;
	}

	sem_list = nullptr;
}
