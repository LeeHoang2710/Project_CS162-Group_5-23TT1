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

void AddClassNode(ClassNode *&head, ClassNode *newclassnode)
{
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

// void DeleteClassNode(ClassNode *&head, Class del_class)
// {
//     if (!head)
//     {
//         cout << "Invalid.\n";
//         return;
//     }
//     if (head->my_class.class_id == del_class.class_id && head->my_class.academic_id == del_class.academic_id)
//     {
//         ClassNode *tmp = head;
//         head = head->next;
//         delete tmp;
//         return;
//     }
//     ClassNode *tmp = head;
//     while (tmp && tmp->next)
//     {
//         if (tmp->next->my_class.class_id == del_class.class_id && tmp->next->my_class.academic_id == del_class.academic_id)
//         {
//             ClassNode *delnode = tmp->next;
//             tmp->next = tmp->next->next;
//             delete delnode;
//             return;
//         }
//         else
//         {
//             tmp = tmp->next;
//         }
//     }
//     cout << "the class that need to remove don't exist.\n";
// }

// ClassNode *SearchClassNode(ClassNode *&head, string searchclassid1, string searchclassid2)
// {
//     if (!head)
//     {
//         cout << "the class that need to find don't exist.\n";
//         return nullptr;
//     }
//     if (head->my_class.class_id == searchclassid1 && head->my_class.academic_id == searchclassid2)
//     {
//         return head;
//     }
//     else
//     {
//         ClassNode *tmp = head->next;
//         while (tmp)
//         {
//             if (tmp->my_class.class_id == searchclassid1 && tmp->my_class.academic_id == searchclassid2)
//                 return tmp;
//             else
//                 tmp = tmp->next;
//         }
//         cout << "the class that need to find don't exist.\n";
//         return nullptr;
//     }
// }

// void AddStudent(ClassNode *&head, string classid, string academicid, StudentNode *newstudent)
// {
//     if (!head)
//     {
//         cout << "The class you want to join don't exist!\n";
//         return;
//     }
//     ClassNode *tmp = head;
//     while (tmp)
//     {
//         if (tmp->my_class.class_id == classid && tmp->my_class.academic_id == academicid)
//         {
//             StudentNode *Stulist = tmp->my_class.student_list;
//             while (Stulist->next)
//                 Stulist = Stulist->next;
//             Stulist->next = newstudent;
//             return;
//         }
//         else
//         {
//             tmp = tmp->next;
//         }
//     }
//     if (!tmp)
//     {
//         cout << "The class you want to join don't exist!\n";
//     }
// }

void ReadClassfromfile(ClassNode *&Listclass, string file_name, ifstream &fin)
{
    fin.open(file_name);
    if (!fin.is_open())
        cout << "Can not open file" << endl;
    else
    {
        string line;
        while (getline(fin, line, '\n'))
        {
            Class new_class = CreateClass(line);
            readStudentFromFile(fin, new_class.student_list);
            AddClassNode(Listclass, InitializeClassNode(new_class));
        }
    }

    fin.close();
}

void ExportClassTFile(ClassNode *Listclass, string file_name, ofstream &fout)
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
    fout.close();
}

ClassSubNode *findClasses(ClassNode *head, string input)
{
    ClassSubNode *sort = nullptr;
    ClassNode *curr = head;
    while (curr)
    {
        if (curr->my_class.class_id.find(input) != string::npos)
            appendClassSubNode(sort, createClassSubNode(curr));
        curr = curr->next;
    }
    return sort;
}

// void importClass(ClassNode *&classes, stringstream &ss, ifstream &fin)
//{
//     string oneclass;
//     while (getline(ss, oneclass, ','))
//     {
//         Class newclass = CreateClass(oneclass);
//         AddClassNode(classes, InitializeClassNode(newclass));
//     }
// };

// void exportClass(ClassNode *class_list, ofstream &fout)
//{
//     if (!class_list)
//         return;
//
//     while (class_list)
//     {
//         fout << class_list->my_class.class_id << ",";
//         class_list = class_list->next;
//     }
//     fout << endl;
// };

bool importNewClassesFromStaff(YearNode *currYearNode, ClassNode *&Listclass, string file_name, ifstream &fin)
{
    fin.open(file_name);
    if (!fin.is_open())
    {
        cout << "Can not open file" << endl;
        return false;
    }

    string oneclass;
    while (getline(fin, oneclass, ','))
    {
        if (oneclass.empty() || fin.eof()) // Check if the line is empty or we've reached the end of the file
            break;

        Class newclass = CreateClass(oneclass);
        // readStudentFromFile(fin, newclass.student_list);
        ClassNode *newClassNode = InitializeClassNode(newclass);
        AddClassNode(Listclass, newClassNode);
        appendClassSubNode(currYearNode->school_year.classSublist, createClassSubNode(newClassNode));
    }

    // ClassNode* tmp = Listclass;
    //
    // while (tmp)
    //{
    //     cout << tmp->my_class.class_id << ",";
    //     tmp = tmp->next;
    // }

    fin.close();
    return true;
}

ClassSubNode *createClassSubNode(ClassNode *classNode)
{
    return new ClassSubNode{classNode, nullptr};
}

void appendClassSubNode(ClassSubNode *&classSublist, ClassSubNode *classSubNode)
{
    if (!classSublist)
    {
        classSublist = classSubNode;
        return;
    }

    ClassSubNode *curr = classSublist;
    while (curr->next)
        curr = curr->next;
    curr->next = classSubNode;
}

ClassNode *searchClassNode(ClassNode *allClass, string class_id)
{
    ClassNode *curr = allClass;
    while (curr)
    {
        if (curr->my_class.class_id == class_id)
            return curr;
        curr = curr->next;
    }

    return nullptr;
}

bool importClassSubNode(ClassNode *allClass, Year &year, stringstream &ss)
{
    string class_id;
    while (getline(ss, class_id, ','))
    {
        ClassNode *classNode = searchClassNode(allClass, class_id);
        if (!classNode)
        {
            cout << "Class " << class_id << " not found" << endl;
            return false;
        }

        ClassSubNode *classSubNode = createClassSubNode(classNode);
        appendClassSubNode(year.classSublist, classSubNode);
    }

    return true;
}

void exportClassSubNode(ClassSubNode *classSublist, ofstream &fout)
{
    if (!classSublist)
		return;

    ClassSubNode *curr = classSublist;
    while (curr)
    {
        fout << curr->class_node->my_class.class_id << ",";
        curr = curr->next;
    }
    fout << endl;
}