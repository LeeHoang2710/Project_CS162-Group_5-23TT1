#include "../struct_and_function/function.h"
Class CreateClass(string classid)
{
    Class newclass;
    newclass.class_id = classid;
    newclass.student_list = nullptr;
    return newclass;
}

ClassNode *InitializeClassNode(Class newclass)
{
    ClassNode *newclassnode = new ClassNode();
    newclassnode->my_class = newclass;
    newclassnode->next = nullptr;
    return newclassnode;
}

void AddClassNode(ClassNode *&head, Class newclass)
{
    ClassNode *newclassnode = InitializeClassNode(newclass);
    if (!head)
    {
        head = newclassnode;
    }
    else
    {
        ClassNode *List_Class = head;
        while (List_Class->next)
            List_Class = List_Class->next;
        List_Class->next = newclassnode;
    }
}

void DeleteClassNode(ClassNode *&head, Class del_class)
{
    if (!head)
    {
        cout << "Invalid.\n";
        return;
    }
    ClassNode *tmp = nullptr;
    if (head->my_class.class_id == del_class.class_id)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    else
    {
        tmp = head;
        while (tmp && tmp->next)
        {
            if (tmp->next->my_class.class_id == del_class.class_id)
            {
                ClassNode *delnode = tmp->next;
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

ClassNode *SearchClassNode(ClassNode *&head, string searchclass)
{
    if (!head)
    {
        cout << "the class that need to find don't exist.\n";
        return nullptr;
    }
    else
    {
        ClassNode *tmp = head;
        while (tmp)
        {
            if (tmp->my_class.class_id == searchclass)
                return tmp;
            else
                tmp = tmp->next;
        }
        cout << "the class that need to find don't exist.\n";
        return nullptr;
    }
}

void AddStudent(ClassNode *&head, string classid, StudentNode *newstudent)
{
    if (!head)
    {
        cout << "The class you want to join don't exist!\n";
        return;
    }
    ClassNode *tmp = head;
    while (tmp)
    {
        if (tmp->my_class.class_id == classid)
        {
            StudentNode *Stulist = tmp->my_class.student_list;
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

void ReadClassfromfile(ClassNode *&Listclass, string file_name, ifstream &fin)
{
    fin.open(file_name);
    if (!fin.is_open())
        cout << "Can not open file" << endl;
    else
    {
        string line;
        while (getline(fin, line))
        {
            Class new_class = CreateClass(line);
            AddClassNode(Listclass, new_class);
            ClassNode *temp = Listclass;
            while (temp->next)
                temp = temp->next;
            readStudentFromFile(fin, temp->my_class.student_list);
        }
    }

    fin.close();
}

void ExportClassTFile(ClassNode *&Listclass, string file_name, ofstream &fout)
{
    fout.open(file_name);
    if (!fout.is_open())
        cout << "Can not open file" << endl;
    else
    {
        while (Listclass)
        {
            fout << Listclass->my_class.class_id << endl;
            exportStudentToFile(fout, Listclass->my_class.student_list);
            Listclass = Listclass->next;
        }
    }
}