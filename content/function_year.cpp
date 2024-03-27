#include "../struct_and_function/function.h"

Year createYear(string p_year_id)
{
    Year new_year;
    new_year.year_id = p_year_id;
    return new_year;
}
YearNode *initYearNode(Year p_school_year)
{
    YearNode *new_year_node = new YearNode;
    new_year_node->next = nullptr;
    new_year_node->school_year = p_school_year;
    return new_year_node;
}

void addNewYearNode(YearNode *&head, Year p_year)
{
    YearNode *new_year_node = initYearNode(p_year);
    if (!head)
        head = new_year_node;
    else
    {
        YearNode *list_year = head;
        while (list_year->next)
            list_year = list_year->next;
        list_year->next = new_year_node;
    }
    return;
}

YearNode *searchYearNode(YearNode *head, Year year)
{
    if (!head)
    {
        cout << "Cannot find the searched year..." << endl;
        return nullptr;
    }
    YearNode *list_year = head;
    while (list_year)
    {
        if (list_year->school_year.year_id == year.year_id)
            return list_year;
        else
            list_year = list_year->next;
    }
    cout << "Cannot find the searched year..." << endl;
    return nullptr;
}

void removeNewYearNode(YearNode *&head, Year year)
{
    if (!head)
        return;
    YearNode *list_year = head;
    while (list_year && list_year->next)
    {
        if (list_year->next->school_year.year_id == year.year_id)
        {
            YearNode *temp_year = list_year->next;
            list_year->next = list_year->next->next;
            delete temp_year;
        }
        else
            list_year = list_year->next;
    }
}

void importYear(YearNode *&year_list, string filename, ifstream &fin)
{
    fin.open(filename);

    YearNode *currYear = year_list;
    string year;
    while (getline(fin, year))
    {
        Year new_year = createYear(year);
        addNewYearNode(year_list, new_year);
    }

    fin.close();
}

void exportYear(YearNode *year_list, string filename, ofstream &fout)
{
    fout.open(filename);

    YearNode *currYear = year_list;
    while (currYear)
    {
        fout << currYear->school_year.year_id << endl;
        currYear = currYear->next;
    }

    fout.close();
}
