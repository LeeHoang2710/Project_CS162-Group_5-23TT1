#include "../include/function.h"

Year createYear(string p_year_id, ClassSubNode *classSublist)
{
    Year new_year;
    new_year.year_id = p_year_id;
    new_year.classSublist = classSublist;
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
}

YearNode *searchYearNode(YearNode *head, string year)
{
    if (!head)
    {
        cout << "Cannot find the searched year..." << endl;
        return nullptr;
    }

    YearNode *list_year = head;
    while (list_year)
    {
        if (list_year->school_year.year_id == year)
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

bool importYear(YearNode *&year_list, ClassNode *allClass, string filename, ifstream &fin)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(fin, line))
    {
        Year new_year = createYear(line, nullptr);
        getline(fin, line, '\n');
        stringstream classes(line);
        if (line == "#")
        {
            addNewYearNode(year_list, new_year);
            continue;
        }

        bool success = importClassSubNode(allClass, new_year, classes);
        if (!success)
            return false;

        for (int i = 0; i < 3; ++i)
        {
            if (fin.eof())
                break;

            getline(fin, line, '\n');
            if (line == "#")
                break;

            stringstream ss(line);
            bool success = importSemester(allClass, new_year.list_sem, ss, fin);
            if (!success)
                return false;
        }

        addNewYearNode(year_list, new_year);
    }

    fin.close();
    return true;
}

bool exportYear(YearNode *&year_list, string filename, ofstream &fout)
{
    fout.open(filename);
    if (!fout.is_open())
    {
        cout << "Cannot open file " << filename << endl;
        return false;
    }

    YearNode *currYear = year_list;
    while (currYear)
    {
        fout << currYear->school_year.year_id << endl;
        exportClassSubNode(currYear->school_year.classSublist, fout);
        exportSemesterInYear(currYear->school_year.list_sem, fout);
        currYear = currYear->next;
    }

    fout.close();
    return true;
}

void deleteYearList(YearNode *&year_list)
{
    while (year_list)
    {
        YearNode *temp = year_list;
        deleteClassSubList(temp->school_year.classSublist);
        deleteSemesterList(temp->school_year.list_sem, year_list->school_year.year_id);
        year_list = year_list->next;
        delete temp;
    }
}
