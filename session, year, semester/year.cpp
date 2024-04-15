#include "./year.h"
#include "./semester.h"
#include "../SourceCode/class.h"

void inputYearId(string& year_id)
{
	cout << "Enter year ID: ";
	cin >> year_id;
}

Year createYear(const string& p_year_id)
{
	return Year{ p_year_id, nullptr };
}

YearNode* initYearNode(const Year& p_school_year)
{
	return new YearNode{ p_school_year, nullptr };
}

void appendYearNode(YearNode*& head, YearNode* new_year_node)
{
	if (!head)
		head = new_year_node;
	else
	{
		YearNode* curr = head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_year_node;
	}
}
void addNewYearNode(YearNode*& head, Year p_year)
{
	YearNode* new_year_node = initYearNode(p_year);
	if (!head)
		head = new_year_node;
	else
	{
		YearNode* list_year = head;
		while (list_year->next)
			list_year = list_year->next;
		list_year->next = new_year_node;
	}
	return;
}

void updateYearId(YearNode* yearNode, const string& year_id)
{
	yearNode->school_year.year_id = year_id;
}

bool removeYearNode(YearNode*& head, const string& year_id)
{
	YearNode* yearNode = searchYearNode(head, year_id);
	if (!yearNode)
	{
		//cout << "Cannot find the year to be deleted." << endl;
		return false;
	}

	if (head == yearNode)
		head = yearNode->next;
	else
	{
		YearNode* prev = head;
		while (prev->next != yearNode)
			prev = prev->next;

		prev->next = yearNode->next;
	}

	deleteSemesterList(yearNode->school_year.list_sem); // delete inside
	delete yearNode;
	return true;
}

YearNode* searchYearNode(YearNode* head, const string& year_id)
{
	while (head)
	{
		if (head->school_year.year_id == year_id)
			return head;

		head = head->next;
	}

	return nullptr;
}
void importClass(ClassNode*& classes, stringstream& ss, ifstream& fin) {
	string oneclass;
	while (getline(ss, oneclass, ',')) {
		Class newclass = CreateClass(oneclass);
		AddClassNode(classes, newclass);
	}
};
void importYear(YearNode*& year_list, string filename, ifstream& fin)
{
	fin.open(filename);

	string line;
	while (getline(fin, line))
	{
		Year new_year = createYear(line);
		getline(fin, line, 'n');
		stringstream clstr(line);
		if (line == "#") continue;
		else importClass(year_list->school_year.allclass, clstr, fin);
		for (int i = 0; i < 3; ++i)
		{
			if (fin.eof()) break;
			getline(fin, line, '\n');
			if (line == "#") break;
			stringstream ss(line);
			importSemester(new_year.list_sem, ss, fin);
		}
		addNewYearNode(year_list, new_year);
	}

	fin.close();
}

void exportYear(YearNode* year_list, string filename, ofstream& fout)
{
	fout.open(filename);

	YearNode* currYear = year_list;
	while (currYear)
	{
		fout << currYear->school_year.year_id << endl;
		if (!currYear->school_year.list_sem)
			fout << "#" << endl;
		else
			exportSemesterInYear(currYear->school_year.list_sem, fout);
		currYear = currYear->next;
	}

	fout.close();
}
void exportYear(YearNode*& year_list, string filename, ofstream& fout)
{
	fout.open(filename);

	YearNode* currYear = year_list;
	while (currYear)
	{
		fout << currYear->school_year.year_id << endl;
		exportSemesterInYear(currYear->school_year.list_sem, fout);
		currYear = currYear->next;
	}

	fout.close();
}
void exportClass(ClassNode* class_list, ofstream& fout) {
	while (class_list) {
		fout << class_list->my_class.class_id << ",";
		class_list = class_list->next;
	}
};