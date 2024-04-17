#include "../struct_and_function/function.h"

Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, int max_students, Session teaching_session, string class_id, ClassNode* class_list)
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
    new_course_node->next = NULL;
    new_course_node->course = new_course;
    return new_course_node;
}

// void addNewCourseNode(CourseNode *&head, Course cs, StudentNode *liststu)
// {
//     // semester id
//     //  year id
//     // CourseNode *new_course_node = initCourseNode(cs, liststu);
//     if (!head)
//         head = new_course_node;
//     else
//     {
//         CourseNode *list_course = head;
//         while (list_course->next)
//             list_course = list_course->next;
//         list_course->next = new_course_node;
//     }
// }
// cái này là do chưa có student node nên phải tạo hàm test thôi

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

bool importCourse(ClassNode* allClass, CourseNode*& Courselist, ifstream& fin)
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

        appendNewCourseNode(Courselist, cs);
    }

    return true;
}

void exportCourse(CourseNode *&Courselist, ofstream &fout)
{
    while (Courselist)
    {
        fout << Courselist->course.course_id << ",";
        fout << Courselist->course.course_name << ",";
        fout << Courselist->course.teacher_name << ",";
        fout << Courselist->course.num_credit << ",";
        fout << Courselist->course.max_students << ",";
        fout << Courselist->course.teaching_session.day_of_the_week << ",";
        fout << Courselist->course.teaching_session.session_no << ",";
        fout << Courselist->course.main_class->my_class.class_id << endl;
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

CourseNode *findCourse(CourseNode *head, string input)
{
    CourseNode *sort = nullptr;
    CourseNode *curr = head;
    while (curr)
    {
        if (curr->course.course_id.find(input) != string::npos)
            appendNewCourseNode(sort, curr->course);

        curr = curr->next;
    }

    return sort;
}

void deleteCourseList(CourseNode*& courseList)
{
    while (courseList)
    {
		CourseNode *temp = courseList;
        //deleteExtraStudents
		courseList = courseList->next;
		delete temp;
	}
}
