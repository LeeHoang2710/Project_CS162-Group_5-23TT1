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
        head = newclassnode;
    else
    {
        ClassNode *List_Class = head;
        while (List_Class->next)
            List_Class = List_Class->next;
        List_Class->next = newclassnode;
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

ClassNode *searchClassNode(ClassNode *allClass, string class_id)
{
    ClassNode *curr = allClass;
    while (curr)
    {
        if (curr->my_class.class_id == class_id)
            return curr;
        curr = curr->next;
    }

    cout << "Cannot find class " << class_id << endl;
    return nullptr;
}

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

    fin.close();
    return true;
}

ClassSubNode *createClassSubNode(ClassNode *classNode)
{
    return new ClassSubNode{classNode, nullptr};
}

ClassSubNode *findClasses(ClassNode *head, string input)
{
    for (int i = 0; i < input.size(); ++i)
        input[i] = toupper(input[i]);

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
        fout << curr->class_node->my_class.class_id;
        if (curr->next)
            fout << ",";

        curr = curr->next;
    }

    fout << endl;
}

void deleteClassList(ClassNode *&classList)
{
    while (classList)
    {
        ClassNode *temp = classList;
        deleteStudentList(temp->my_class.student_list);
        classList = classList->next;
        delete temp;
    }
}

void deleteClassSubList(ClassSubNode *&classSublist)
{
    while (classSublist)
    {
        ClassSubNode *temp = classSublist;
        classSublist = classSublist->next;
        delete temp;
    }
}

void ExportClassStudents(ofstream &op, string &destination, ClassNode *Curr)
{
    string id = Curr->my_class.class_id;
    string filename = destination + "/" + id + ".csv";
    destination = filename;
    op.open(filename);
    StudentNode *stulist = Curr->my_class.student_list;
    op << "No,Student ID,First Name,Last Name,Gender,Dob,Social ID" << endl;
    while (stulist)
    {
        op << stulist->student.num << ",";
        op << stulist->student.student_id << ",";
        op << stulist->student.first_name << ",";
        op << stulist->student.last_name << ",";
        if (stulist->student.gender == 0)
            op << "Male"
               << ",";
        else
            op << "Female"
               << ",";
        op << stulist->student.dob << ",";
        op << stulist->student.social_id << ",";
        op << endl;
        stulist = stulist->next;
    }
    op.close();
}