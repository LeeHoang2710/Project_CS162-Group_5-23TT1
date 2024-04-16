#include "../struct_and_function/function.h"

Semester createSemester(const string &sem_id, const string &start_date, const string &end_date)
{
    return Semester{start_date, end_date, sem_id, nullptr};
}

SemesterNode *createSemesterNode(const Semester &new_sem)
{
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
}

bool importSemester(ClassNode *allClass, SemesterNode *&sem_list, stringstream &is, ifstream &fin)
{
    string start_date, end_date, sem_id;
    getline(is, sem_id, ',');
    getline(is, start_date, ',');
    getline(is, end_date, '\n');

    // Create a new Semester
    Semester new_sem = createSemester(sem_id, start_date, end_date);
    bool success = importCourse(allClass, new_sem.course_list, fin);
    if (!success)
        return false;

    // Append the new Semester to the sem_list
    appendSemesterNode(sem_list, new_sem);
    return true;
}

void exportSemesterInYear(SemesterNode *&sem_list, ofstream &fout)
{
    int count = 0;
    while (sem_list)
    {

        fout << sem_list->sem.semester_id << ","
             << sem_list->sem.start_date << ","
             << sem_list->sem.end_date << endl;
        exportCourse(sem_list->sem.course_list, fout);
        ++count;
        sem_list = sem_list->next;
    }

    if (count < 3)
        fout << "#" << endl;
}

void deleteSemesterList(SemesterNode *&sem_list)
{
    while (sem_list)
    {
        SemesterNode *temp = sem_list;
        deleteCourseList(temp->sem.course_list);
        sem_list = sem_list->next;
        delete temp;
    }
}
