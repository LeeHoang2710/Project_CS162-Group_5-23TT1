#include "../struct_and_function/function.h"

float updateTotalGpa(StudentNode *studentNode)
{
    ResultsNode *currResultsNode = studentNode->student.results_list;
    float total = 0.0f;
    unsigned short count = 0;

    while (currResultsNode)
    {
        total += currResultsNode->results.score.overall;
        ++count;
        currResultsNode = currResultsNode->next;
    }

    return total / count;
}

Results createResults(const string &course_id, const string &sem_id, const string &year_id, float process, float midterm, float final)
{
    Results newResults;
    newResults.course_id = course_id;
    newResults.sem_id = sem_id;
    newResults.year_id = year_id;
    newResults.score.process = process;
    newResults.score.midterm = midterm;
    newResults.score.final = final;
    newResults.score.overall = 0.35 * process + 0.25 * midterm + 0.4 * final;
    return newResults;
}

ResultsNode *createResultsNode(const Results &results)
{
    return new ResultsNode{results};
}

void appendResultsNode(ResultsNode *&results_list, ResultsNode *resultsNode)
{
    if (!results_list)
        results_list = resultsNode;
    else
    {
        ResultsNode *curr = results_list;
        while (curr->next)
            curr = curr->next;

        curr->next = resultsNode;
    }
}

void Loadcoursescorefromfile(ifstream &fin, StudentNode *&Studentlist, ClassNode *MainClass)
{
    StudentNode *tempStu = Studentlist;
    string Line;
    getline(fin, Line, '\n');
    if (MainClass->my_class.class_id != Line)
    {
        cout << "Error: Class ID does not match" << endl;
        return;
    }
    else
    {
        while (tempStu && getline(fin, Line, '\n') && Line != "")
        {
            if (Line != "*")
            {
                if (tempStu)
                {
                    stringstream ss1(Line);
                    string s1;
                    getline(ss1, s1, ',');
                    tempStu->student.student_id = s1;
                    getline(ss1, s1, ',');
                    tempStu->student.first_name = s1;
                    getline(ss1, s1, ',');
                    tempStu->student.last_name = s1;
                }

                while (getline(fin, Line, '\n'))
                {
                    if (Line != "*")
                    {
                        stringstream ss2(Line);
                        string course, year, sem, p, m, f;
                        getline(ss2, course, ',');
                        getline(ss2, year, ',');
                        getline(ss2, sem, ',');
                        getline(ss2, p, ',');
                        getline(ss2, m, ',');
                        getline(ss2, f, ',');
                        Results currResults = createResults(course, sem, year, stof(p), stof(m), stof(f));
                        appendResultsNode(tempStu->student.results_list, createResultsNode(currResults));
                    }
                    else
                        break;
                }

                tempStu->student.total_gpa = updateTotalGpa(tempStu);
            }

            tempStu = tempStu->next;
        }
    }

    fin.close();
}

void Exportallscoretofile(ofstream &fout, StudentNode *&Studentlist)
{
    fout.open("../database/result.csv");
    while (Studentlist)
    {
        fout << Studentlist->student.student_id << ',' << Studentlist->student.first_name << ',';
        fout << Studentlist->student.last_name << "\n";
        ResultsNode *courselist = Studentlist->student.results_list;
        while (courselist)
        {
            fout << courselist->results.course_id << ',' << courselist->results.year_id << ',';
            fout << courselist->results.sem_id << ',' << courselist->results.score.process << ',';
            fout << courselist->results.score.midterm << ',' << courselist->results.score.final << ',';
            fout << fixed << setprecision(1) << courselist->results.score.overall << "\n";
            courselist = courselist->next;
        }
        fout << "*" << endl;
        Studentlist = Studentlist->next;
    }
    fout.close();
}