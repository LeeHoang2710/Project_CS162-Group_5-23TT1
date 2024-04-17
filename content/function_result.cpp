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

float UpdateCurGpa(StudentNode *studentNode)
{
    ResultsNode *currRes = studentNode->student.results_list;
    string mostcuryear = "0000-0000", mostcursem = "Semester 0";
    while (currRes)
    {
        if (currRes->results.year_id > mostcuryear)
        {
            mostcuryear = currRes->results.year_id;
            mostcursem = currRes->results.sem_id;
        }
        else if (currRes->results.year_id == mostcuryear)
        {
            if (currRes->results.sem_id > mostcursem)
                mostcursem = currRes->results.sem_id;
        }
        currRes = currRes->next;
    }
    currRes = studentNode->student.results_list;
    float total = 0.0f;
    int count = 0;
    while (currRes)
    {
        if (currRes->results.year_id == mostcuryear && currRes->results.sem_id == mostcursem)
        {
            total += currRes->results.score.overall;
            count++;
        }
        currRes = currRes->next;
    }
    return total / count;
}

void updateCourseOverall(Score &score)
{
    score.overall = 0.35 * score.process + 0.25 * score.midterm + 0.4 * score.final;
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
    updateCourseOverall(newResults.score);
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

void addResultsNodeToClass(ClassNode *&classNode, const string &year_id, const string &sem_id, const string &course_id)
{
    if (!classNode)
    {
        cout << "ClassNode is nullptr." << endl;
        return;
    }

    StudentNode *currStudent = classNode->my_class.student_list;
    while (currStudent)
    {
        Results newResults = createResults(course_id, sem_id, year_id, 0.0f, 0.0f, 0.0f);
        ResultsNode *newResultsNode = createResultsNode(newResults);
        appendResultsNode(currStudent->student.results_list, newResultsNode);
        currStudent = currStudent->next;
    }
}

ResultsNode *searchResultsNode(ResultsNode *results_list, string course_id, string year_id, string sem_id)
{
    while (results_list && results_list->results.course_id != course_id && results_list->results.sem_id == sem_id && results_list->results.year_id == year_id)
        results_list = results_list->next;

    return results_list;
}

void updateCourseIdForClass(ClassNode *&classNode, string old_course_id, string new_course_id, string year_id, string sem_id)
{
    StudentNode *currStudent = classNode->my_class.student_list;
    while (currStudent)
    {
        ResultsNode *currResultsNode = currStudent->student.results_list;
        searchResultsNode(currResultsNode, old_course_id, year_id, sem_id)->results.course_id = new_course_id;
        currStudent = currStudent->next;
    }
}

bool importResults(ifstream &fin, ClassNode *&ClassList, string filename)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open " << filename << endl;
        return false;
    }

    string Line;
    while (getline(fin, Line, '\n'))
    {
        if (Line.empty())
            break;

        ClassNode *currClass = searchClassNode(ClassList, Line);
        if (!currClass)
            return false;
        else
        {
            StudentNode *tempStu = currClass->my_class.student_list;
            while (getline(fin, Line, '\n') && tempStu)
            {
                while (getline(fin, Line, '\n'))
                {
                    if (Line == "*")
                        break;
                    else
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
                }
                tempStu->student.cur_gpa = UpdateCurGpa(tempStu);
                tempStu->student.total_gpa = updateTotalGpa(tempStu);
                tempStu = tempStu->next;
            }
        }
    }

    fin.close();
    return true;
}

void Exportallscoretofile(ofstream &fout, string filename, ClassNode *allClass)
{
    fout.open(filename);
    if (!fout.is_open())
    {
        cout << "Cannot open " << filename << endl;
        return;
    }

    while (allClass)
    {
        fout << allClass->my_class.class_id << endl;
        StudentNode *Studentlist = allClass->my_class.student_list;
        while (Studentlist)
        {
            fout << Studentlist->student.student_id << ',' << Studentlist->student.first_name << ',';
            fout << Studentlist->student.last_name << endl;
            ResultsNode *courselist = Studentlist->student.results_list;
            while (courselist)
            {
                fout << courselist->results.course_id << ',' << courselist->results.year_id << ',';
                fout << courselist->results.sem_id << ',' << courselist->results.score.process << ',';
                fout << courselist->results.score.midterm << ',' << courselist->results.score.final << ',';
                fout << fixed << setprecision(1) << courselist->results.score.overall << endl;
                courselist = courselist->next;
            }

            fout << "*" << endl;
            Studentlist = Studentlist->next;
        }

        fout << "#" << endl;
        allClass = allClass->next;
    }

    fout.close();
}

bool UpdateResults(ifstream &fin, string filename, string yr, string sem, CourseNode *&curr)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "can not open results file to course" << endl;
        return false;
    }
    string read;
    getline(fin, read, '\n');
    while (!fin.eof())
    {
        int i = 1;
        string no, stu_find, fullname;
        getline(fin, no, ',');
        if (no == "")
        {
            fin.close();
            return true;
        }
        getline(fin, stu_find, ',');
        getline(fin, fullname, ',');
        StudentNode *stuTemp = searchStudentNodeInOneClass(curr->course.main_class->my_class.student_list, stu_find);
        if (!stuTemp)
        {
            stuTemp = searchStudentSubNode(curr->course.extra_stu, stu_find)->student_node;
            if (!stuTemp)
            {
                cout << "students in files and course are not matched, maybe this student is not in this course yet" << endl;
                fin.close();
                return false;
            }
        }
        else
            cout << i++;
        ResultsNode *change = searchResultsNode(stuTemp->student.results_list, curr->course.course_id, yr, sem);
        string p, m, f;
        getline(fin, p, ',');
        getline(fin, m, ',');
        getline(fin, f, ',');
        change->results.score.process = stof(p);
        change->results.score.midterm = stof(m);
        change->results.score.final = stof(f);
        change->results.score.overall = 0.35 * stof(p) + 0.25 * stof(m) + 0.4 * stof(f);
        stuTemp->student.total_gpa = UpdateCurGpa(stuTemp);
        stuTemp->student.total_gpa = updateTotalGpa(stuTemp);
        getline(fin, read, '\n');
    }

    fin.close();
    return true;
}

bool deleteResultsNode(ResultsNode *&resultsList, string course_id, string year_id, string sem_id)
{
    ResultsNode *temp = searchResultsNode(resultsList, course_id, year_id, sem_id);
    if (!temp)
    {
        cout << "ResultsNode for course " << course_id << " does not exist." << endl;
        return false;
    }

    if (temp == resultsList)
    {
        resultsList = resultsList->next;
        delete temp;
        return true;
    }

    ResultsNode *prev = resultsList;
    while (prev->next != temp)
        prev = prev->next;

    prev->next = temp->next;
    delete temp;
    return true;
}

void deleteCourseResultsForClass(StudentNode *&studentList, string course_id, string year_id, string sem_id)
{
    StudentNode *currStu = studentList;
    while (currStu)
    {
        bool success = deleteResultsNode(currStu->student.results_list, course_id, year_id, sem_id);
        if (!success)
            cout << "ResultsNode for " << course_id << " does not exist for " << currStu->student.student_id << endl;

        currStu = currStu->next;
    }
}

void deleteResultsList(ResultsNode *&resultsList)
{
    while (resultsList)
    {
        ResultsNode *temp = resultsList;
        resultsList = resultsList->next;
        delete temp;
    }
}

void ExportStudentTofile(ofstream &op, string &destination, CourseNode *curr, string year_id, string sem_id)
{
    string filename = destination + "/" + curr->course.course_id + "_" + year_id + "_" + sem_id + ".csv";
    cout << filename;
    op.open(filename);
    cout << "oke";
    StudentNode *tempstu = curr->course.main_class->my_class.student_list;
    op << "No,Student ID,Full name,Process Mark, Midterm Mark,Final Mark, Total Mark" << endl;
    while (tempstu)
    {
        op << tempstu->student.num << ","
           << tempstu->student.student_id << ","
           << tempstu->student.last_name << " "
           << tempstu->student.first_name << ",";
        ResultsNode *findcurr = searchResultsNode(tempstu->student.results_list, curr->course.course_id, year_id, sem_id);
        op << findcurr->results.score.process << ","
           << findcurr->results.score.midterm << ","
           << findcurr->results.score.final << ","
           << findcurr->results.score.overall << endl;
        tempstu = tempstu->next;
    }

    StudentSubNode *tempextra = curr->course.extra_stu;
    while (tempextra)
    {
        op << tempextra->student_node->student.num << ","
           << tempextra->student_node->student.student_id << ","
           << tempextra->student_node->student.last_name << " "
           << tempextra->student_node->student.first_name << ",";
        ResultsNode *findcurr = searchResultsNode(tempextra->student_node->student.results_list, curr->course.course_id, year_id, sem_id);
        op << findcurr->results.score.process << ","
           << findcurr->results.score.midterm << ","
           << findcurr->results.score.final << ","
           << findcurr->results.score.overall << endl;
        tempextra = tempextra->next;
    }
    destination = filename;
    op.close();
}

void ExportAllResultsToFile(ofstream &op, string &destination, StudentNode *Curr)
{
    string name = Curr->student.last_name + " " + Curr->student.first_name;
    string id = Curr->student.student_id;
    string filename = destination + "/" + id + "_scoreboard.csv";
    op.open(filename);
    op << "Full Name:"
       << "," << name << endl;
    op << "Student ID:"
       << "," << id << endl;
    op << "Total Gpa "
       << "," << Curr->student.total_gpa << endl;
    op << "Course,Semester,Year,Process Mark,Midterm Mark,Final Mark,Total Mark" << endl;
    ResultsNode *restemp = Curr->student.results_list;
    while (restemp)
    {
        op << restemp->results.course_id << ","
           << restemp->results.sem_id << ","
           << restemp->results.year_id << ",";
        op << restemp->results.score.process << ","
           << restemp->results.score.midterm << ","
           << restemp->results.score.final << ","
           << restemp->results.score.overall << endl;
        restemp = restemp->next;
    }

    op.close();
}
