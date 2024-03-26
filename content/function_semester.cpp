#include "../struct_and_function/function.h"

Semester createSemester(const string &sem_id, const string &start_date, const string &end_date)
{
    // In this order: semester_id, start_date, end_date, course_list
    return Semester{sem_id, start_date, end_date, nullptr};
}

SemesterNode *createSemesterNode(const Semester &new_sem)
{
    // In this order: sem, next
    return new SemesterNode{new_sem, nullptr};
}

void appendSemesterNode(SemesterNode *&sem_list, SemesterNode *new_sem_node)
{
    if (!sem_list)
        sem_list = new_sem_node;
    else
    {
        SemesterNode *curr = sem_list;
        while (curr->next)
            curr = curr->next;

        curr->next = new_sem_node;
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