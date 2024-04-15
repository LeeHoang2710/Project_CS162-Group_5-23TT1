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

void addResultsNodeToClass(ClassNode*& classNode, const string& year_id, const string& sem_id, const string& course_id)
{
    if (!classNode)
    {
        cout << "hello world" << endl;
        return;
    }

    StudentNode* currStudent = classNode->my_class.student_list;
    while (currStudent)
    {
        Results newResults = createResults(course_id, sem_id, year_id, 0.0f, 0.0f, 0.0f);
        ResultsNode* newResultsNode = createResultsNode(newResults);
        appendResultsNode(currStudent->student.results_list, newResultsNode);
        currStudent = currStudent->next;
    }
}

ResultsNode* searchResultsNode(ResultsNode* results_list, string course_id, string year_id, string sem_id)
{
    while (results_list && results_list->results.course_id != course_id && results_list->results.sem_id == sem_id && results_list->results.year_id == year_id)
        results_list = results_list->next;

    return results_list;
}

void updateCourseIdForClass(ClassNode*& classNode, string old_course_id, string new_course_id, string year_id, string sem_id)
{
    StudentNode* currStudent = classNode->my_class.student_list;
    while (currStudent)
    {
        ResultsNode* currResultsNode = currStudent->student.results_list;
        searchResultsNode(currResultsNode, old_course_id, year_id, sem_id)->results.course_id = new_course_id;
        currStudent = currStudent->next;
    }
}

bool importResults(ifstream& fin, ClassNode*& ClassList, string filename)
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

        ClassNode* currClass = searchClassNode(ClassList, Line);
        if (!currClass)
            return false;
        else
        {
            StudentNode* tempStu = currClass->my_class.student_list;
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
                tempStu->student.total_gpa = updateTotalGpa(tempStu);
                tempStu = tempStu->next;
            }
        }
    }

    fin.close();
    return true;
}

void Exportallscoretofile(ofstream &fout, string filename, ClassNode* allClass)
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
        StudentNode* Studentlist = allClass->my_class.student_list;
        while (Studentlist)
        {
            fout << Studentlist->student.student_id << ',' << Studentlist->student.first_name << ',';
            fout << Studentlist->student.last_name << endl;
            ResultsNode* courselist = Studentlist->student.results_list;
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