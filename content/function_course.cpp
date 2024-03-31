#include "../struct_and_function/function.h"

Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, Session teaching_session)
{
    Course tmp;
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

void deletecourse(CourseNode *CourseHead, string delCourse)
{
    if (CourseHead->course.course_id == delCourse)
    {
        CourseNode *tmp = CourseHead;
        CourseHead = CourseHead->next;
        delete tmp;
    }
    for (CourseNode *tmp = CourseHead; tmp->next != nullptr; tmp = tmp->next)
    {
        if (tmp->next->course.course_id == delCourse)
        {
            CourseNode *del = tmp->next;
            tmp->next = tmp->next->next;
            delete del;
        }
    }
}

void importCourse(CourseNode *&Courselist, istringstream &ss)
{
    while (ss)
    {
        Course cs;
        string line;
        string number;
        getline(ss, cs.course_id, ',');
        if (cs.course_id == "*")
            break;
        getline(ss, cs.course_name, ',');
        getline(ss, cs.teacher_name, ',');
        getline(ss, number, ',');
        cs.num_credit = stoi(number);
        getline(ss, number, ',');
        cs.max_students = stoi(number);
        getline(ss, number, ',');
        cs.teaching_session.day_of_the_week = stoi(number);
        getline(ss, number, '\n');
        cs.teaching_session.session_no = stoi(number);
        appendNewCourseNode(Courselist, cs);
    }
}

void exportCourse(CourseNode *Courselist, ofstream &fout)
{
    for (CourseNode *tmp = Courselist; tmp != NULL; tmp = tmp->next)
    {
        fout << tmp->course.course_id << ",";
        fout << tmp->course.course_name << ",";
        fout << tmp->course.teacher_name << ",";
        fout << tmp->course.num_credit << ",";
        fout << tmp->course.max_students << ",";
        fout << tmp->course.teaching_session.day_of_the_week << ",";
        fout << tmp->course.teaching_session.session_no << endl;
    }
    fout << "*" << endl;
}