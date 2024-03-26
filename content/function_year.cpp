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

void importYearSemester(YearNode *&year_list, string filename, ifstream &fin)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open " << filename << " to import school year and semester information." << endl;
        return;
    }

    YearNode *currYear = year_list;
    SemesterNode *currSem = nullptr;
    string line;
    while (getline(fin, line))
    {
        istringstream ss(line);
        string year_id, sem_id, start_date, end_date;
        getline(ss, year_id, ',');
        getline(ss, sem_id, ',');
        getline(ss, start_date, ',');
        getline(ss, end_date, ',');
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

        Semester semester = createSemester(sem_id, start_date, end_date);
        SemesterNode *semNode = createSemesterNode(semester);
        appendSemesterNode(currYear->school_year.list_sem, semNode);
    }

    fin.close();
}

void exportYearSemester(YearNode *year_list, string filename, ofstream &fout)
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
        SemesterNode *currSem = year_list->school_year.list_sem;
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
