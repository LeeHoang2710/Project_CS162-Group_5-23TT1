#include "../year_LeeHoang.h"

Year createYear(string p_year_id)
{
	return Year{ p_year_id, nullptr };
}
YearNode* initYearNode(Year p_school_year)
{
	return new YearNode{ p_school_year, nullptr };
}

void addNewYearNode(YearNode*& head, YearNode* new_year_node)
{
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

YearNode* searchYearNode(YearNode* head, string year_id)
{
	if (!head)
	{
		//cout << "Cannot find the searched year..." << endl;
		return nullptr;
	}
	YearNode* list_year = head;
	while (list_year)
	{
		if (list_year->school_year.year_id == year_id)
			return list_year;
		else
			list_year = list_year->next;
	}
	//cout << "Cannot find the searched year..." << endl;
	return nullptr;
}

void removeNewYearNode(YearNode*& head, Year year)
{
	if (!head)
		return;
	YearNode* list_year = head;
	while (list_year && list_year->next)
	{
		if (list_year->next->school_year.year_id == year.year_id)
		{
			YearNode* temp_year = list_year->next;
			list_year->next = list_year->next->next;
			delete temp_year;
		}
		else
			list_year = list_year->next;
	}
}
