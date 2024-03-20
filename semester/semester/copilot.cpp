#include "../semester.h"

void addCourseListToSemester(SemesterNode* semNode, CourseNode* course_list)
{
	semNode->sem.course_list = course_list;
}