#include "../struct_and_function/function.h"

Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, int max_students, Session teaching_session, string class_id, ClassNode *class_list)
{
    Course tmp;
    if (max_students != 50)
        tmp.max_students = max_students;

    if (class_id.empty())
        tmp.main_class = nullptr;
    else
        tmp.main_class = searchClassNode(class_list, class_id);

    tmp.course_id = course_id;
    tmp.course_name = course_name;
    tmp.teacher_name = teacher_name;
    tmp.num_credit = num_credit;
    tmp.teaching_session = teaching_session;
    return tmp;
}

CourseNode *initCourseNode(Course new_course)
{
    CourseNode *new_course_node = new CourseNode;
    new_course_node->next = nullptr;
    new_course_node->course = new_course;
    return new_course_node;
}

void appendNewCourseNode(CourseNode *&head, Course cs)
{
    // semester id
    //  year id
    CourseNode *new_course_node = initCourseNode(cs);
    if (!head)
        head = new_course_node;
    else
    {
        CourseNode *list_course = head;
        while (list_course->next)
            list_course = list_course->next;
        list_course->next = new_course_node;
    }
}

bool deleteCourseNode(CourseNode *&CourseHead, string course_id, string year_id, string sem_id)
{
    if (CourseHead->course.course_id == course_id)
    {
        CourseNode *tmp = CourseHead;
        deleteCourseResultsForClass(CourseHead->course.main_class->my_class.student_list, course_id, year_id, sem_id);
        deleteAllExtraStudents(CourseHead->course.extra_stu, course_id, year_id, sem_id);
        CourseHead = CourseHead->next;
        delete tmp;
        return true;
    }

    for (CourseNode *tmp = CourseHead; tmp->next != nullptr; tmp = tmp->next)
    {
        if (tmp->next->course.course_id == course_id)
        {
            CourseNode *del = tmp->next;
            tmp->next = tmp->next->next;
            deleteCourseResultsForClass(del->course.main_class->my_class.student_list, course_id, year_id, sem_id);
            deleteAllExtraStudents(del->course.extra_stu, course_id, year_id, sem_id);
            delete del;
            return true;
        }
    }

    return false;
}

bool importCourse(ClassNode *allClass, CourseNode *&Courselist, ifstream &fin)
{
    string number;
    while (getline(fin, number))
    {
        Course cs;
        if (number == "*")
            break;

        stringstream line(number);
        getline(line, cs.course_id, ',');
        getline(line, cs.course_name, ',');
        getline(line, cs.teacher_name, ',');
        getline(line, number, ',');
        cs.num_credit = stoi(number);
        getline(line, number, ',');
        cs.max_students = stoi(number);
        getline(line, number, ',');
        cs.teaching_session.day_of_the_week = stoi(number);
        getline(line, number, ',');
        cs.teaching_session.session_no = stoi(number);
        getline(line, number, ',');
        cs.main_class = searchClassNode(allClass, number);
        if (!cs.main_class)
        {
            cout << "Cannot find class " << number << endl;
            return false;
        }

        while (getline(line, number, ','))
        {
            StudentNode *stu = searchStudentNode(allClass, number);
            if (!stu)
            {
                cout << "Student " << number << " does not exist." << endl;
                return false;
            }

            appendStudentSubNode(cs.extra_stu, createStudentSubNode(stu));
        }

        appendNewCourseNode(Courselist, cs);
    }

    return true;
}

void exportCourse(CourseNode *&Courselist, ofstream &fout)
{
    while (Courselist)
    {
        fout << Courselist->course.course_id << ","
             << Courselist->course.course_name << ","
             << Courselist->course.teacher_name << ","
             << Courselist->course.num_credit << ","
             << Courselist->course.max_students << ","
             << Courselist->course.teaching_session.day_of_the_week << ","
             << Courselist->course.teaching_session.session_no << ","
             << Courselist->course.main_class->my_class.class_id << ",";
        StudentSubNode *temp = Courselist->course.extra_stu;
        while (temp)
        {
            fout << temp->student_node->student.student_id;
            if (temp->next)
                fout << ",";

            temp = temp->next;
        }

        fout << endl;
        Courselist = Courselist->next;
    }

    fout << "*" << endl;
}

void compareCourse(Course &old, Course &newone)
{
    if (newone.course_id == "")
        newone.course_id = old.course_id;

    if (newone.course_name == "")
        newone.course_name = old.course_name;

    if (newone.teacher_name == "")
        newone.teacher_name = old.teacher_name;

    if (newone.num_credit == 0)
        newone.num_credit = old.num_credit;

    if (newone.max_students == 0)
        newone.max_students = old.max_students;

    if (newone.main_class == nullptr)
        newone.main_class = old.main_class;

    if (newone.teaching_session.day_of_the_week == 0)
        newone.teaching_session.day_of_the_week = old.teaching_session.day_of_the_week;

    if (newone.teaching_session.session_no == 0)
        newone.teaching_session.session_no = old.teaching_session.session_no;
}

void replaceCourse(CourseNode *&curr, Course newOne, string year_id, string sem_id)
{
    if (!curr)
    {
        cout << "Current CourseNode is nullptr." << endl;
        return;
    }

    if (newOne.main_class != curr->course.main_class)
    {
        deleteCourseResultsForClass(curr->course.main_class->my_class.student_list, curr->course.course_id, year_id, sem_id);
        curr->course = newOne;
        addResultsNodeToClass(curr->course.main_class, year_id, sem_id, curr->course.course_id);
    }
    else
    {
        string old_course_id;
        old_course_id = curr->course.course_id;
        curr->course = newOne;
        updateCourseIdForClass(curr->course.main_class, old_course_id, curr->course.course_id, year_id, sem_id);
    }
}

void findCourse(CourseNode **head, CourseNode **search, int &count, string input)
{
    for (int i = 0; i < input.size(); ++i)
        input[i] = toupper(input[i]);

    for (int i = 0; i < count; ++i)
        search[i] = nullptr;

    count = 0;
    for (int i = 0; head[i]; ++i)
    {
        if (head[i]->course.course_id.find(input) != string::npos)
        {
            search[count] = head[i];
            count++;
        }
    }
}

void deleteCourseList(CourseNode *&courseList, string year_id, string sem_id)
{
    while (courseList)
    {
        CourseNode *temp = courseList;
        deleteAllExtraStudents(temp->course.extra_stu, temp->course.course_id, year_id, sem_id);
        courseList = courseList->next;
        delete temp;
    }
}

bool importmanycourses(ifstream &fin, string filename, ClassNode *class_list, CourseNode *&curr, string yr, string sem)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open file " << filename << endl;
        return false;
    }
    string read; // header
    getline(fin, read, '\n');
    string number;
    while (!fin.eof())
    {
        Course cs;
        getline(fin, number, '\n');
        if (number.empty() || number == "#")
            break;
        stringstream line(number);
        getline(line, cs.course_id, ',');
        getline(line, cs.course_name, ',');
        getline(line, cs.teacher_name, ',');
        getline(line, number, ',');
        cs.num_credit = stoi(number);
        getline(line, number, ',');
        cs.max_students = stoi(number);
        getline(line, number, ',');
        cs.teaching_session.day_of_the_week = stoi(number);
        getline(line, number, ',');
        cs.teaching_session.session_no = stoi(number);
        getline(line, number, ',');
        cs.main_class = searchClassNode(class_list, number);
        if (!cs.main_class)
        {
            cout << "Cannot find class " << number << endl;
            fin.close();
            return false;
        }

        while (getline(line, number, ','))
        {
            StudentNode *stu = searchStudentNode(class_list, number);
            if (!stu)
            {
                cout << "Student " << number << " does not exist." << endl;
                fin.close();
                return false;
            }

            appendStudentSubNode(cs.extra_stu, createStudentSubNode(stu));
        }
        appendNewCourseNode(curr, cs);
        addResultsNodeToClass(cs.main_class, yr, sem, cs.course_id);
    }
    fin.close();
    return true;
}

ResultsNode *CurrCourse(StudentNode *studentNode)
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
    currRes = nullptr;
    ResultsNode *temp = studentNode->student.results_list;
    while (temp)
    {
        if (temp->results.year_id == mostcuryear && temp->results.sem_id == mostcursem)
            appendResultsNode(currRes, createResultsNode(temp->results));
        temp = temp->next;
    }
    return currRes;
}
