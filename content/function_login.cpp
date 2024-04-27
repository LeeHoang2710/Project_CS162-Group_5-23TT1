#include "../include/function.h"

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
    string line;
    while (getline(ip, line))
    {
        string username, first, last, gender, dob, social, pass;
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, first, ',');
        getline(ss, last, ',');
        getline(ss, gender, ',');
        getline(ss, dob, ',');
        getline(ss, social, ',');
        getline(ss, pass, '\n');

		Staff temp = createStaff(username, first, last, stoi(gender), dob, social, pass);
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
