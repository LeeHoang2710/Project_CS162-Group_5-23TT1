#include "../semester.h"

int main()
{
    string filename = "database/semester.csv";
    ifstream fin;
    ofstream fout;
    YearNode* year_list = importYearSemester(filename, fin);
    string sem_id = "Semester 3", start_date = "01/01/2000", end_date = "02/01/2000";
    Semester sem = createSemester(sem_id, start_date, end_date);
    SemesterNode* semNode = createSemesterNode(sem);
    addSemesterNode(year_list->school_year.list_sem, semNode);
    removeSemesterNode(year_list, "2023-2024", 3);
    exportYearSemester(year_list, "outputTest.txt", fout);
    deleteYearList(year_list);
    return 0;
}