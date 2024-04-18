#include "../struct_and_function/function.h"

void StorePassWordStudent(StudentNode *&StuPass, ifstream &ip, string file)
{
    ip.open(file);
    StudentNode *cur = StuPass;
    Student tmp;

    while (getline(ip, tmp.student_id, ',') && getline(ip, tmp.password, '\n'))
    {
        StudentNode *newNode = new StudentNode;
        newNode->student = tmp;
        newNode->next = nullptr;

        if (StuPass == nullptr)
        {
            StuPass = newNode;
            cur = StuPass;
        }
        else
        {
            cur->next = newNode;
            cur = cur->next;
        }
    }

    ip.close();
}

void StorePassWordStaff(StaffNode *&StaffPass, ifstream &ip, string file)
{
    ip.open(file);
    StaffNode *cur = StaffPass;
    Staff tmp;

    while (getline(ip, tmp.username, ',') && getline(ip, tmp.password, '\n'))
    {
        StaffNode *newNode = new StaffNode;
        newNode->staff = tmp;
        newNode->next = nullptr;

        if (StaffPass == nullptr)
        {
            StaffPass = newNode;
            cur = StaffPass;
        }
        else
        {
            cur->next = newNode;
            cur = cur->next;
        }
    }

    ip.close();
}

bool LoginForStudent(ClassNode *StuPass, string &username, string &pass, string &class_id)
{
    if (!StuPass)
        return false;
    ClassNode *login = StuPass;
    for (login; login != nullptr; login = login->next)
    {
        StudentNode *tmp = login->my_class.student_list;
        for (tmp; tmp != nullptr; tmp = tmp->next)
        {
            if (tmp->student.student_id == username && tmp->student.password == pass)
            {
                class_id = login->my_class.class_id;
                return true;
            }
        }
    }

    return false;
}

bool LoginForStaff(StaffNode *StaffPass, string &username, string &pass)
{
    if (!StaffPass)
        return false;

    StaffNode *tmp = StaffPass;
    for (tmp; tmp != nullptr; tmp = tmp->next)
    {
        if (tmp->staff.username == username && tmp->staff.password == pass)
            return true;
    }

    return false;
}

void UpdateStuPassFile(StudentNode *List, ofstream &op)
{
    op.open("../database/Students_Password.csv");
    for (StudentNode *tmp = List; tmp != nullptr; tmp = tmp->next)
    {
        op << tmp->student.student_id << ",";
        op << tmp->student.password;
        if (tmp->next != nullptr)
            op << endl;
    }

    op.close();
}

void UpdateStaffPassFile(StaffNode *List, ofstream &op)
{
    op.open("../database/Staff_Password.csv");
    for (StaffNode *tmp = List; tmp != nullptr; tmp = tmp->next)
    {
        op << tmp->staff.username << ",";
        op << tmp->staff.password;
        if (tmp->next != nullptr)
            op << endl;
    }

    op.close();
}

bool ChangePassStudent(StudentNode *current)
{
    while (1)
    {
        string input_Pass;
        // cout << "Enter your current password: ";
        cin >> input_Pass;
        if (current->student.password == input_Pass)
        {
            // cout << "Enter your new password: ";
            cin >> input_Pass;
            current->student.password = input_Pass;
            // cout << "Password changed successfully " << endl;
            return true;
        }
        else
        {
            // cout << "current password is wrong, please try again" << endl;
            return false;
        }
    }
}

bool ChangePassStaff(StaffNode *current)
{
    while (1)
    {
        string input_Pass;
        // cout << "Enter your current password: ";
        cin >> input_Pass;
        if (current->staff.password == input_Pass)
        {
            // cout << "Enter your new password: ";
            cin >> input_Pass;
            current->staff.password = input_Pass;
            // cout << "Password changed successfully" << endl;
            return true;
        }

        return false;
    }
}

Staff createStaff(string p_staff_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass)
{
    Staff person;
    person.username = p_staff_id;
    person.first_name = p_first;
    person.last_name = p_last;
    person.gender = p_gender;
    person.dob = p_dob;
    person.social_id = p_social_id;
    person.password = p_pass;
    return person;
}

StaffNode *initStaffNode(Staff new_staff)
{
    StaffNode *new_staff_node = new StaffNode;
    new_staff_node->next = nullptr;
    new_staff_node->staff = new_staff;
    return new_staff_node;
}

void addNewStaffNode(StaffNode *&head, Staff new_staff)
{
    StaffNode *new_staff_node = initStaffNode(new_staff);
    if (!head)
        head = new_staff_node;
    else
    {
        StaffNode *list_Staff = head;
        while (list_Staff->next)
            list_Staff = list_Staff->next;
        list_Staff->next = new_staff_node;
    }
}

void importStaff(StaffNode *&Staff_list, ifstream &ip, string filename)
{
    ip.open(filename);
    string number;
    while (getline(ip, number))
    {
        Staff temp;

        stringstream line(number);
        getline(line, temp.username, ',');
        getline(line, temp.first_name, ',');
        getline(line, temp.last_name, ',');
        getline(line, number, ',');
        temp.gender = stoi(number);
        getline(line, temp.dob, ',');
        getline(line, temp.social_id, ',');
        getline(line, temp.password, '\n');

        addNewStaffNode(Staff_list, temp);
    }

    ip.close();
}

StaffNode *searchStaffNode(StaffNode *head, string staff_1_id)
{
    if (!head)
    {
        cout << "Cannot find the searched staff..." << endl;
        return nullptr;
    }

    StaffNode *list_staff = head;
    while (list_staff)
    {
        if (list_staff->staff.username == staff_1_id)
            return list_staff;
        else
            list_staff = list_staff->next;
    }

    cout << "Cannot find the searched staff..." << endl;
    return nullptr;
}

void ExportStaff(StaffNode *&Staff_list, ofstream &op, string filename)
{
    op.open(filename);

    for (StaffNode *tmp = Staff_list; tmp != nullptr; tmp = tmp->next)
    {
        op << tmp->staff.username << ","
           << tmp->staff.first_name << ","
           << tmp->staff.last_name << ","
           << tmp->staff.gender << ","
           << tmp->staff.dob << ","
           << tmp->staff.social_id << ","
           << tmp->staff.password << endl;
    }

    op.close();
}

void deleteStaffList(StaffNode *&staffList)
{
    while (staffList)
    {
        StaffNode *temp = staffList;
        staffList = staffList->next;
        delete temp;
    }
}
