#include "struct_and_library.h"
Class CreateClass(string classid,string headteacher,StudentNode* studenthead)
{
	Class newclass;
	newclass.class_id = classid;
	newclass.class_id = headteacher;
	newclass.student_list = studenthead;
	return newclass;
}
ClassNode* InitializeClassNode(Class newclass) 
{
	ClassNode* newclassnode = new ClassNode();
	newclassnode->my_class = newclass;
	newclassnode->next = nullptr;
	return newclassnode;
}
void AddClassNode(ClassNode* &head,Class newclass)
{
	ClassNode* newclassnode = new ClassNode(); 
	newclassnode = InitializeClassNode(newclass);
	if (!head) 
	{
		head = newclassnode;
	}
	else 
	{
		ClassNode* List_Class = head;
		while (List_Class->next)
		{
			List_Class = List_Class->next;
		}
		List_Class->next = newclassnode;
	}
}
void DeleteClassNode(ClassNode* &head,Class del_class)
{
	if (!head) 
	{
		cout << "Invalid.\n";
		return;
	}
	ClassNode* tmp = nullptr;
	if (head->my_class.class_id == del_class.class_id)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
	else 
	{
		tmp = head;
		while (tmp->next) 
		{
			if (tmp->next->my_class.class_id == del_class.class_id) 
			{
				ClassNode* delnode = tmp->next;
				tmp->next = tmp->next->next;
				delete delnode;
				return;
			}
			else
			{
				tmp = tmp->next;
			}
		}
		cout << "the class that need to remove don't exist.\n";
	}
}
ClassNode* SearchClassNode(ClassNode*& head,Class searchclass) 
{
	if (!head) 
	{
		cout << "the class that need to find don't exist.\n";
		return nullptr;
	}
	else 
	{
		ClassNode* tmp = head;
		while (tmp)
		{
			if (tmp->my_class.class_id == searchclass.class_id)
				return tmp;
			else
				tmp = tmp->next;
		}
		cout << "the class that need to find don't exist.\n";
		return nullptr;
	}
}
void AddStudent(ClassNode* &head,string classid,StudentNode* newstudent)
{
	if (!head)
	{
		cout << "The class you want to join don't exist!\n";
		return;
	}
	ClassNode* tmp = head;
	while (tmp)
		{
		if (tmp->my_class.class_id == classid) 
		{
			StudentNode* Stulist = tmp->my_class.student_list;
			while (Stulist->next)
				Stulist = Stulist->next;
			Stulist->next = newstudent;
			return;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	if (!tmp)
	{
		cout << "The class you want to join don't exist!\n";
	}
}
