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
	//Missing enter 0 to go back...
	int sem;
	cout << "Enter semester number: ";
	cin >> sem;
	string semester_id = "Semester " + to_string(sem);

	int start, end;
	cout << "Enter schoolyear:" << endl
		<< "	Enter start year: ";
	cin >> start;
	cout << "	Enter end year: ";
	cin >> end;
	string year_id = to_string(start) + " - " + to_string(end);
	
	if (!pHY)
	{
		pHY = new YearNode;
		Year* syTemp = &(pHY->school_year);
		syTemp->year_id = year_id;
		syTemp->list_sem = new SemesterNode;
		Semester* sTemp = &(syTemp->list_sem->sem);
		sTemp->semester_id = semester_id;
	}
	else
	{
		YearNode* currY = pHY;
		while (currY->next && currY->school_year.year_id != year)
			currY = currY->next;
		if (currY->school_year.year_id != year)
		{
			currY->next = new YearNode;
			currY = currY->next;
			currY->school_year.year_id = year;
		}
	}
}