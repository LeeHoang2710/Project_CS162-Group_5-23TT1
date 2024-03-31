#include "./year.h"
#include "./semester.h"

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
