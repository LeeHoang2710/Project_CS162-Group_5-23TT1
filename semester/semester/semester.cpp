#include "../semester.h"

//Assuming users always input correctly
//Missing menus
//Missing "Enter 0 to go back"

Semester createSemester(string sem_id, string start_date, string end_date, CourseNode* course_list)
{
	Semester sem;
	sem.semester_id = sem_id;
	sem.start_date = start_date;
	sem.end_date = end_date;
	sem.course_list = course_list;
	return sem;
}
SemesterNode* initSemesterNode(Semester new_sem)
{
	SemesterNode* newSemNode = new SemesterNode;
	newSemNode->sem = new_sem;
	return newSemNode;
}
void addSemesterNode(SemesterNode*& sem_list, Semester new_sem)
{
	if (!sem_list)
		sem_list = initSemesterNode(new_sem);
	else
	{
		SemesterNode* curr = sem_list;
		while (curr->next)
			curr = curr->next;
		curr->next = initSemesterNode(new_sem);
	}
}
void removeSemesterNode(SemesterNode*& sem_list, int sem_num)
{
	if (!sem_list)
		cout << "There are no semesters." << endl;
	else
	{
		string sem = "Semester " + sem_num;
		if (sem_list->sem.semester_id == sem)
		{
			SemesterNode* temp = sem_list;
			sem_list = sem_list->next;
			//delete course list,...
			CourseNode* curr = temp->sem.course_list;
			while (curr)
			{
				CourseNode* tempC = curr;
				curr = curr->next;
				delete tempC;
			}
			delete temp;
		}
		else
		{
			SemesterNode* curr = sem_list->next;
			while (curr->next->next && curr->next->sem.semester_id != sem)
				curr = curr->next;
			if (curr->next->sem.semester_id == sem)
			{
				SemesterNode* temp = curr->next;
				curr->next = curr->next->next;
				//delete course list,...
				CourseNode* curr = temp->sem.course_list;
				while (curr)
				{
					CourseNode* tempC = curr;
					curr = curr->next;
					delete tempC;
				}
				delete temp;
			}

		}
	}
}
