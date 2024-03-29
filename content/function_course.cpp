#include "../struct_and_function/function.h"

Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, Session teaching_session)
{
    Course tmp;
    tmp.course_id = course_id;
    tmp.course_name = course_name;
    tmp.teacher_name = teacher_name;
    tmp.num_credit = num_credit;
    tmp.teaching_session[0] = teaching_session;
    return tmp;
}

CourseNode *initCourseNode(Course new_course, StudentNode *liststu)
{
    CourseNode *new_course_node = new CourseNode;
    new_course_node->next = NULL;
    new_course_node->course = new_course;
    new_course_node->student_list = liststu;
    return new_course_node;
}

void addNewCourseNode(CourseNode *&head, Course cs, StudentNode *liststu)
{
    // semester id
    //  year id
    CourseNode *new_course_node = initCourseNode(cs, liststu);
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