#include "../struct_and_function/function.h"

void Loadcoursescorefromfile(ifstream &fin, StudentNode *&Studentlist)
{
    StudentNode *tmp1 = nullptr;
    string Line;
    while (getline(fin, Line, '\n') && Line != "")
    {
        if (Line != "*")
        {
            StudentNode *tmp = nullptr;
            if (!Studentlist)
            {
                Studentlist = new StudentNode();
                Studentlist->next = nullptr;
                stringstream ss1(Line);
                string s1;
                getline(ss1, s1, ',');
                Studentlist->student.student_id = s1;
                getline(ss1, s1, ',');
                Studentlist->student.first_name = s1;
                getline(ss1, s1, ',');
                Studentlist->student.last_name = s1;
                tmp1 = Studentlist;
                tmp = Studentlist;
            }
            else
            {
                StudentNode *newstudent = new StudentNode();
                newstudent->next = nullptr;
                stringstream ss1(Line);
                string s1;
                getline(ss1, s1, ',');
                newstudent->student.student_id = s1;
                getline(ss1, s1, ',');
                newstudent->student.first_name = s1;
                getline(ss1, s1, ',');
                newstudent->student.last_name = s1;
                tmp1->next = newstudent;
                tmp1 = tmp1->next;
                tmp = newstudent;
            }
            ResultsNode *Resulist = nullptr;
            ResultsNode *tmp2 = nullptr;
            while (getline(fin, Line, '\n'))
            {
                if (Line != "*")
                {
                    if (!Resulist)
                    {
                        Resulist = new ResultsNode();
                        Resulist->next = nullptr;
                        stringstream ss2(Line);
                        string s2;
                        getline(ss2, s2, ',');
                        Resulist->results.course_id = s2;
                        getline(ss2, s2, ',');
                        Resulist->results.year_id = s2;
                        getline(ss2, s2, ',');
                        Resulist->results.sem_id = s2;
                        float fl;
                        getline(ss2, s2, ',');
                        if (s2.size() == 3)
                        {
                            fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
                            Resulist->results.score.process = fl;
                        }
                        else
                            Resulist->results.score.process = (float)(s2[0] - '0');
                        getline(ss2, s2, ',');
                        if (s2.size() == 3)
                        {
                            fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
                            Resulist->results.score.midterm = fl;
                        }
                        else
                            Resulist->results.score.midterm = (float)(s2[0] - '0');
                        getline(ss2, s2, ',');
                        if (s2.size() == 3)
                        {
                            fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
                            Resulist->results.score.final = fl;
                        }
                        else
                            Resulist->results.score.final = (float)(s2[0] - '0');
                        Resulist->results.score.overall = 0.35 * Resulist->results.score.process + 0.25 * Resulist->results.score.midterm + 0.4 * Resulist->results.score.final;
                        tmp2 = Resulist;
                    }
                    else
                    {
                        ResultsNode *newResulist = new ResultsNode();
                        newResulist->next = nullptr;
                        stringstream ss2(Line);
                        string s2;
                        getline(ss2, s2, ',');
                        newResulist->results.course_id = s2;
                        getline(ss2, s2, ',');
                        newResulist->results.year_id = s2;
                        getline(ss2, s2, ',');
                        newResulist->results.sem_id = s2;
                        float fl;
                        getline(ss2, s2, ',');
                        if (s2.size() == 3)
                        {
                            fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
                            newResulist->results.score.process = fl;
                        }
                        else
                            newResulist->results.score.process = (float)(s2[0] - '0');
                        getline(ss2, s2, ',');
                        if (s2.size() == 3)
                        {
                            fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
                            newResulist->results.score.midterm = fl;
                        }
                        else
                            newResulist->results.score.midterm = (float)(s2[0] - '0');
                        getline(ss2, s2, ',');
                        if (s2.size() == 3)
                        {
                            fl = (float)(s2[0] - '0') + (float)(s2[2] - '0') / 10;
                            newResulist->results.score.final = fl;
                        }
                        else
                            newResulist->results.score.final = (float)(s2[0] - '0');
                        newResulist->results.score.overall = 0.35 * newResulist->results.score.process + 0.25 * newResulist->results.score.midterm + 0.4 * newResulist->results.score.final;
                        tmp2->next = newResulist;
                        tmp2 = tmp2->next;
                    }
                }
                else
                    break;
            }
            tmp->student.results_list = Resulist;
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