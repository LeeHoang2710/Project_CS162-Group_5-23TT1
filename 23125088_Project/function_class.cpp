#include "struct_and_library.h"
#include "function.h"
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
void ReadClassfromfile(ClassNode* Listclass[],ifstream &fin)
{
	for (int j = 0; j < 10; ++j)
	{
		Listclass[j] = 0;
	}
	int i = 0;
	string line;
	while (getline(fin, line, '\n'))
	{
		stringstream ss(line);
		string newclass;
		while (getline(ss, newclass, ',')) 
		{
			ClassNode* tmp = 0;
			if (!Listclass[i]) 
			{
				Listclass[i] = new ClassNode();
				Listclass[i]->my_class.class_id = newclass;
				Listclass[i]->next = 0;
			}
			else {
				tmp = Listclass[i];
				while (tmp->next)
					tmp = tmp->next;
				ClassNode* newclassnode = new ClassNode();
				newclassnode->my_class.class_id = newclass;
				newclassnode->next = 0;
				tmp->next = newclassnode;
			}
		}
		i++;
	}
}
void ReadStudentfromfile(StudentNode*& ListStu, ifstream& fin)
{
	string Line;
	while (getline(fin, Line, '\n'))
	{
		stringstream ss(Line);
		string word;
		if (!ListStu) 
		{
			ListStu = new StudentNode();
			getline(ss, word, ',');
			int oder = 0;
			for (int i = word.length() - 1; i >= 0; --i) 
			{
				oder = oder * 10 + word[i] - '0';
			}
			ListStu->student.num = oder;
			getline(ss, word, ',');
			ListStu->student.student_id = word;
			getline(ss, word, ',');
			ListStu->student.first_name = word;
			string word1, word2;
			getline(ss, word1, ',');
			getline(ss, word2, ',');
			if (word2 != "1" && word2 != "0") 
			{
				word = word1 + word2;
			}
			else
				word = word1;
			ListStu->student.last_name = word;
			getline(ss, word, ',');
			if (word == "0")
			{
				ListStu->student.gender = 0;
			}
			else
				ListStu->student.gender = 1;
			getline(ss, word, ',');
			ListStu->student.dob = word;
			getline(ss, word, ',');
			ListStu->student.social_id = word;
			getline(ss, word, ',');
			ListStu->student.student_class = word;
			ListStu->next = 0;
		}
		else 
		{
			StudentNode* tmp = ListStu;
			while (tmp->next) 
			{
				tmp = tmp->next;
			}
			StudentNode* newnode = new StudentNode();
			getline(ss, word, ',');
			int oder = 0;
			for (int i = word.length() - 1; i >= 0; --i) 
			{
				oder = oder * 10 + word[i] - '0';
			}
			newnode->student.num = oder;
			getline(ss, word, ',');
			newnode->student.student_id = word;
			getline(ss, word, ',');
			newnode->student.first_name = word;
			string word1, word2;
			getline(ss, word1, ',');
			getline(ss, word2, ',');
			if (word2 != "1" && word2 != "0") 
                        {
	                    word = word1 + word2;
	                    newnode->student.last_name = word;
	                    getline(ss,word,',');
	                    if (word == "1")
		                newnode->student.gender = 1;
	                    else
		                newnode->student.gender = 0;
	
                         }
                          else
                          {
	                      newnode->student.last_name = word1;
	                      if (word2 == "1")
		                  newnode->student.gender = 1;
	                      else
		                  newnode->student.gender = 0;
                          }						
			 getline(ss, word, ',');
			 newnode->student.dob = word;
			 getline(ss, word, ',');
			 newnode->student.social_id = word;
			 getline(ss, word, ',');
			 newnode->student.student_class = word;
			 newnode->next = 0;
			 tmp->next = newnode;
		}
	}
}
