#include "../struct_and_function/function.h"

Semester createSemester(const string &sem_id, const string &start_date, const string &end_date)
{
    // In this order: semester_id, start_date, end_date, course_list
    return Semester{start_date, end_date, sem_id, nullptr};
}

SemesterNode *createSemesterNode(const Semester &new_sem)
{
    // In this order: sem, next
    return new SemesterNode{new_sem, nullptr};
}

void appendSemesterNode(SemesterNode *&sem_list, Semester new_sem)
{
    SemesterNode *new_sem_node = createSemesterNode(new_sem);
    if (!sem_list)
        sem_list = new_sem_node;
    else
    {
        SemesterNode *curr = sem_list;
        while (curr->next)
            curr = curr->next;
        curr->next = new_sem_node;
    }
    return;
}
void importSemester(SemesterNode *&sem_list, istringstream &is)
{
    string tempSem;
    getline(is, tempSem, ',');
    string start_date, end_date;
    getline(is, start_date, ',');
    getline(is, end_date, '\n');

    // Create a new SemesterNode
    SemesterNode *new_node = new SemesterNode;
    new_node->sem.semester_id = tempSem;
    new_node->sem.start_date = start_date;
    new_node->sem.end_date = end_date;
    new_node->next = nullptr;

    // Add the new node to the sem_list
    if (sem_list == nullptr)
        sem_list = new_node;
    else
    {
        SemesterNode *curr = sem_list;
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

void exportSemesterInYear(SemesterNode *sem_list, ofstream &fout)
{
    while (sem_list)
    {
        fout << sem_list->sem.semester_id << ","
             << sem_list->sem.start_date << ","
             << sem_list->sem.end_date << endl;
        sem_list = sem_list->next;
    }
}

void deleteYearList(YearNode *&year_list)
{
    while (year_list)
    {
        YearNode *temp = year_list;
        year_list = year_list->next;
        deleteSemesterList(temp->school_year.list_sem);
        delete temp;
    }
}

void deleteSemesterList(SemesterNode *&sem_list)
{
    while (sem_list)
    {
        SemesterNode *temp = sem_list;
        sem_list = sem_list->next;
        // deleteCourseList function, and more...
        // deleteCourseList(temp->sem.course_list);...
        delete temp;
    }
}