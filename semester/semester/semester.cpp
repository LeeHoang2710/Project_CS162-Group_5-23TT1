#include "../semester.h"

bool checkFailedInput()
{
	//unfinished
	if (cin.fail()) {
		cout << "Invalid character input. Please try again." << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void createSemester(YearNode*& pHY)
{
	cout << "You are creating a new semester." << endl;
	//Missing enter 0 to go back..., enter num to do sth
	//Enter semester and school year
	int sem;
	cout << "Enter semester number: ";
	cin >> sem;
	string semester_id = "Semester " + to_string(sem);

	int start, end;
	cout << "Enter school year:" << endl
		<< "	Enter start year: ";
	cin >> start;
	cout << "	Enter end year: ";
	cin >> end;
	string year_id = to_string(start) + " - " + to_string(end);
	
	//Check and add semester
	YearNode* currY = pHY;
	if (!pHY)
	{
		pHY = new YearNode;
		Year* syTemp = &(pHY->school_year);
		syTemp->year_id = year_id;
		syTemp->list_sem = new SemesterNode;
		Semester* sTemp = &(syTemp->list_sem->sem);
		sTemp->semester_id = semester_id;
		currY = pHY;
	}
	else
	{
		while (currY->next && currY->school_year.year_id != year_id)
			currY = currY->next;
		if (currY->school_year.year_id != year_id)
		{
			currY->next = new YearNode;
			currY = currY->next;
			Year* syTemp = &(currY->school_year);
			syTemp->year_id = year_id;
			syTemp->list_sem = new SemesterNode;
			Semester* sTemp = &(syTemp->list_sem->sem);
			sTemp->semester_id = semester_id;
		}
		else
		{
			SemesterNode* sNTemp = currY->school_year.list_sem;
			while (sNTemp->next && sNTemp->sem.semester_id == semester_id)
				sNTemp = sNTemp->next;
			if (sNTemp->sem.semester_id != semester_id)
			{
				sNTemp->next = new SemesterNode;
				sNTemp = sNTemp->next;
				sNTemp->sem.semester_id = semester_id;
			}
			else
			{
				cout << "Semester already exists. Please try again." << endl;
				createSemester(pHY);
				return;
			}
		}
	}
}

void deleteSemester(YearNode*& pHY);
{

}
